#pragma once

#include "shared/exceptions/http_exception.h"

class NotFoundException : public HttpException {
public:
    explicit NotFoundException(string message)
        : HttpException(404, message)
    {
    }
};