#pragma once

#include <string>
#include <json/json.h>
#include "shared/exceptions/validation_exception.h"

using std::string;

struct CustomerRequestDto {
    string name;
    string email;
    string phone;
    int loyaltyPoints;

    static CustomerRequestDto fromJson(Json::Value json) {
        CustomerRequestDto dto;

        if (!json.isMember("name") || !json["name"].isString()) 
        {
            throw ValidationException("Field 'name' is required and must be a string.");
        }

        if (!json.isMember("email") || !json["email"].isString()) 
        {
            throw ValidationException("Field 'email' is required and must be a string.");
        }

        if (!json.isMember("phone") || !json["phone"].isString()) 
        {
            throw ValidationException("Field 'phone' is required and must be a string.");
        }

        dto.name = json["name"].asString();
        dto.email = json["email"].asString();
        dto.phone = json["phone"].asString();
        dto.loyaltyPoints = json.get("loyaltyPoints", 0).asInt();

        return dto;
    }
};
