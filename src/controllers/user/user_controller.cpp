#include "controllers/user/user_controller.h"
#include "services/user/user_service.h"
#include "shared/helpers/http_response_helper.h"
#include "shared/helpers/employee_role_helper.h"
#include "shared/dtos/user/employee_request_dto.h"
#include "shared/dtos/user/customer_request_dto.h"
#include "shared/dtos/user/employee_response_dto.h"
#include "shared/dtos/user/customer_response_dto.h"
#include "shared/exceptions/bad_request_exception.h"

#include <json/json.h>
#include <vector>

using drogon::HttpRequestPtr;
using drogon::HttpResponse;
using drogon::HttpResponsePtr;
using HttpHelper::makeErrorResponse;
using std::string;
using std::vector;

void UserController::listEmployees(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    HttpHelper::handleRequest(cb, [&]() {
        vector<Employee> employees = UserService::listEmployees();

        Json::Value body(Json::arrayValue);
        for (Employee e : employees) {
            EmployeeResponseDto dto = EmployeeResponseDto::fromModel(e);
            body.append(dto.toJson());
        }

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void UserController::createEmployee(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    HttpHelper::handleRequest(cb, [&]() {
        auto json = req->getJsonObject();

        if (!json) {
            throw BadRequestException("invalid JSON");
        }

        EmployeeRequestDto dtoReq = EmployeeRequestDto::fromJson(*json);

        Employee e = UserService::createEmployee(
            dtoReq.name,
            dtoReq.email,
            dtoReq.cpf,
            dtoReq.role
        );

        EmployeeResponseDto dtoResp = EmployeeResponseDto::fromModel(e);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        resp->setStatusCode(drogon::k201Created);
        cb(resp);
    });
}

void UserController::getEmployee(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    HttpHelper::handleRequest(cb, [&]() {
        Employee e = UserService::getEmployeeById(id);

        EmployeeResponseDto dto = EmployeeResponseDto::fromModel(e);
        Json::Value body = dto.toJson();

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void UserController::updateEmployee(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    HttpHelper::handleRequest(cb, [&]() {
        auto json = req->getJsonObject();

        if (!json) {
            throw BadRequestException("Invalid JSON body.");
        }

        EmployeeRequestDto dtoReq = EmployeeRequestDto::fromJson(*json);

        Employee e = UserService::updateEmployee(
            id,
            dtoReq.name,
            dtoReq.email,
            dtoReq.cpf,
            dtoReq.role,
            dtoReq.active
        );

        EmployeeResponseDto dtoResp = EmployeeResponseDto::fromModel(e);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void UserController::deleteEmployee(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    HttpHelper::handleRequest(cb, [&]() {
        UserService::deleteEmployee(id);

        HttpResponsePtr resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k204NoContent);
        cb(resp);
    });
}

void UserController::listCustomers(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    HttpHelper::handleRequest(cb, [&]() {
        vector<Customer> customers = UserService::listCustomers();

        Json::Value body(Json::arrayValue);
        for (Customer c : customers) {
            CustomerResponseDto dto = CustomerResponseDto::fromModel(c);
            body.append(dto.toJson());
        }

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void UserController::createCustomer(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    HttpHelper::handleRequest(cb, [&]() {
        auto json = req->getJsonObject();

        if (!json) {
            throw BadRequestException("Invalid JSON body.");
        }

        CustomerRequestDto dtoReq = CustomerRequestDto::fromJson(*json);

        Customer c = UserService::createCustomer(
            dtoReq.name,
            dtoReq.email,
            dtoReq.phone
        );

        CustomerResponseDto dtoResp = CustomerResponseDto::fromModel(c);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        resp->setStatusCode(drogon::k201Created);
        cb(resp);
    });
}

void UserController::getCustomer(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id) 
{
    HttpHelper::handleRequest(cb, [&]() {
        Customer c = UserService::getCustomerById(id);

        CustomerResponseDto dto = CustomerResponseDto::fromModel(c);
        Json::Value body = dto.toJson();

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void UserController::updateCustomer(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    HttpHelper::handleRequest(cb, [&]() {
        auto json = req->getJsonObject();

        if (!json) {
           throw BadRequestException("Invalid JSON body.");
        }

        CustomerRequestDto dtoReq = CustomerRequestDto::fromJson(*json);

        Customer c = UserService::updateCustomer(
            id,
            dtoReq.name,
            dtoReq.email,
            dtoReq.phone,
            dtoReq.loyaltyPoints
        );

        CustomerResponseDto dtoResp = CustomerResponseDto::fromModel(c);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void UserController::deleteCustomer(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    HttpHelper::handleRequest(cb, [&]() {
        UserService::deleteCustomer(id);

        HttpResponsePtr resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k204NoContent);
        cb(resp);
    });
}
