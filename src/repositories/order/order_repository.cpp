#include "repositories/order/order_repository.h"
#include "shared/exceptions/not_found_exception.h"

vector<Order> OrderRepository::orders = {};
int OrderRepository::nextId = 1;

Order OrderRepository::createOrder(
    int tableId,
    int waiterId,
    PaymentType paymentType,
    optional<int> customerId,
    optional<int> employeeId)
{
    Order order(
        nextId,
        tableId,
        waiterId,
        paymentType,
        customerId,
        employeeId
    );

    orders.push_back(order);
    nextId++;

    return order;
}

vector<Order> OrderRepository::findAll()
{
    return orders;
}

Order OrderRepository::findById(int id)
{
    for (const Order& order : orders)
    {
        if (order.getId() == id)
        {
            return order;
        }
    }

    throw NotFoundException("Order not found.");
}

Order OrderRepository::updateOrder(
    int id,
    int tableId,
    int waiterId,
    PaymentType paymentType,
    optional<int> customerId,
    optional<int> employeeId,
    bool closed)
{
    for (Order& order : orders)
    {
        if (order.getId() == id)
        {
            order.setTableId(tableId);
            order.setWaiterId(waiterId);
            order.setPaymentType(paymentType);

            if (customerId.has_value()) {
                order.setCustomerId(customerId.value());
            } else {
                order.clearCustomer();
            }

            if (employeeId.has_value()) {
                order.setEmployeeId(employeeId.value());
            } else {
                order.clearEmployee();
            }

            order.setClosed(closed);
            return order;
        }
    }

    throw NotFoundException("Order not found.");
}

Order OrderRepository::updateTotals(
    int id,
    double subtotal,
    double discount,
    double fee,
    double total)
{
    for (Order& order : orders)
    {
        if (order.getId() == id)
        {
            order.setSubtotal(subtotal);
            order.setDiscount(discount);
            order.setFee(fee);
            order.setTotal(total);
            return order;
        }
    }

    throw NotFoundException("Order not found.");
}

void OrderRepository::deleteOrder(int id)
{
    for (size_t i = 0; i < orders.size(); i++)
    {
        if (orders[i].getId() == id)
        {
            orders.erase(orders.begin() + static_cast<long>(i));
            return;
        }
    }

    throw NotFoundException("Order not found.");
}
