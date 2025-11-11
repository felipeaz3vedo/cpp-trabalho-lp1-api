#pragma once

#include <drogon/HttpController.h>

class ReservationController : public drogon::HttpController<ReservationController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(ReservationController::listReservations,  "/reservations",     drogon::Get);
    ADD_METHOD_TO(ReservationController::createReservation, "/reservations",     drogon::Post);
    ADD_METHOD_TO(ReservationController::getReservation,    "/reservations/{1}", drogon::Get);
    ADD_METHOD_TO(ReservationController::updateReservation, "/reservations/{1}", drogon::Put);
    ADD_METHOD_TO(ReservationController::deleteReservation, "/reservations/{1}", drogon::Delete);
    METHOD_LIST_END

    void listReservations(const drogon::HttpRequestPtr&,
                          std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void createReservation(const drogon::HttpRequestPtr&,
                           std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void getReservation(const drogon::HttpRequestPtr&,
                        std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                        int id);

    void updateReservation(const drogon::HttpRequestPtr&,
                           std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                           int id);

    void deleteReservation(const drogon::HttpRequestPtr&,
                           std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                           int id);
};
