#pragma once

#include "shared/exceptions/http_exception.h"

class BadRequestException : public HttpException {
public:
    explicit BadRequestException(string message)
        : HttpException(400, message)
    {
    }
};