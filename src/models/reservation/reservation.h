#pragma once

#include <string>
#include "shared/exceptions/validation_exception.h"

using std::string;

class Reservation {
public:
    Reservation(
        int id,
        int customerId,
        int tableId,
        string startDateTime,
        string endDateTime,
        string notes = "",
        bool active = true);

    int getId() const;

    int getCustomerId() const;
    void setCustomerId(int customerId);

    int getTableId() const;
    void setTableId(int tableId);

    string getStartDateTime() const;
    void setStartDateTime(string startDateTime);

    string getEndDateTime() const;
    void setEndDateTime(string endDateTime);

    string getNotes() const;
    void setNotes(string notes);

    bool isActive() const;
    void setActive(bool active);

private:
    int id;
    int customerId;
    int tableId;
    string startDateTime;
    string endDateTime;
    string notes;
    bool active;

    void validate();
    void validateCustomerId();
    void validateTableId();
    void validateDateTimes();
};
