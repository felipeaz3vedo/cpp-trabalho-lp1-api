#pragma once

#include <string>
#include "models/payment/payment_method.h"

using std::string;

class CashPayment : public PaymentMethod {
public:
    CashPayment();

    string getMethodName() const override;

    double calculateFee(double amount) const override;
};
