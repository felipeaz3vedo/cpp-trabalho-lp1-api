#pragma once

#include <json/json.h>
#include "shared/exceptions/validation_exception.h"

struct OrderItemRequestDto {
    int menuItemId;
    int quantity;

    static OrderItemRequestDto fromJsonForCreate(const Json::Value& json) {
        OrderItemRequestDto dto;

        if (!json.isMember("menuItemId") || !json["menuItemId"].isInt()) {
            throw ValidationException(
                "Field 'menuItemId' is required and must be an integer."
            );
        }

        if (!json.isMember("quantity") || !json["quantity"].isInt()) {
            throw ValidationException(
                "Field 'quantity' is required and must be an integer."
            );
        }

        dto.menuItemId = json["menuItemId"].asInt();
        dto.quantity = json["quantity"].asInt();

        return dto;
    }

    static OrderItemRequestDto fromJsonForUpdate(const Json::Value& json) {
        OrderItemRequestDto dto;

        if (!json.isMember("quantity") || !json["quantity"].isInt()) {
            throw ValidationException(
                "Field 'quantity' is required and must be an integer."
            );
        }

        dto.menuItemId = 0;
        dto.quantity = json["quantity"].asInt();

        return dto;
    }
};
