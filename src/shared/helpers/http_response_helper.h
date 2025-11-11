#pragma once

#include <string>
#include <functional>
#include <json/json.h>
#include <drogon/HttpResponse.h>

#include "shared/exceptions/http_exception.h"

using std::string;
using std::function;
using drogon::HttpResponsePtr;

namespace HttpHelper {

    HttpResponsePtr makeErrorResponse(int code, string message);

    template <typename Func>
    void handleRequest(const function<void(const HttpResponsePtr&)>& cb, Func func) {
        try {
            func();
        } catch (const HttpException& ex) {
            cb(makeErrorResponse(ex.getStatusCode(), ex.what()));
        } catch (const std::exception& ex) {
            cb(makeErrorResponse(500, "Internal server error."));
        }
    }
}