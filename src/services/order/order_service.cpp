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

    double calculateUserDiscount(const Order& order, double subtotal)
    {
        if (!order.hasCustomer()) {
            return 0.0;
        }

        int userId = order.getCustomerId().value();
        double discount = 0.0;

        bool discountApplied = false;

        try {
            Customer customer = CustomerRepository::findById(userId);
            discount = customer.calculateDiscount(subtotal);
            discountApplied = true;
        } catch (const NotFoundException&) {
        }

        if (!discountApplied) {
            try {
                Employee employee = EmployeeRepository::findById(userId);
                discount = employee.calculateDiscount(subtotal);
                discountApplied = true;
            } catch (const NotFoundException&) {
            }
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
    optional<int> customerId)
{
    TableRepository::findById(tableId);

    Employee waiter = EmployeeRepository::findById(waiterId);
    validateWaiterIsValid(waiter);

    if (customerId.has_value()) {
        int userId = customerId.value();

        bool found = true;
        try {
            CustomerRepository::findById(userId);
        } catch (const NotFoundException&) {
            try {
                EmployeeRepository::findById(userId);
            } catch (const NotFoundException&) {
                found = false;
            }
        }

        if (!found) {
            throw NotFoundException("Customer/Employee for discount not found.");
        }
    }

    Order order = OrderRepository::createOrder(
        tableId,
        waiterId,
        paymentType,
        customerId
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
    bool closed)
{
    Order existing = OrderRepository::findById(id);

    if (existing.isClosed() && !closed) {
        throw BusinessException("Closed order cannot be reopened.");
    }

    TableRepository::findById(tableId);

    Employee waiter = EmployeeRepository::findById(waiterId);
    validateWaiterIsValid(waiter);

    if (customerId.has_value()) {
        int userId = customerId.value();

        bool found = true;

        try {
            CustomerRepository::findById(userId);
        } catch (const NotFoundException&) {
            try {
                EmployeeRepository::findById(userId);
            } catch (const NotFoundException&) {
                found = false;
            }
        }

        if (!found) {
            throw NotFoundException("Customer/Employee for discount not found.");
        }
    }

    Order updated = OrderRepository::updateOrder(
        id,
        tableId,
        waiterId,
        paymentType,
        customerId,
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

    OrderRepository::updateOrder(
        updated.getId(),
        updated.getTableId(),
        updated.getWaiterId(),
        updated.getPaymentType(),
        updated.hasCustomer()
            ? optional<int>(updated.getCustomerId().value())
            : optional<int>(),
        true
    );

    if (updated.hasCustomer()) {
        int userId = updated.getCustomerId().value();

        try {
            Customer customer = CustomerRepository::findById(userId);

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
