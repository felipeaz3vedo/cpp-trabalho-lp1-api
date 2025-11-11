#pragma once

#include <json/json.h>
#include "models/table/table.h"

struct TableResponseDto {
    int id;
    int number;
    int capacity;
    bool available;

    static TableResponseDto fromModel(Table table)
    {
        TableResponseDto dto;
        dto.id = table.getId();
        dto.number = table.getNumber();
        dto.capacity = table.getCapacity();
        dto.available = table.isAvailable();
        return dto;
    }

    Json::Value toJson() const
    {
        Json::Value json;
        json["id"] = id;
        json["number"] = number;
        json["capacity"] = capacity;
        json["available"] = available;
        return json;
    }
};
