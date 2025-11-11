#pragma once

#include <vector>
#include <string>
#include "models/user/employee.h"

using std::string;

class EmployeeRepository {
public:
    static Employee createEmployee(
        string name,
        string email,
        string document,
        EmployeeRole role);

    static std::vector<Employee> findAll();

    static Employee findById(int id);

    static Employee updateEmployee(
        int id,
        string name,
        string email,
        string document,
        EmployeeRole role,
        bool active);

    static void deleteEmployee(int id);

private:
    static std::vector<Employee> employees;
    static int nextId;
};
