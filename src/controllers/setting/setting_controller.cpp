#include "controllers/setting/setting_controller.h"
#include "services/setting/setting_service.h"
#include "shared/dtos/setting/setting_response_dto.h"
#include "shared/helpers/http_response_helper.h"
#include "shared/exceptions/validation_exception.h"
#include <json/json.h>
#include <drogon/MultiPart.h>

using drogon::HttpRequestPtr;
using drogon::HttpResponsePtr;
using HttpHelper::handleRequest;

void SettingController::importSettingsFromCsv(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        if (req->getContentType() != drogon::CT_MULTIPART_FORM_DATA)
        {
            throw ValidationException("Content-Type must be multipart/form-data with a CSV file.");
        }

        drogon::MultiPartParser parser;
        int parseResult = parser.parse(req);
        if (parseResult != 0)
        {
            throw ValidationException("Failed to parse multipart/form-data request.");
        }

        const auto &files = parser.getFiles();
        if (files.empty())
        {
            throw ValidationException("CSV file is required. Send as multipart/form-data.");
        }

        const auto &file = files[0];

        const char *dataPtr = file.fileData();
        size_t dataLen = file.fileLength();

        std::string csvContent(dataPtr, dataPtr + dataLen);

        if (csvContent.empty())
        {
            throw ValidationException("Uploaded CSV file is empty.");
        }

        auto settings = SettingService::importFromCsv(csvContent);

        Json::Value body(Json::arrayValue);
        for (const auto &setting : settings)
        {
            SettingResponseDto dto = SettingResponseDto::fromModel(setting);
            body.append(dto.toJson());
        }

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        resp->setStatusCode(drogon::k201Created);
        cb(resp);
    });
}

void SettingController::listSettings(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        auto settings = SettingService::listSettings();

        Json::Value body(Json::arrayValue);
        for (const auto &setting : settings)
        {
            SettingResponseDto dto = SettingResponseDto::fromModel(setting);
            body.append(dto.toJson());
        }

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void SettingController::createSetting(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();
        if (!json)
        {
            throw ValidationException("Invalid JSON body.");
        }

        if (!(*json)["key"].isString())
        {
            throw ValidationException("Field 'key' is required and must be a string.");
        }

        if (!(*json)["type"].isString())
        {
            throw ValidationException("Field 'type' is required and must be a string.");
        }

        if (!(*json)["value"].isString())
        {
            throw ValidationException("Field 'value' is required and must be a string.");
        }

        std::string key = (*json)["key"].asString();
        std::string typeName = (*json)["type"].asString();
        std::string value = (*json)["value"].asString();

        Setting setting = SettingService::createSetting(key, typeName, value);

        SettingResponseDto dto = SettingResponseDto::fromModel(setting);
        Json::Value body = dto.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        resp->setStatusCode(drogon::k201Created);
        cb(resp);
    });
}

void SettingController::updateSetting(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb,
    const std::string& key)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();
        if (!json)
        {
            throw ValidationException("Invalid JSON body.");
        }

        if (!(*json)["value"].isString())
        {
            throw ValidationException("Field 'value' is required and must be a string.");
        }

        std::string value = (*json)["value"].asString();

        Setting setting = SettingService::updateSetting(key, value);

        SettingResponseDto dto = SettingResponseDto::fromModel(setting);
        Json::Value body = dto.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void SettingController::deleteSetting(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    const std::string& key)
{
    handleRequest(cb, [&]() {
        SettingService::deleteSetting(key);

        HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k204NoContent);
        cb(resp);
    });
}
