#include "controllers/category/category_controller.h"
#include "services/category/category_service.h"
#include "shared/dtos/category/category_request_dto.h"
#include "shared/dtos/category/category_response_dto.h"
#include "shared/helpers/http_response_helper.h"
#include "shared/exceptions/bad_request_exception.h"

#include <json/json.h>
#include <vector>

using drogon::HttpRequestPtr;
using drogon::HttpResponsePtr;
using HttpHelper::handleRequest;
using std::vector;

void CategoryController::listCategories(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        vector<Category> categories = CategoryService::listCategories();

        Json::Value body(Json::arrayValue);
        for (const Category& category : categories)
        {
            CategoryResponseDto dto = CategoryResponseDto::fromModel(category);
            body.append(dto.toJson());
        }

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void CategoryController::createCategory(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();
        if (!json)
        {
            throw BadRequestException("Invalid JSON body.");
        }

        CategoryRequestDto dtoReq = CategoryRequestDto::fromJson(*json);

        Category category = CategoryService::createCategory(
            dtoReq.name,
            dtoReq.description,
            dtoReq.active);

        CategoryResponseDto dtoResp = CategoryResponseDto::fromModel(category);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        resp->setStatusCode(drogon::k201Created);
        cb(resp);
    });
}

void CategoryController::getCategory(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        Category category = CategoryService::getCategoryById(id);

        CategoryResponseDto dto = CategoryResponseDto::fromModel(category);
        Json::Value body = dto.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void CategoryController::updateCategory(
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

        CategoryRequestDto dtoReq = CategoryRequestDto::fromJson(*json);

        Category category = CategoryService::updateCategory(
            id,
            dtoReq.name,
            dtoReq.description,
            dtoReq.active);

        CategoryResponseDto dtoResp = CategoryResponseDto::fromModel(category);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void CategoryController::deleteCategory(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        CategoryService::deleteCategory(id);

        HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k204NoContent);
        cb(resp);
    });
}
