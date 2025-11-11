#pragma once

#include "shared/exceptions/http_exception.h"

class ValidationException : public HttpException {
public:
    explicit ValidationException(string message)
        : HttpException(400, message)
    {
    }
};