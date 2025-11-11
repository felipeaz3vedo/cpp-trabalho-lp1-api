#pragma once

#include <string>
#include <json/json.h>
#include "models/user/employee.h"
#include "shared/helpers/employee_role_helper.h"

using std::string;

struct EmployeeResponseDto {
    int id;
    string name;
    string email;
    string cpf;
    bool active;
    string role;

    static EmployeeResponseDto fromModel(Employee e) {
        EmployeeResponseDto dto;
        dto.id = e.getId();
        dto.name = e.getName();
        dto.email = e.getEmail();
        dto.cpf = e.getCpf();
        dto.active = e.isActive();
        dto.role = EmployeeRoleHelper::toString(e.getRole());
        return dto;
    }

    Json::Value toJson() const {
        Json::Value body;
        body["id"] = id;
        body["name"] = name;
        body["email"] = email;
        body["cpf"] = cpf;
        body["active"] = active;
        body["role"] = role;
        return body;
    }
};
