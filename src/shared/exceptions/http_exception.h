#pragma once

#include <stdexcept>
#include <string>

using std::string;

class HttpException : public std::runtime_error {
public:
    HttpException(int statusCode, string message)
        : std::runtime_error(message.c_str())
    {
        this->statusCode = statusCode;
    }

    int getStatusCode() const {
        return statusCode;
    }

private:
    int statusCode;
};