#pragma once

#include <string>
#include "shared/exceptions/validation_exception.h"

using std::string;

class MenuItem
{
public:
    MenuItem(
        int id,
        string name,
        string description,
        double price,
        bool active = true,
        int categoryId = 0);

    int getId() const;

    string getName() const;
    void setName(string name);
    string getDescription() const;
    void setDescription(string description);
    double getPrice() const;
    void setPrice(double price);
    bool isActive() const;
    void setActive(bool active);
    int getCategoryId() const;
    void setCategoryId(int categoryId);

private:
    int id;
    string name;
    string description;
    double price;
    bool active;
    int categoryId;

    void validate();
    void validateName();
    void validatePrice();
    void validateCategoryId();
};
