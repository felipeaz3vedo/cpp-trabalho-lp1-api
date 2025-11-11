#pragma once

#include <json/json.h>
#include "models/reservation/reservation.h"

struct ReservationResponseDto {
    int id;
    int customerId;
    int tableId;
    std::string startDateTime;
    std::string endDateTime;
    std::string notes;
    bool active;

    static ReservationResponseDto fromModel(Reservation reservation)
    {
        ReservationResponseDto dto;
        dto.id = reservation.getId();
        dto.customerId = reservation.getCustomerId();
        dto.tableId = reservation.getTableId();
        dto.startDateTime = reservation.getStartDateTime();
        dto.endDateTime = reservation.getEndDateTime();
        dto.notes = reservation.getNotes();
        dto.active = reservation.isActive();
        return dto;
    }

    Json::Value toJson() const
    {
        Json::Value json;
        json["id"] = id;
        json["customerId"] = customerId;
        json["tableId"] = tableId;
        json["startDateTime"] = startDateTime;
        json["endDateTime"] = endDateTime;
        json["notes"] = notes;
        json["active"] = active;
        return json;
    }
};
