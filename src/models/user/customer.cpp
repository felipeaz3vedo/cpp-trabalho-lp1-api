#include "models/user/customer.h"

Customer::Customer(
    int id,
    string name,
    string email,
    string phone,
    int loyaltyPoints)
    : User(id, name, email, UserType::CUSTOMER)
{
    this->phone = phone;
    this->loyaltyPoints = loyaltyPoints;
}

string Customer::getPhone() const
{
    return this->phone;
}

void Customer::setPhone(string phone)
{
    this->phone = phone;
}

int Customer::getLoyaltyPoints() const
{
    return this->loyaltyPoints;
}

void Customer::setLoyaltyPoints(int points)
{
    this->loyaltyPoints = points;
}

double Customer::calculateDiscount(double orderTotal) const
{
    if (this->loyaltyPoints >= 100) {
        return orderTotal * 0.05;
    }

    return 0.0;
}
