#pragma once

#include <string>
#include "models/user/user.h"
#include "shared/enums/employee_role.h"

using std::string;

class Employee : public User {
public:
    Employee(
        int id,
        string name,
        string email,
        string cpf,
        EmployeeRole role,
        bool active = true);

    string getCpf() const;
    EmployeeRole getRole() const;
    bool isActive() const;

    void setCpf(string cpf);
    void setRole(EmployeeRole role);
    void setActive(bool active);

    double calculateDiscount(double orderTotal) const override;

private:
    string cpf;
    EmployeeRole role;
    bool active;
};
