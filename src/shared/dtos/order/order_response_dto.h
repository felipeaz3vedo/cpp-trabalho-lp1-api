#pragma once

#include <optional>
#include <json/json.h>
#include "models/order/order.h"
#include "shared/helpers/payment_type_helper.h"

using std::optional;

struct OrderResponseDto {
    int id;
    int tableId;
    int waiterId;
    optional<int> customerId;
    PaymentType paymentType;
    double subtotal;
    double discount;
    double fee;
    double total;
    bool closed;

    static OrderResponseDto fromModel(Order order)
    {
        OrderResponseDto dto;
        dto.id = order.getId();
        dto.tableId = order.getTableId();
        dto.waiterId = order.getWaiterId();
        dto.paymentType = order.getPaymentType();
        dto.subtotal = order.getSubtotal();
        dto.discount = order.getDiscount();
        dto.fee = order.getFee();
        dto.total = order.getTotal();
        dto.closed = order.isClosed();

        if (order.hasCustomer()) {
            dto.customerId = order.getCustomerId().value();
        } else {
            dto.customerId = optional<int>();
        }

        return dto;
    }

    Json::Value toJson() const
    {
        Json::Value json;
        json["id"] = this->id;
        json["tableId"] = this->tableId;
        json["waiterId"] = this->waiterId;
        json["paymentType"] = PaymentTypeHelper::toString(this->paymentType);
        json["subtotal"] = this->subtotal;
        json["discount"] = this->discount;
        json["fee"] = this->fee;
        json["total"] = this->total;
        json["closed"] = this->closed;

        if (this->customerId.has_value()) {
            json["customerId"] = this->customerId.value();
        } else {
            json["customerId"] = Json::nullValue;
        }

        return json;
    }
};
