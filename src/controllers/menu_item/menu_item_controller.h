#pragma once

#include <drogon/HttpController.h>

class MenuItemController : public drogon::HttpController<MenuItemController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(MenuItemController::listMenuItems,  "/menu-items",     drogon::Get);
    ADD_METHOD_TO(MenuItemController::createMenuItem, "/menu-items",     drogon::Post);
    ADD_METHOD_TO(MenuItemController::getMenuItem,    "/menu-items/{1}", drogon::Get);
    ADD_METHOD_TO(MenuItemController::updateMenuItem, "/menu-items/{1}", drogon::Put);
    ADD_METHOD_TO(MenuItemController::deleteMenuItem, "/menu-items/{1}", drogon::Delete);
    METHOD_LIST_END

    void listMenuItems(const drogon::HttpRequestPtr&,
                       std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void createMenuItem(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void getMenuItem(const drogon::HttpRequestPtr&,
                     std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                     int id);

    void updateMenuItem(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                        int id);

    void deleteMenuItem(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                        int id);
};
