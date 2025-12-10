#pragma once

#include <drogon/HttpController.h>

class CategoryController : public drogon::HttpController<CategoryController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(CategoryController::listCategories,
                  "/categories",
                  drogon::Get);

    ADD_METHOD_TO(CategoryController::createCategory,
                  "/categories",
                  drogon::Post);

    ADD_METHOD_TO(CategoryController::getCategory,
                  "/categories/{1}",
                  drogon::Get);

    ADD_METHOD_TO(CategoryController::updateCategory,
                  "/categories/{1}",
                  drogon::Put);

    ADD_METHOD_TO(CategoryController::deleteCategory,
                  "/categories/{1}",
                  drogon::Delete);
    METHOD_LIST_END

    void listCategories(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void createCategory(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void getCategory(const drogon::HttpRequestPtr&,
                     std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                     int id);

    void updateCategory(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                        int id);

    void deleteCategory(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                        int id);
};
