#pragma once

#include <drogon/HttpController.h>

class SettingController : public drogon::HttpController<SettingController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(SettingController::importSettingsFromCsv,
                  "/settings/import",
                  drogon::Post);

    ADD_METHOD_TO(SettingController::listSettings,
                  "/settings",
                  drogon::Get);

    ADD_METHOD_TO(SettingController::createSetting,
                  "/settings",
                  drogon::Post);

    ADD_METHOD_TO(SettingController::updateSetting,
                  "/settings/{1}",
                  drogon::Put);

    ADD_METHOD_TO(SettingController::deleteSetting,
                  "/settings/{1}",
                  drogon::Delete);
    METHOD_LIST_END

    void importSettingsFromCsv(const drogon::HttpRequestPtr&,
                               std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void listSettings(const drogon::HttpRequestPtr&,
                      std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void createSetting(const drogon::HttpRequestPtr&,
                       std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void updateSetting(const drogon::HttpRequestPtr&,
                       std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                       const std::string& key);

    void deleteSetting(const drogon::HttpRequestPtr&,
                       std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                       const std::string& key);
};
