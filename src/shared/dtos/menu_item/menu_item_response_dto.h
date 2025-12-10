#pragma once

#include <string>
#include <json/json.h>
#include "models/menu_item/menu_item.h"

using std::string;

struct MenuItemResponseDto
{
    int id;
    string name;
    string description;
    double price;
    bool active;
    int categoryId;

    static MenuItemResponseDto fromModel(const MenuItem &item)
    {
        MenuItemResponseDto dto;

        dto.id          = item.getId();
        dto.name        = item.getName();
        dto.description = item.getDescription();
        dto.price       = item.getPrice();
        dto.active      = item.isActive();
        dto.categoryId  = item.getCategoryId();

        return dto;
    }

    Json::Value toJson() const
    {
        Json::Value json;

        json["id"]          = id;
        json["name"]        = name;
        json["description"] = description;
        json["price"]       = price;
        json["active"]      = active;
        json["categoryId"]  = categoryId;

        return json;
    }
};
