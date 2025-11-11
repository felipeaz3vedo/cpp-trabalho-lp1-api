#pragma once

#include <json/json.h>
#include "models/order_menu_item/order_menu_item.h"

struct OrderItemResponseDto {
    int id;
    int orderId;
    int menuItemId;
    int quantity;
    double unitPrice;
    double totalPrice;

    static OrderItemResponseDto fromModel(const OrderMenuItem& item) {
        OrderItemResponseDto dto;
        dto.id = item.getId();
        dto.orderId = item.getOrderId();
        dto.menuItemId = item.getMenuItemId();
        dto.quantity = item.getQuantity();
        dto.unitPrice = item.getUnitPrice();
        dto.totalPrice = item.getTotalPrice();
        return dto;
    }

    Json::Value toJson() const {
        Json::Value j;
        j["id"] = id;
        j["orderId"] = orderId;
        j["menuItemId"] = menuItemId;
        j["quantity"] = quantity;
        j["unitPrice"] = unitPrice;
        j["totalPrice"] = totalPrice;
        return j;
    }
};
