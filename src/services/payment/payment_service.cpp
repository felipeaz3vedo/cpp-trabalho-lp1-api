#include "services/payment/payment_service.h"
#include "models/payment/card_payment.h"
#include "models/payment/cash_payment.h"

double PaymentService::calculateFee(PaymentType type, double amount)
{
    if (amount < 0.0) {
        amount = 0.0;
    }

    switch (type) {
        case PaymentType::CARD: {
            CardPayment card("Generic", "0000");
            return card.calculateFee(amount);
        }
        case PaymentType::CASH:
        default: {
            CashPayment cash;
            return cash.calculateFee(amount);
        }
    }
}

string PaymentService::getMethodName(PaymentType type)
{
    switch (type) {
        case PaymentType::CARD:
            return "CARD";
        case PaymentType::CASH:
            return "CASH";
        default:
            return "UNKNOWN";
    }
}
