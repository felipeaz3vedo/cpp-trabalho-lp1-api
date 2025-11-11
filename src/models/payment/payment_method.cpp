#include "models/payment/payment_method.h"

PaymentMethod::PaymentMethod(PaymentType type)
{
    this->type = type;
}

PaymentMethod::~PaymentMethod() = default;

PaymentType PaymentMethod::getType() const
{
    return this->type;
}
