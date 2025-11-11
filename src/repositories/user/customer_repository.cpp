#include "repositories/user/customer_repository.h"
#include "shared/exceptions/not_found_exception.h"

std::vector<Customer> CustomerRepository::customers = std::vector<Customer>();
int CustomerRepository::nextId = 1;

Customer CustomerRepository::createCustomer(
    string name,
    string email,
    string phone)
{
    Customer c(nextId, name, email, phone, 0);
    customers.push_back(c);
    nextId++;
    return c;
}

std::vector<Customer> CustomerRepository::findAll()
{
    return customers;
}

Customer CustomerRepository::findById(int id)
{
    for (Customer& c : customers) {
        if (c.getId() == id) {
            return c;
        }
    }

    throw NotFoundException("Customer not found");
}

Customer CustomerRepository::updateCustomer(
    int id,
    string name,
    string email,
    string phone,
    int loyaltyPoints)
{
    for (Customer& c : customers) {
        if (c.getId() == id) {
            c.setName(name);
            c.setEmail(email);
            c.setPhone(phone);
            c.setLoyaltyPoints(loyaltyPoints);
            return c;
        }
    }

    throw NotFoundException("Customer not found");
}

void CustomerRepository::deleteCustomer(int id)
{
    for (std::size_t i = 0; i < customers.size(); i++) {
        if (customers[i].getId() == id) {
            customers.erase(customers.begin() + (long)i);
            return;
        }
    }

    throw NotFoundException("Customer not found");
}
