#include "controllers/order/order_controller.h"
#include "services/order/order_service.h"
#include "shared/dtos/order/order_request_dto.h"
#include "shared/dtos/order/order_response_dto.h"
#include "shared/dtos/order_item/order_item_request_dto.h"
#include "shared/dtos/order_item/order_item_response_dto.h"
#include "shared/helpers/http_response_helper.h"
#include "shared/exceptions/validation_exception.h"
#include "shared/exceptions/bad_request_exception.h"

#include <json/json.h>
#include <vector>
#include <optional>

using drogon::HttpRequestPtr;
using drogon::HttpResponsePtr;
using drogon::HttpResponse;
using HttpHelper::handleRequest;
using std::vector;
using std::string;
using std::optional;

void OrderController::listOrders(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        vector<Order> orders = OrderService::listOrders();

        Json::Value body(Json::arrayValue);
        for (Order o : orders) {
            OrderResponseDto dto = OrderResponseDto::fromModel(o);
            body.append(dto.toJson());
        }

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void OrderController::createOrder(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();
        if (!json) {
            throw BadRequestException("Invalid JSON body.");
        }

        OrderRequestDto dtoReq = OrderRequestDto::fromJsonForCreate(*json);

        Order order = OrderService::createOrder(
            dtoReq.tableId,
            dtoReq.waiterId,
            dtoReq.paymentType,
            dtoReq.customerId,
            dtoReq.employeeId
        );

        OrderResponseDto dtoResp = OrderResponseDto::fromModel(order);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        resp->setStatusCode(drogon::k201Created);
        cb(resp);
    });
}

void OrderController::getOrder(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        Order order = OrderService::getOrderById(id);

        OrderResponseDto dto = OrderResponseDto::fromModel(order);
        Json::Value body = dto.toJson();

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void OrderController::updateOrder(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();
        if (!json) {
            throw BadRequestException("Invalid JSON body.");
        }

        OrderRequestDto dtoReq = OrderRequestDto::fromJsonForUpdate(*json);

        Order order = OrderService::updateOrder(
            id,
            dtoReq.tableId,
            dtoReq.waiterId,
            dtoReq.paymentType,
            dtoReq.customerId,
            dtoReq.employeeId,
            dtoReq.closed
        );

        OrderResponseDto dtoResp = OrderResponseDto::fromModel(order);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void OrderController::deleteOrder(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        OrderService::deleteOrder(id);

        HttpResponsePtr resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k204NoContent);
        cb(resp);
    });
}

void OrderController::closeOrder(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        Order order = OrderService::closeOrder(id);

        OrderResponseDto dto = OrderResponseDto::fromModel(order);
        Json::Value body = dto.toJson();

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void OrderController::listOrderItems(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int orderId)
{
    handleRequest(cb, [&]() {
        vector<OrderMenuItem> items = OrderService::listItemsByOrder(orderId);

        Json::Value body(Json::arrayValue);
        for (OrderMenuItem item : items) {
            OrderItemResponseDto dto = OrderItemResponseDto::fromModel(item);
            body.append(dto.toJson());
        }

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void OrderController::addOrderItem(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int orderId)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();
        if (!json) {
            throw BadRequestException("Invalid JSON body.");
        }

        OrderItemRequestDto dtoReq = OrderItemRequestDto::fromJsonForCreate(*json);

        OrderMenuItem item = OrderService::addItemToOrder(
            orderId,
            dtoReq.menuItemId,
            dtoReq.quantity
        );

        OrderItemResponseDto dtoResp = OrderItemResponseDto::fromModel(item);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(body);
        resp->setStatusCode(drogon::k201Created);
        cb(resp);
    });
}

void OrderController::updateOrderItemQtd(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int orderId,
    int menuItemId)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();
        if (!json) {
            throw BadRequestException("Invalid JSON body.");
        }

        OrderItemRequestDto dtoReq = OrderItemRequestDto::fromJsonForUpdate(*json);

        OrderMenuItem item = OrderService::updateOrderItemQtd(
            orderId,
            menuItemId,
            dtoReq.quantity
        );

        OrderItemResponseDto dtoResp = OrderItemResponseDto::fromModel(item);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void OrderController::deleteOrderItem(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int orderId,
    int menuItemId)
{
    handleRequest(cb, [&]() {
        OrderService::removeOrderItem(orderId, menuItemId);

        HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k204NoContent);
        cb(resp);
    });
}
