#pragma once

#include <string>
#include "shared/exceptions/validation_exception.h"

using std::string;

class Table {
public:
    Table(
        int id,
        int number,
        int capacity,
        bool available = true);

    int getId() const;
    int getNumber() const;
    void setNumber(int number);
    int getCapacity() const;
    void setCapacity(int capacity);
    bool isAvailable() const;
    void setAvailable(bool available);

private:
    int id;
    int number;
    int capacity;
    bool available;

    void validate();
    void validateNumber();
    void validateCapacity();
};
