#pragma once

#include <drogon/HttpController.h>

class OrderController : public drogon::HttpController<OrderController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(OrderController::listOrders,  "/orders",             drogon::Get);
    ADD_METHOD_TO(OrderController::createOrder, "/orders",             drogon::Post);
    ADD_METHOD_TO(OrderController::getOrder,    "/orders/{1}",         drogon::Get);
    ADD_METHOD_TO(OrderController::updateOrder, "/orders/{1}",         drogon::Put);
    ADD_METHOD_TO(OrderController::deleteOrder, "/orders/{1}",         drogon::Delete);
    ADD_METHOD_TO(OrderController::closeOrder,  "/orders/{1}/close",   drogon::Post);

    ADD_METHOD_TO(OrderController::listOrderItems,     "/orders/{1}/items",     drogon::Get);
    ADD_METHOD_TO(OrderController::addOrderItem,       "/orders/{1}/items",     drogon::Post);
    ADD_METHOD_TO(OrderController::updateOrderItemQtd, "/orders/{1}/items/{2}", drogon::Put);
    ADD_METHOD_TO(OrderController::deleteOrderItem,    "/orders/{1}/items/{2}", drogon::Delete);
    METHOD_LIST_END

    void listOrders(const drogon::HttpRequestPtr&,
                    std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void createOrder(const drogon::HttpRequestPtr&,
                     std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void getOrder(const drogon::HttpRequestPtr&,
                  std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                  int id);

    void updateOrder(const drogon::HttpRequestPtr&,
                     std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                     int id);

    void deleteOrder(const drogon::HttpRequestPtr&,
                     std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                     int id);

    void closeOrder(const drogon::HttpRequestPtr&,
                    std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                    int id);

    void listOrderItems(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                        int orderId);

    void addOrderItem(const drogon::HttpRequestPtr&,
                      std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                      int orderId);

    void updateOrderItemQtd(const drogon::HttpRequestPtr&,
                            std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                            int orderId,
                            int menuItemId);

    void deleteOrderItem(const drogon::HttpRequestPtr&,
                         std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                         int orderId,
                         int menuItemId);
};
