#pragma once

#include <string>
#include "shared/enums/payment_type.h"

using std::string;

namespace PaymentTypeHelper {
    PaymentType fromString(string value);
    string toString(PaymentType type);
}
