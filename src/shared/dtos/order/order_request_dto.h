#pragma once

#include <string>
#include <optional>
#include <json/json.h>
#include "shared/enums/payment_type.h"
#include "shared/helpers/payment_type_helper.h"
#include "shared/exceptions/validation_exception.h"

using std::string;
using std::optional;

struct OrderRequestDto {
    int tableId;
    int waiterId;
    optional<int> customerId;
    optional<int> employeeId;
    PaymentType paymentType;
    bool closed;

    static OrderRequestDto fromJsonForCreate(Json::Value json)
    {
        OrderRequestDto dto;

        if (!json.isMember("tableId") || !json["tableId"].isInt()) {
            throw ValidationException("Field 'tableId' is required and must be an integer.");
        }

        if (!json.isMember("waiterId") || !json["waiterId"].isInt()) {
            throw ValidationException("Field 'waiterId' is required and must be an integer.");
        }

        if (!json.isMember("paymentType") || !json["paymentType"].isString()) {
            throw ValidationException("Field 'paymentType' is required and must be a string.");
        }

        dto.tableId = json["tableId"].asInt();
        dto.waiterId = json["waiterId"].asInt();

        bool hasCustomer = json.isMember("customerId") && json["customerId"].isInt();
        bool hasEmployee = json.isMember("employeeId") && json["employeeId"].isInt();

        if (hasCustomer && hasEmployee) {
            throw ValidationException(
                "Order cannot have both 'customerId' and 'employeeId'. Choose only one."
            );
        }
        if (!hasCustomer && !hasEmployee) {
            throw ValidationException(
                "Order must have exactly one of: 'customerId' or 'employeeId'."
            );
        }

        if (hasCustomer) {
            dto.customerId = json["customerId"].asInt();
        } else {
            dto.customerId = optional<int>();
        }

        if (hasEmployee) {
            dto.employeeId = json["employeeId"].asInt();
        } else {
            dto.employeeId = optional<int>();
        }

        string paymentTypeStr = json["paymentType"].asString();
        dto.paymentType = PaymentTypeHelper::fromString(paymentTypeStr);

        dto.closed = false; // na criação sempre começa aberta

        return dto;
    }

    static OrderRequestDto fromJsonForUpdate(Json::Value json)
    {
        OrderRequestDto dto;

        if (!json.isMember("tableId") || !json["tableId"].isInt()) {
            throw ValidationException("Field 'tableId' is required and must be an integer.");
        }

        if (!json.isMember("waiterId") || !json["waiterId"].isInt()) {
            throw ValidationException("Field 'waiterId' is required and must be an integer.");
        }

        if (!json.isMember("paymentType") || !json["paymentType"].isString()) {
            throw ValidationException("Field 'paymentType' is required and must be a string.");
        }

        if (!json.isMember("closed") || !json["closed"].isBool()) {
            throw ValidationException("Field 'closed' is required and must be a boolean.");
        }

        dto.tableId = json["tableId"].asInt();
        dto.waiterId = json["waiterId"].asInt();

        bool hasCustomer = json.isMember("customerId") && json["customerId"].isInt();
        bool hasEmployee = json.isMember("employeeId") && json["employeeId"].isInt();

        if (hasCustomer && hasEmployee) {
            throw ValidationException(
                "Order cannot have both 'customerId' and 'employeeId'. Choose only one."
            );
        }
        if (!hasCustomer && !hasEmployee) {
            throw ValidationException(
                "Order must have exactly one of: 'customerId' or 'employeeId'."
            );
        }

        if (hasCustomer) {
            dto.customerId = json["customerId"].asInt();
        } else {
            dto.customerId = optional<int>();
        }

        if (hasEmployee) {
            dto.employeeId = json["employeeId"].asInt();
        } else {
            dto.employeeId = optional<int>();
        }

        string paymentTypeStr = json["paymentType"].asString();
        dto.paymentType = PaymentTypeHelper::fromString(paymentTypeStr);

        dto.closed = json["closed"].asBool();

        return dto;
    }
};
