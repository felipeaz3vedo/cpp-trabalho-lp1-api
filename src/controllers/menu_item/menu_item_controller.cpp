#include "controllers/menu_item/menu_item_controller.h"
#include "services/menu_item/menu_item_service.h"
#include "shared/helpers/http_response_helper.h"
#include "shared/exceptions/bad_request_exception.h"
#include "shared/dtos/menu_item/menu_item_request_dto.h"
#include "shared/dtos/menu_item/menu_item_response_dto.h"

#include <json/json.h>
#include <vector>

using drogon::HttpRequestPtr;
using drogon::HttpResponsePtr;
using HttpHelper::handleRequest;
using std::vector;
using std::string;

void MenuItemController::listMenuItems(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        vector<MenuItem> items = MenuItemService::listMenuItems();

        Json::Value body(Json::arrayValue);
        for (const MenuItem& item : items)
        {
            MenuItemResponseDto dto = MenuItemResponseDto::fromModel(item);
            body.append(dto.toJson());
        }

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void MenuItemController::createMenuItem(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();
        if (!json)
        {
            throw BadRequestException("Invalid JSON body.");
        }

        MenuItemRequestDto dtoReq = MenuItemRequestDto::fromJson(*json);

        MenuItem item = MenuItemService::createMenuItem(
            dtoReq.name,
            dtoReq.description,
            dtoReq.price,
            dtoReq.active
        );

        MenuItemResponseDto dtoResp = MenuItemResponseDto::fromModel(item);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        resp->setStatusCode(drogon::k201Created);
        cb(resp);
    });
}

void MenuItemController::getMenuItem(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        MenuItem item = MenuItemService::getMenuItemById(id);

        MenuItemResponseDto dto = MenuItemResponseDto::fromModel(item);
        Json::Value body = dto.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void MenuItemController::updateMenuItem(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();
        if (!json)
        {
            throw BadRequestException("Invalid JSON body.");
        }

        MenuItemRequestDto dtoReq = MenuItemRequestDto::fromJson(*json);

        MenuItem item = MenuItemService::updateMenuItem(
            id,
            dtoReq.name,
            dtoReq.description,
            dtoReq.price,
            dtoReq.active
        );

        MenuItemResponseDto dtoResp = MenuItemResponseDto::fromModel(item);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void MenuItemController::deleteMenuItem(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        MenuItemService::deleteMenuItem(id);

        HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k204NoContent);
        cb(resp);
    });
}
