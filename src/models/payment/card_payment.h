#pragma once

#include <string>
#include "models/payment/payment_method.h"

using std::string;

class CardPayment : public PaymentMethod {
public:
    CardPayment(
        string cardBrand,
        string last4Digits,
        double percentageFee = 0.025,
        double fixedFee = 0.0
    );

    string getCardBrand() const;
    string getLast4Digits() const;

    string getMethodName() const override;

    double calculateFee(double amount) const override;

private:
    string cardBrand;
    string last4Digits;
    double percentageFee;
    double fixedFee;
};
