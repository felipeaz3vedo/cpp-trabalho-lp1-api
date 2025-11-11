#pragma once

#include "shared/enums/user_type.h"
#include "shared/exceptions/validation_exception.h"
#include <string>

using std::string;

class User {
public:
    User(
        int id,
         string name,
         string email,
         UserType type);

    virtual ~User() = default;

    int getId() const;
    string getName() const;
    void setName(string name);
    string getEmail() const;
    void setEmail(string email);
    UserType getType() const;

    virtual double calculateDiscount(double orderTotal) const = 0;

protected:
    int id;
    string name;
    string email;
    UserType type;

    void validate();
    void validateName();
    void validateEmail();
};