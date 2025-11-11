#include "shared/helpers/payment_type_helper.h"
#include "shared/exceptions/validation_exception.h"

PaymentType PaymentTypeHelper::fromString(string value)
{
    if (value == "CASH") {
        return PaymentType::CASH;
    }

    if (value == "CARD") {
        return PaymentType::CARD;
    }

    throw ValidationException("Invalid payment type: " + value);
}

string PaymentTypeHelper::toString(PaymentType type)
{
    switch (type) {
        case PaymentType::CASH:
            return "CASH";
        case PaymentType::CARD:
            return "CARD";
        default:
            throw ValidationException("Invalid PaymentType enum value.");
    }
}
