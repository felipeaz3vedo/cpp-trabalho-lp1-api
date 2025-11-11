#pragma once

#include <string>
#include <json/json.h>
#include "shared/exceptions/validation_exception.h"

using std::string;

struct ReservationRequestDto {
    int customerId;
    int tableId;
    string startDateTime;
    string endDateTime;
    string notes;
    bool active;

    static ReservationRequestDto fromJson(Json::Value json)
    {
        ReservationRequestDto dto;

        if (!json.isMember("customerId") || !json["customerId"].isInt())
        {
            throw ValidationException("Field 'customerId' is required and must be an integer.");
        }

        if (!json.isMember("tableId") || !json["tableId"].isInt())
        {
            throw ValidationException("Field 'tableId' is required and must be an integer.");
        }

        if (!json.isMember("startDateTime") || !json["startDateTime"].isString())
        {
            throw ValidationException("Field 'startDateTime' is required and must be a string.");
        }

        if (!json.isMember("endDateTime") || !json["endDateTime"].isString())
        {
            throw ValidationException("Field 'endDateTime' is required and must be a string.");
        }

        dto.customerId = json["customerId"].asInt();
        dto.tableId = json["tableId"].asInt();
        dto.startDateTime = json["startDateTime"].asString();
        dto.endDateTime = json["endDateTime"].asString();
        dto.notes = json.get("notes", "").asString();
        dto.active = json.get("active", true).asBool();

        return dto;
    }
};
