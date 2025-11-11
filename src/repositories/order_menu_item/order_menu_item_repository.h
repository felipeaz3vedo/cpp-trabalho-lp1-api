#pragma once

#include <vector>
#include "models/order_menu_item/order_menu_item.h"

using std::vector;

class OrderMenuItemRepository {
public:
    static OrderMenuItem createOrderMenuItem(
        int orderId,
        int menuItemId,
        int quantity,
        double unitPrice
    );

    static vector<OrderMenuItem> findAll();

    static vector<OrderMenuItem> findByOrderId(int orderId);

    static OrderMenuItem findByOrderIdAndMenuItemId(
        int orderId,
        int menuItemId);

    static OrderMenuItem updateOrderMenuItem(
        int id,
        int quantity,
        double unitPrice
    );

    static void deleteOrderMenuItem(int id);

    static void deleteAllByOrderId(int orderId);

private:
    static vector<OrderMenuItem> orderItems;
    static int nextId;
};
