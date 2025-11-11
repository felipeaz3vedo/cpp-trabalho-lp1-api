#include "shared/helpers/http_response_helper.h"

HttpResponsePtr HttpHelper::makeErrorResponse(int code, string message)
{
    Json::Value body;
    body["error"] = message;

    auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
    resp->setStatusCode((drogon::HttpStatusCode)code);
    return resp;
}