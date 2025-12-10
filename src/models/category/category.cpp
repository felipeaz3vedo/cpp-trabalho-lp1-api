#include "models/category/category.h"

Category::Category(
    int id,
    string name,
    string description,
    bool active)
{
    this->id = id;
    this->name = name;
    this->description = description;
    this->active = active;

    this->validate();
}

int Category::getId() const
{
    return this->id;
}

string Category::getName() const
{
    return this->name;
}

void Category::setName(const string& name)
{
    this->name = name;
    this->validateName();
}

string Category::getDescription() const
{
    return this->description;
}

void Category::setDescription(const string& description)
{
    this->description = description;
}

bool Category::isActive() const
{
    return this->active;
}

void Category::setActive(bool active)
{
    this->active = active;
}

void Category::validate()
{
    this->validateName();
}

void Category::validateName()
{
    if (this->name.empty())
    {
        throw ValidationException("Category 'name' must not be empty.");
    }
}
