#pragma once

#include <string>
#include <json/json.h>
#include "shared/exceptions/validation_exception.h"

using std::string;

struct CategoryRequestDto
{
    string name;
    string description;
    bool active;

    static CategoryRequestDto fromJson(const Json::Value &json)
    {
        CategoryRequestDto dto;

        if (!json.isMember("name") || !json["name"].isString())
        {
            throw ValidationException("Field 'name' is required and must be a string.");
        }

        dto.name = json["name"].asString();

        if (json.isMember("description") && json["description"].isString())
        {
            dto.description = json["description"].asString();
        }
        else
        {
            dto.description = "";
        }

        if (json.isMember("active") && json["active"].isBool())
        {
            dto.active = json["active"].asBool();
        }
        else
        {
            dto.active = true;
        }

        return dto;
    }
};
