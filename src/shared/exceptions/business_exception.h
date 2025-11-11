#pragma once

#include "shared/exceptions/http_exception.h"

class BusinessException : public HttpException {
public:
    explicit BusinessException(string message)
        : HttpException(422, message)
    {
    }
};