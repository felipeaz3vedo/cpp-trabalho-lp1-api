#include "controllers/reservation/reservation_controller.h"
#include "services/reservation/reservation_service.h"
#include "shared/dtos/reservation/reservation_request_dto.h"
#include "shared/dtos/reservation/reservation_response_dto.h"
#include "shared/helpers/http_response_helper.h"
#include "shared/exceptions/validation_exception.h"

#include <json/json.h>
#include <vector>

using drogon::HttpRequestPtr;
using drogon::HttpResponsePtr;
using HttpHelper::handleRequest;
using std::vector;

void ReservationController::listReservations(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        vector<Reservation> reservations = ReservationService::listReservations();

        Json::Value body(Json::arrayValue);
        for (Reservation r : reservations)
        {
            ReservationResponseDto dto = ReservationResponseDto::fromModel(r);
            body.append(dto.toJson());
        }

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void ReservationController::createReservation(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    handleRequest(cb, [&]() {
        auto json = req->getJsonObject();

        if (!json)
        {
            throw ValidationException("Invalid JSON body.");
        }

        ReservationRequestDto dtoReq = ReservationRequestDto::fromJson(*json);

        Reservation r = ReservationService::createReservation(
            dtoReq.customerId,
            dtoReq.tableId,
            dtoReq.startDateTime,
            dtoReq.endDateTime,
            dtoReq.notes,
            dtoReq.active
        );

        ReservationResponseDto dtoResp = ReservationResponseDto::fromModel(r);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        resp->setStatusCode(drogon::k201Created);
        cb(resp);
    });
}

void ReservationController::getReservation(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        Reservation r = ReservationService::getReservationById(id);

        ReservationResponseDto dto = ReservationResponseDto::fromModel(r);
        Json::Value body = dto.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void ReservationController::updateReservation(
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

        ReservationRequestDto dtoReq = ReservationRequestDto::fromJson(*json);

        Reservation r = ReservationService::updateReservation(
            id,
            dtoReq.customerId,
            dtoReq.tableId,
            dtoReq.startDateTime,
            dtoReq.endDateTime,
            dtoReq.notes,
            dtoReq.active
        );

        ReservationResponseDto dtoResp = ReservationResponseDto::fromModel(r);
        Json::Value body = dtoResp.toJson();

        HttpResponsePtr resp = drogon::HttpResponse::newHttpJsonResponse(body);
        cb(resp);
    });
}

void ReservationController::deleteReservation(
    const HttpRequestPtr&,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id)
{
    handleRequest(cb, [&]() {
        ReservationService::deleteReservation(id);

        HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k204NoContent);
        cb(resp);
    });
}
