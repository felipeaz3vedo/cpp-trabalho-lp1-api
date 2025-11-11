#include "repositories/user/employee_repository.h"
#include "shared/exceptions/not_found_exception.h"

std::vector<Employee> EmployeeRepository::employees = std::vector<Employee>();
int EmployeeRepository::nextId = 1;

Employee EmployeeRepository::createEmployee(
    string name,
    string email,
    string document,
    EmployeeRole role)
{
    Employee e(nextId, name, email, document, role, true);
    employees.push_back(e);
    nextId++;
    return e;
}

std::vector<Employee> EmployeeRepository::findAll()
{
    return employees;
}

Employee EmployeeRepository::findById(int id)
{
    for (Employee& e : employees) {
        if (e.getId() == id) {
            return e;
        }
    }

    throw NotFoundException("Employee não encontrado");
}

Employee EmployeeRepository::updateEmployee(
    int id,
    string name,
    string email,
    string cpf,
    EmployeeRole role,
    bool active)
{
    for (Employee& e : employees) {
        if (e.getId() == id) {
            e.setName(name);
            e.setEmail(email);
            e.setCpf(cpf);
            e.setRole(role);
            e.setActive(active);
            return e;
        }
    }
    
    throw NotFoundException("Employee not found");
}

void EmployeeRepository::deleteEmployee(int id)
{
    for (std::size_t i = 0; i < employees.size(); i++) {
        if (employees[i].getId() == id) {
            employees.erase(employees.begin() + (long)i);
            return;
        }
    }

    throw NotFoundException("Employee not found");
}
