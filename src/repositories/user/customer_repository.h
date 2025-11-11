#pragma once

#include <vector>
#include <string>
#include "models/user/customer.h"

using std::string;

class CustomerRepository {
public:
    static Customer createCustomer(
        string name,
        string email,
        string phone);

    static std::vector<Customer> findAll();

    static Customer findById(int id);

    static Customer updateCustomer(
        int id,
        string name,
        string email,
        string phone,
        int loyaltyPoints);

    static void deleteCustomer(int id);

private:
    static std::vector<Customer> customers;
    static int nextId;
};
