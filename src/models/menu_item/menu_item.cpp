#include "models/menu_item/menu_item.h"

MenuItem::MenuItem(
    int id,
    string name,
    string description,
    double price,
    bool active)
{
    this->id = id;
    this->name = name;
    this->description = description;
    this->price = price;
    this->active = active;

    this->validate();
}

int MenuItem::getId() const
{
    return this->id;
}

string MenuItem::getName() const
{
    return this->name;
}

void MenuItem::setName(string name)
{
    this->name = name;
    this->validateName();
}

string MenuItem::getDescription() const
{
    return this->description;
}

void MenuItem::setDescription(string description)
{
    this->description = description;
}

double MenuItem::getPrice() const
{
    return this->price;
}

void MenuItem::setPrice(double price)
{
    this->price = price;
    this->validatePrice();
}

bool MenuItem::isActive() const
{
    return this->active;
}

void MenuItem::setActive(bool active)
{
    this->active = active;
}

void MenuItem::validate()
{
    this->validateName();
    this->validatePrice();
}

void MenuItem::validateName()
{
    if (this->name == "") {
        throw ValidationException("MenuItem 'name' must not be empty.");
    }
}

void MenuItem::validatePrice()
{
    if (this->price <= 0.0) {
        throw ValidationException("MenuItem 'price' must be greater than zero.");
    }
}
