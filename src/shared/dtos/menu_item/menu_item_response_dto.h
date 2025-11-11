#pragma once

#include <string>
#include <json/json.h>
#include "models/menu_item/menu_item.h"

using std::string;

struct MenuItemResponseDto {
    int id;
    string name;
    string description;
    double price;
    bool active;

    static MenuItemResponseDto fromModel(const MenuItem& item) {
        MenuItemResponseDto dto;
        dto.id          = item.getId();
        dto.name        = item.getName();
        dto.description = item.getDescription();
        dto.price       = item.getPrice();
        dto.active      = item.isActive();
        return dto;
    }

    Json::Value toJson() const {
        Json::Value json;
        json["id"]          = this->id;
        json["name"]        = this->name;
        json["description"] = this->description;
        json["price"]       = this->price;
        json["active"]      = this->active;
        return json;
    }
};
