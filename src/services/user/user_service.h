#pragma once

#include <vector>
#include <string>
#include "models/user/employee.h"
#include "models/user/customer.h"

using std::string;

class UserService {
public:
    static Employee createEmployee(
        string name,
        string email,
        string document,
        EmployeeRole role);

    static std::vector<Employee> listEmployees();

    static Employee getEmployeeById(int id);

    static Employee updateEmployee(
        int id,
        string name,
        string email,
        string document,
        EmployeeRole role,
        bool active);

    static void deleteEmployee(int id);

    static Customer createCustomer(
        string name,
        string email,
        string phone);

    static std::vector<Customer> listCustomers();

    static Customer getCustomerById(int id);

    static Customer updateCustomer(
        int id,
        string name,
        string email,
        string phone,
        int loyaltyPoints);

    static void deleteCustomer(int id);
};
