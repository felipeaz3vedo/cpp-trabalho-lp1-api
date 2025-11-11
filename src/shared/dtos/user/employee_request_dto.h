#pragma once

#include <string>
#include <json/json.h>
#include "shared/enums/employee_role.h"
#include "shared/helpers/employee_role_helper.h"
#include "shared/exceptions/validation_exception.h"

using std::string;

struct EmployeeRequestDto {
    string name;
    string email;
    string cpf;
    EmployeeRole role;
    bool active;

    static EmployeeRequestDto fromJson(Json::Value json) 
    {
        EmployeeRequestDto dto;

        if (!json.isMember("name") || !json["name"].isString()) 
        {
            throw ValidationException("Field 'name' is required and must be a string.");
        }

        if (!json.isMember("email") || !json["email"].isString())
        {
            throw ValidationException("Field 'email' is required and must be a string.");
        }

        if (!json.isMember("cpf") || !json["cpf"].isString()) 
        {
            throw ValidationException("Field 'cpf' is required and must be a string.");
        }

        if (!json.isMember("role") || !json["role"].isString()) 
        {
            throw ValidationException("Field 'role' is required and must be a string.");
        }

        dto.name = json["name"].asString();
        dto.email = json["email"].asString();
        dto.cpf = json["cpf"].asString();

        string roleStr = json["role"].asString();
        dto.role = EmployeeRoleHelper::fromString(roleStr);

        dto.active = json.get("active", true).asBool();

        return dto;
    }
};
