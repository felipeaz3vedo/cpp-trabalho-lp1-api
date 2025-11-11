#pragma once

#include <string>
#include <json/json.h>
#include "shared/exceptions/validation_exception.h"

using std::string;

struct TableRequestDto {
    int number;
    int capacity;
    bool available;

    static TableRequestDto fromJson(Json::Value json)
    {
        TableRequestDto dto;

        if (!json.isMember("number") || !json["number"].isInt())
        {
            throw ValidationException("Field 'number' is required and must be an integer.");
        }

        if (!json.isMember("capacity") || !json["capacity"].isInt())
        {
            throw ValidationException("Field 'capacity' is required and must be an integer.");
        }

        dto.number = json["number"].asInt();
        dto.capacity = json["capacity"].asInt();
        dto.available = json.get("available", true).asBool();

        return dto;
    }
};