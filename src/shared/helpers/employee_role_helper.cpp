#include "shared/helpers/employee_role_helper.h"
#include "shared/exceptions/validation_exception.h"
#include <stdexcept>

EmployeeRole EmployeeRoleHelper::fromString(string value)
{
    if (value == "MANAGER") {
        return EmployeeRole::MANAGER;
    } else if (value == "COOK") {
        return EmployeeRole::COOK;
    } else if (value == "CASHIER") {
        return EmployeeRole::CASHIER;
    } else if (value == "WAITER") {
        return EmployeeRole::WAITER;
    }

    throw ValidationException("Invalid employee role: " + value + ".");
}

string EmployeeRoleHelper::toString(EmployeeRole role)
{
    switch (role) {
        case EmployeeRole::MANAGER:
            return "MANAGER";
        case EmployeeRole::COOK:
            return "COOK";
        case EmployeeRole::CASHIER:
            return "CASHIER";
        case EmployeeRole::WAITER:
            return "WAITER";
        default:
            throw ValidationException("Invalid EmployeeRole enum value.");
    }
}