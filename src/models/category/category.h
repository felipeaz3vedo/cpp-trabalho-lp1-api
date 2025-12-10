#pragma once

#include <string>
#include "shared/exceptions/validation_exception.h"

using std::string;

class Category
{
public:
    Category(int id,
             string name,
             string description,
             bool active = true);

    int getId() const;

    string getName() const;
    void setName(const string& name);

    string getDescription() const;
    void setDescription(const string& description);

    bool isActive() const;
    void setActive(bool active);

private:
    int id;
    string name;
    string description;
    bool active;

    void validate();
    void validateName();
};
