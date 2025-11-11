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

        if (json.isMember("customerId") && json["customerId"].isInt()) {
            dto.customerId = json["customerId"].asInt();
        } else {
            dto.customerId = optional<int>();
        }

        string paymentTypeStr = json["paymentType"].asString();
        dto.paymentType = PaymentTypeHelper::fromString(paymentTypeStr);

        dto.closed = false;

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

        dto.tableId = json["tableId"].asInt();
        dto.waiterId = json["waiterId"].asInt();

        if (json.isMember("customerId") && json["customerId"].isInt()) {
            dto.customerId = json["customerId"].asInt();
        } else {
            dto.customerId = optional<int>();
        }

        string paymentTypeStr = json["paymentType"].asString();
        dto.paymentType = PaymentTypeHelper::fromString(paymentTypeStr);

        dto.closed = json.get("closed", false).asBool();

        return dto;
    }
};
