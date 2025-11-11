#include "models/payment/cash_payment.h"

CashPayment::CashPayment()
    : PaymentMethod(PaymentType::CASH)
{
}

string CashPayment::getMethodName() const
{
    return "Cash";
}

double CashPayment::calculateFee(double _) const
{
    return 0.0;
}
