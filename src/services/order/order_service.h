#pragma once

#include <vector>
#include <optional>
#include "models/order/order.h"
#include "models/order_menu_item/order_menu_item.h"
#include "shared/enums/payment_type.h"

using std::vector;
using std::optional;

class OrderService {
public:
    static Order createOrder(
        int tableId,
        int waiterId,
        PaymentType paymentType,
        optional<int> customerId,
        optional<int> employeeId);

    static vector<Order> listOrders();

    static Order getOrderById(int id);

    static Order updateOrder(
        int id,
        int tableId,
        int waiterId,
        PaymentType paymentType,
        optional<int> customerId,
        optional<int> employeeId,
        bool closed);

    static void deleteOrder(int id);

    static Order closeOrder(int id);

    static OrderMenuItem addItemToOrder(
        int orderId,
        int menuItemId,
        int quantity);

    static OrderMenuItem updateOrderItemQtd(
        int orderId,
        int menuItemId,
        int quantity);

    static void removeOrderItem(
        int orderId,
        int menuItemId);

    static vector<OrderMenuItem> listItemsByOrder(int orderId);
};
