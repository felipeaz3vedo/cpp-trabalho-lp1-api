#pragma once

#include <drogon/HttpController.h>

class TableController : public drogon::HttpController<TableController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TableController::listTables,   "/tables",     drogon::Get);
    ADD_METHOD_TO(TableController::createTable,  "/tables",     drogon::Post);
    ADD_METHOD_TO(TableController::getTable,     "/tables/{1}", drogon::Get);
    ADD_METHOD_TO(TableController::updateTable,  "/tables/{1}", drogon::Put);
    ADD_METHOD_TO(TableController::deleteTable,  "/tables/{1}", drogon::Delete);
    METHOD_LIST_END

    void listTables(const drogon::HttpRequestPtr&,
                    std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void createTable(const drogon::HttpRequestPtr&,
                     std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void getTable(const drogon::HttpRequestPtr&,
                  std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                  int id);

    void updateTable(const drogon::HttpRequestPtr&,
                     std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                     int id);

    void deleteTable(const drogon::HttpRequestPtr&,
                     std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                     int id);
};
