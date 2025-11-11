#pragma once

#include <string>
#include "shared/enums/employee_role.h"

using std::string;

namespace EmployeeRoleHelper {
    EmployeeRole fromString(string value);
    string toString(EmployeeRole role);
}
