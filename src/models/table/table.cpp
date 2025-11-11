#include "models/table/table.h"

Table::Table(
    int id,
    int number,
    int capacity,
    bool available)
{
    this->id = id;
    this->number = number;
    this->capacity = capacity;
    this->available = available;

    this->validate();
}

int Table::getId() const
{
    return this->id;
}

int Table::getNumber() const
{
    return this->number;
}

void Table::setNumber(int number)
{
    this->number = number;
    this->validateNumber();
}

int Table::getCapacity() const
{
    return this->capacity;
}

void Table::setCapacity(int capacity)
{
    this->capacity = capacity;
    this->validateCapacity();
}

bool Table::isAvailable() const
{
    return this->available;
}

void Table::setAvailable(bool available)
{
    this->available = available;
}

void Table::validate()
{
    this->validateNumber();
    this->validateCapacity();
}

void Table::validateNumber()
{
    if (this->number <= 0) {
        throw ValidationException("Table 'number' must be greater than zero.");
    }
}

void Table::validateCapacity()
{
    if (this->capacity <= 0) {
        throw ValidationException("Table 'capacity' must be greater than zero.");
    }

    if (this->capacity > 50) {
        throw ValidationException("Table 'capacity' must be lower or equal to 50.");
    }
}
