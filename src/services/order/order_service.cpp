#include "services/order/order_service.h"
#include "services/payment/payment_service.h"
#include "repositories/order/order_repository.h"
#include "repositories/order_menu_item/order_menu_item_repository.h"
#include "repositories/table/table_repository.h"
#include "repositories/user/employee_repository.h"
#include "repositories/user/customer_repository.h"
#include "repositories/menu_item/menu_item_repository.h"
#include "shared/exceptions/validation_exception.h"
#include "shared/exceptions/business_exception.h"
#include "shared/exceptions/not_found_exception.h"
#include "shared/enums/employee_role.h"

#include <vector>
#include <optional>

using std::string;
using std::vector;
using std::optional;

namespace {
    void validateQuantity(int quantity)
    {
        if (quantity <= 0) {
            throw ValidationException("Field 'quantity' must be greater than zero.");
        }
    }

    void validateOrderIsNotClosed(const Order& order)
    {
        if (order.isClosed()) {
            throw BusinessException("Order is already closed and cannot be modified.");
        }
    }

    void validateWaiterIsValid(const Employee& employee)
    {
        if (!employee.isActive()) {
            throw BusinessException("Waiter must be active.");
        }

        if (employee.getRole() != EmployeeRole::WAITER) {
            throw BusinessException("Employee must have role WAITER to be a waiter.");
        }
    }

    void validateDiscountAssociation(optional<int> customerId, optional<int> employeeId)
    {
        bool hasCustomer = customerId.has_value();
        bool hasEmployee = employeeId.has_value();

        if (hasCustomer && hasEmployee) {
            throw BusinessException(
                "Order cannot be associated with both a customer and an employee."
            );
        }

        if (!hasCustomer && !hasEmployee) {
            throw BusinessException(
                "Order must be associated with exactly one of: customerId or employeeId."
            );
        }
    }

    double calculateUserDiscount(const Order& order, double subtotal)
    {
        double discount = 0.0;

        if (order.hasCustomer()) {
            int customerId = order.getCustomerId().value();
            Customer customer = CustomerRepository::findById(customerId);
            discount = customer.calculateDiscount(subtotal);
        } else if (order.hasEmployee()) {
            int employeeId = order.getEmployeeId().value();
            Employee employee = EmployeeRepository::findById(employeeId);
            discount = employee.calculateDiscount(subtotal);
        } else {
            discount = 0.0;
        }

        if (discount < 0.0) {
            discount = 0.0;
        }
        if (discount > subtotal) {
            discount = subtotal;
        }

        return discount;
    }

    void recalculateTotals(int orderId)
    {
        Order order = OrderRepository::findById(orderId);

        vector<OrderMenuItem> items = OrderMenuItemRepository::findByOrderId(orderId);

        double subtotal = 0.0;
        for (OrderMenuItem item : items) {
            subtotal += item.getTotalPrice();
        }

        double discount = calculateUserDiscount(order, subtotal);

        double amountAfterDiscount = subtotal - discount;

        double fee = PaymentService::calculateFee(
            order.getPaymentType(),
            amountAfterDiscount
        );

        double total = amountAfterDiscount + fee;

        OrderRepository::updateTotals(
            orderId,
            subtotal,
            discount,
            fee,
            total
        );
    }
}

Order OrderService::createOrder(
    int tableId,
    int waiterId,
    PaymentType paymentType,
    optional<int> customerId,
    optional<int> employeeId)
{
    TableRepository::findById(tableId);

    Employee waiter = EmployeeRepository::findById(waiterId);
    validateWaiterIsValid(waiter);

    validateDiscountAssociation(customerId, employeeId);

    if (customerId.has_value()) {
        CustomerRepository::findById(customerId.value());
    } else if (employeeId.has_value()) {
        EmployeeRepository::findById(employeeId.value());
    }

    Order order = OrderRepository::createOrder(
        tableId,
        waiterId,
        paymentType,
        customerId,
        employeeId
    );

    return order;
}

vector<Order> OrderService::listOrders()
{
    return OrderRepository::findAll();
}

Order OrderService::getOrderById(int id)
{
    return OrderRepository::findById(id);
}

Order OrderService::updateOrder(
    int id,
    int tableId,
    int waiterId,
    PaymentType paymentType,
    optional<int> customerId,
    optional<int> employeeId,
    bool closed)
{
    Order existing = OrderRepository::findById(id);

    if (existing.isClosed() && !closed) {
        throw BusinessException("Closed order cannot be reopened.");
    }

    TableRepository::findById(tableId);

    Employee waiter = EmployeeRepository::findById(waiterId);
    validateWaiterIsValid(waiter);

    validateDiscountAssociation(customerId, employeeId);

    if (customerId.has_value()) {
        CustomerRepository::findById(customerId.value());
    } else if (employeeId.has_value()) {
        EmployeeRepository::findById(employeeId.value());
    }

    Order updated = OrderRepository::updateOrder(
        id,
        tableId,
        waiterId,
        paymentType,
        customerId,
        employeeId,
        closed
    );

    recalculateTotals(id);

    return updated;
}

void OrderService::deleteOrder(int id)
{
    Order existing = OrderRepository::findById(id);

    if (existing.isClosed()) {
        throw BusinessException("Closed order cannot be deleted.");
    }

    OrderMenuItemRepository::deleteAllByOrderId(id);

    OrderRepository::deleteOrder(id);
}

Order OrderService::closeOrder(int id)
{
    Order order = OrderRepository::findById(id);

    if (order.isClosed()) {
        throw BusinessException("Order is already closed.");
    }

    recalculateTotals(id);

    Order updated = OrderRepository::findById(id);
    updated.setClosed(true);

    optional<int> customerIdArg;
    optional<int> employeeIdArg;

    if (updated.hasCustomer()) {
        customerIdArg = updated.getCustomerId().value();
    } else if (updated.hasEmployee()) {
        employeeIdArg = updated.getEmployeeId().value();
    }

    OrderRepository::updateOrder(
        updated.getId(),
        updated.getTableId(),
        updated.getWaiterId(),
        updated.getPaymentType(),
        customerIdArg,
        employeeIdArg,
        true
    );

    if (updated.hasCustomer()) {
        int customerId = updated.getCustomerId().value();

        try {
            Customer customer = CustomerRepository::findById(customerId);

            int points = updated.calculateLoyaltyPoints();
            int newPoints = customer.getLoyaltyPoints() + points;

            CustomerRepository::updateCustomer(
                customer.getId(),
                customer.getName(),
                customer.getEmail(),
                customer.getPhone(),
                newPoints
            );
        } catch (const NotFoundException&) {
        }
    }

    return OrderRepository::findById(id);
}

OrderMenuItem OrderService::addItemToOrder(
    int orderId,
    int menuItemId,
    int quantity)
{
    validateQuantity(quantity);

    Order order = OrderRepository::findById(orderId);
    validateOrderIsNotClosed(order);

    MenuItem menuItem = MenuItemRepository::findById(menuItemId);
    if (!menuItem.isActive()) {
        throw BusinessException("Cannot add inactive menu item to order.");
    }

    double unitPrice = menuItem.getPrice();

    OrderMenuItem item = OrderMenuItemRepository::createOrderMenuItem(
        orderId,
        menuItemId,
        quantity,
        unitPrice
    );

    recalculateTotals(orderId);

    return item;
}

OrderMenuItem OrderService::updateOrderItemQtd(
    int orderId,
    int menuItemId,
    int quantity)
{
    validateQuantity(quantity);

    Order order = OrderRepository::findById(orderId);
    validateOrderIsNotClosed(order);

    MenuItem menuItem = MenuItemRepository::findById(menuItemId);
    if (!menuItem.isActive()) {
        throw BusinessException("Cannot update item with inactive menu item.");
    }

    OrderMenuItem existing =
        OrderMenuItemRepository::findByOrderIdAndMenuItemId(orderId, menuItemId);

    OrderMenuItem updated = OrderMenuItemRepository::updateOrderMenuItem(
        existing.getId(),
        quantity,
        existing.getUnitPrice()
    );

    recalculateTotals(orderId);

    return updated;
}

void OrderService::removeOrderItem(
    int orderId,
    int menuItemId)
{
    Order order = OrderRepository::findById(orderId);
    validateOrderIsNotClosed(order);

    OrderMenuItem existing =
        OrderMenuItemRepository::findByOrderIdAndMenuItemId(orderId, menuItemId);

    OrderMenuItemRepository::deleteOrderMenuItem(existing.getId());

    recalculateTotals(orderId);
}

vector<OrderMenuItem> OrderService::listItemsByOrder(int orderId)
{
    OrderRepository::findById(orderId);

    return OrderMenuItemRepository::findByOrderId(orderId);
}
