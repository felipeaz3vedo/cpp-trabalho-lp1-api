#include "services/user/user_service.h"
#include "repositories/user/employee_repository.h"
#include "repositories/user/customer_repository.h"
#include "shared/exceptions/business_exception.h"

using std::string;
using std::vector;

namespace {
    void ensureUniqueCpfOnCreate(const string& cpf)
    {
        vector<Employee> employees = EmployeeRepository::findAll();

        for (const Employee& e : employees)
        {
            if (e.getCpf() == cpf)
            {
                throw BusinessException("An employee with this CPF already exists.");
            }
        }
    }

    void ensureUniqueCpfOnUpdate(int employeeId, const string& cpf)
    {
        vector<Employee> employees = EmployeeRepository::findAll();

        for (const Employee& e : employees)
        {
            if (e.getId() == employeeId)
            {
                continue;
            }

            if (e.getCpf() == cpf)
            {
                throw BusinessException("Another employee with this CPF already exists.");
            }
        }
    }
}

Employee UserService::createEmployee(
    string name,
    string email,
    string cpf,
    EmployeeRole role)
{
    ensureUniqueCpfOnCreate(cpf);

    return EmployeeRepository::createEmployee(
        name,
        email,
        cpf,
        role);
}

std::vector<Employee> UserService::listEmployees()
{
    return EmployeeRepository::findAll();
}

Employee UserService::getEmployeeById(int id)
{
    return EmployeeRepository::findById(id);
}

Employee UserService::updateEmployee(
    int id,
    string name,
    string email,
    string cpf,
    EmployeeRole role,
    bool active)
{
    ensureUniqueCpfOnUpdate(id, cpf);

    return EmployeeRepository::updateEmployee(
        id,
        name,
        email,
        cpf,
        role,
        active);
}

void UserService::deleteEmployee(int id)
{
    EmployeeRepository::deleteEmployee(id);
}

Customer UserService::createCustomer(
    string name,
    string email,
    string phone)
{
    return CustomerRepository::createCustomer(
        name,
        email,
        phone);
}

std::vector<Customer> UserService::listCustomers()
{
    return CustomerRepository::findAll();
}

Customer UserService::getCustomerById(int id)
{
    return CustomerRepository::findById(id);
}

Customer UserService::updateCustomer(
    int id,
    string name,
    string email,
    string phone,
    int loyaltyPoints)
{
    return CustomerRepository::updateCustomer(
        id,
        name,
        email,
        phone,
        loyaltyPoints);
}

void UserService::deleteCustomer(int id)
{
    CustomerRepository::deleteCustomer(id);
}
