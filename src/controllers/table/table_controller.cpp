#include "controllers/table/table_controller.h"
#include "services/table/table_service.h"
#include "shared/dtos/table/table_request_dto.h"
#include "shared/dtos/table/table_response_dto.h"
#include "shared/helpers/http_response_helper.h"
#include "shared/exceptions/validation_exception.h"

#include <json/json.h>
#include <vector>

using drogon::HttpRequestPtr;
using drogon::HttpResponsePtr;
using HttpHelper::handleRequest;
using std::vector;

void TableController::listTables(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        vector<Table> tables = TableService::listTables();

        Json::Value body(Json::arrayValue);
        for (Table table : tables)
        {
            TableResponseDto dto = TableResponseDto::fromModel(table);
            body.append(dto.toJson());
        }

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void TableController::createTable(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();

        if (!json)
        {
            throw ValidationException("Invalid JSON body.");
        }

        TableRequestDto dtoReq = TableRequestDto::fromJson(*json);

        Table table = TableService::createTable(
            dtoReq.number,
            dtoReq.capacity,
            dtoReq.available
        );

        TableResponseDto dtoResp = TableResponseDto::fromModel(table);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        resp->setStatusCode(drogon::k201Created);
        cb(resp);
    });
}

void TableController::getTable(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        Table table = TableService::getTableById(id);

        TableResponseDto dto = TableResponseDto::fromModel(table);
        Json::Value body = dto.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void TableController::updateTable(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();

        if (!json)
        {
            throw ValidationException("Invalid JSON body.");
        }

        TableRequestDto dtoReq = TableRequestDto::fromJson(*json);

        Table table = TableService::updateTable(
            id,
            dtoReq.number,
            dtoReq.capacity,
            dtoReq.available
        );

        TableResponseDto dtoResp = TableResponseDto::fromModel(table);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void TableController::deleteTable(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        TableService::deleteTable(id);

        HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k204NoContent);
        cb(resp);
    });
}
