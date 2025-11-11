#pragma once

#include <string>
#include "shared/exceptions/validation_exception.h"

using std::string;

class MenuItem {
public:
    MenuItem(
        int id,
        string name,
        string description,
        double price,
        bool active = true
    );

    int getId() const;

    string getName() const;
    void setName(string name);
    string getDescription() const;
    void setDescription(string description);
    double getPrice() const;
    void setPrice(double price);
    bool isActive() const;
    void setActive(bool active);

private:
    int id;
    string name;
    string description;
    double price;
    bool active;

    void validate();
    void validateName();
    void validatePrice();
};
