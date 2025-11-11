#pragma once

#include <string>
#include <json/json.h>
#include "shared/exceptions/validation_exception.h"

using std::string;

struct MenuItemRequestDto {
    string name;
    string description;
    double price;
    bool active;

    static MenuItemRequestDto fromJson(const Json::Value& json) {
        MenuItemRequestDto dto;

        if (!json.isMember("name") || !json["name"].isString()) {
            throw ValidationException("Field 'name' is required and must be a string.");
        }

        if (!json.isMember("price") || !json["price"].isNumeric()) {
            throw ValidationException("Field 'price' is required and must be numeric.");
        }

        dto.name        = json["name"].asString();
        dto.description = json.get("description", "").asString();
        dto.price       = json["price"].asDouble();
        dto.active      = json.get("active", true).asBool();

        return dto;
    }
};
