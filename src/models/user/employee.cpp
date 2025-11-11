#include "models/user/employee.h"

Employee::Employee(
    int id,
    string name,
    string email,
    string cpf,
    EmployeeRole role,
    bool active)
    : User(id, name, email, UserType::EMPLOYEE)
{
    this->cpf = cpf;
    this->role = role;
    this->active = active;
}

string Employee::getCpf() const
{
    return this->cpf;
}

EmployeeRole Employee::getRole() const
{
    return this->role;
}

bool Employee::isActive() const
{
    return this->active;
}

void Employee::setCpf(string cpf)
{
    this->cpf = cpf;
}

void Employee::setRole(EmployeeRole role)
{
    this->role = role;
}

void Employee::setActive(bool active)
{
    this->active = active;
}

double Employee::calculateDiscount(double orderTotal) const
{
    return orderTotal * 0.10;
}
