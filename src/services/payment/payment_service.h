#pragma once

#include <string>
#include "shared/enums/payment_type.h"

using std::string;

class PaymentService {
public:
    static double calculateFee(PaymentType type, double amount);
    static string getMethodName(PaymentType type);
};
