#pragma once

#include <string>
#include <json/json.h>
#include "models/user/customer.h"

using std::string;

struct CustomerResponseDto {
    int id;
    string name;
    string email;
    string phone;
    int loyaltyPoints;

    static CustomerResponseDto fromModel(Customer c) 
    {
        CustomerResponseDto dto;
        dto.id = c.getId();
        dto.name = c.getName();
        dto.email = c.getEmail();
        dto.phone = c.getPhone();
        dto.loyaltyPoints = c.getLoyaltyPoints();
        return dto;
    }

    Json::Value toJson() const 
    {
        Json::Value body;
        body["id"] = id;
        body["name"] = name;
        body["email"] = email;
        body["phone"] = phone;
        body["loyaltyPoints"] = loyaltyPoints;
        return body;
    }
};
