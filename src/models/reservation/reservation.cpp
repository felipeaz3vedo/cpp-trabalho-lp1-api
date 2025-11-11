#include "models/reservation/reservation.h"

Reservation::Reservation(
    int id,
    int customerId,
    int tableId,
    string startDateTime,
    string endDateTime,
    string notes,
    bool active)
{
    this->id = id;
    this->customerId = customerId;
    this->tableId = tableId;
    this->startDateTime = startDateTime;
    this->endDateTime = endDateTime;
    this->notes = notes;
    this->active = active;

    this->validate();
}

int Reservation::getId() const
{
    return this->id;
}

int Reservation::getCustomerId() const
{
    return this->customerId;
}

void Reservation::setCustomerId(int customerId)
{
    this->customerId = customerId;
    this->validateCustomerId();
}

int Reservation::getTableId() const
{
    return this->tableId;
}

void Reservation::setTableId(int tableId)
{
    this->tableId = tableId;
    this->validateTableId();
}

string Reservation::getStartDateTime() const
{
    return this->startDateTime;
}

void Reservation::setStartDateTime(string startDateTime)
{
    this->startDateTime = startDateTime;
    this->validateDateTimes();
}

string Reservation::getEndDateTime() const
{
    return this->endDateTime;
}

void Reservation::setEndDateTime(string endDateTime)
{
    this->endDateTime = endDateTime;
    this->validateDateTimes();
}

string Reservation::getNotes() const
{
    return this->notes;
}

void Reservation::setNotes(string notes)
{
    this->notes = notes;
}

bool Reservation::isActive() const
{
    return this->active;
}

void Reservation::setActive(bool active)
{
    this->active = active;
}

void Reservation::validate()
{
    this->validateCustomerId();
    this->validateTableId();
    this->validateDateTimes();
}

void Reservation::validateCustomerId()
{
    if (this->customerId <= 0) {
        throw ValidationException("Field 'customerId' must be greater than zero.");
    }
}

void Reservation::validateTableId()
{
    if (this->tableId <= 0) {
        throw ValidationException("Field 'tableId' must be greater than zero.");
    }
}

void Reservation::validateDateTimes()
{
    if (this->startDateTime.empty()) {
        throw ValidationException("Field 'startDateTime' must not be empty.");
    }

    if (this->endDateTime.empty()) {
        throw ValidationException("Field 'endDateTime' must not be empty.");
    }

    if (!(this->startDateTime < this->endDateTime)) {
        throw ValidationException("Field 'startDateTime' must be earlier than 'endDateTime'.");
    }
}
