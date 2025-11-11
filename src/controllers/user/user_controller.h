#pragma once

#include <drogon/HttpController.h>

class UserController : public drogon::HttpController<UserController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::listEmployees,   "/users/employees",      drogon::Get);
    ADD_METHOD_TO(UserController::createEmployee,  "/users/employees",      drogon::Post);
    ADD_METHOD_TO(UserController::getEmployee,     "/users/employees/{1}",  drogon::Get);
    ADD_METHOD_TO(UserController::updateEmployee,  "/users/employees/{1}",  drogon::Put);
    ADD_METHOD_TO(UserController::deleteEmployee,  "/users/employees/{1}",  drogon::Delete);
    
    ADD_METHOD_TO(UserController::listCustomers,   "/users/customers",      drogon::Get);
    ADD_METHOD_TO(UserController::createCustomer,  "/users/customers",      drogon::Post);
    ADD_METHOD_TO(UserController::getCustomer,     "/users/customers/{1}",  drogon::Get);
    ADD_METHOD_TO(UserController::updateCustomer,  "/users/customers/{1}",  drogon::Put);
    ADD_METHOD_TO(UserController::deleteCustomer,  "/users/customers/{1}",  drogon::Delete);
    METHOD_LIST_END

    void listEmployees(const drogon::HttpRequestPtr&,
                       std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void createEmployee(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void getEmployee(const drogon::HttpRequestPtr&,
                     std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                     int id);

    void updateEmployee(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                        int id);

    void deleteEmployee(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                        int id);

    void listCustomers(const drogon::HttpRequestPtr&,
                       std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void createCustomer(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void getCustomer(const drogon::HttpRequestPtr&,
                     std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                     int id);

    void updateCustomer(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                        int id);

    void deleteCustomer(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                        int id);
};
