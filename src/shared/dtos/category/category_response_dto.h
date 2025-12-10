#pragma once

#include <string>
#include <json/json.h>
#include "models/category/category.h"

using std::string;

struct CategoryResponseDto
{
    int id;
    string name;
    string description;
    bool active;

    static CategoryResponseDto fromModel(const Category &category)
    {
        CategoryResponseDto dto;
        dto.id          = category.getId();
        dto.name        = category.getName();
        dto.description = category.getDescription();
        dto.active      = category.isActive();
        return dto;
    }

    Json::Value toJson() const
    {
        Json::Value json;
        json["id"]          = id;
        json["name"]        = name;
        json["description"] = description;
        json["active"]      = active;
        return json;
    }
};
