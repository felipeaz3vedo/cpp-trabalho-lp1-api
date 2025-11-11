#pragma once

#include <string>
#include "models/user/user.h"

using std::string;

class Customer : public User {
public:
    Customer(
        int id,
        string name,
        string email,
        string phone,
        int loyaltyPoints = 0);

    string getPhone() const;
    void setPhone(string phone);

    int getLoyaltyPoints() const;
    void setLoyaltyPoints(int points);

    double calculateDiscount(double orderTotal) const override;

private:
    string phone;
    int loyaltyPoints;
};
