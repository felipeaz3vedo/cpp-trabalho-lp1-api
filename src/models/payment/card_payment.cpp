#include "models/payment/card_payment.h"

CardPayment::CardPayment(
    string cardBrand,
    string last4Digits,
    double percentageFee,
    double fixedFee)
    : PaymentMethod(PaymentType::CARD)
{
    this->cardBrand = cardBrand;
    this->last4Digits = last4Digits;
    this->percentageFee = percentageFee;
    this->fixedFee = fixedFee;
}

string CardPayment::getCardBrand() const
{
    return this->cardBrand;
}

string CardPayment::getLast4Digits() const
{
    return this->last4Digits;
}

string CardPayment::getMethodName() const
{
    return "Card " + this->cardBrand;
}

double CardPayment::calculateFee(double amount) const
{
    return amount * this->percentageFee + this->fixedFee;
}
