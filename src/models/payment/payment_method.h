#pragma once

#include <string>
#include "shared/enums/payment_type.h"

using std::string;

class PaymentMethod {
public:
    PaymentMethod(PaymentType type);

    virtual ~PaymentMethod();

    PaymentType getType() const;

    virtual string getMethodName() const = 0;

    virtual double calculateFee(double amount) const = 0;

protected:
    PaymentType type;
};
