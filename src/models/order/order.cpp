#include "models/order/order.h"

Order::Order(
    int id,
    int tableId,
    int waiterId,
    PaymentType paymentType,
    optional<int> customerId,
    optional<int> employeeId)
{
    this->id = id;
    this->tableId = tableId;
    this->waiterId = waiterId;
    this->paymentType = paymentType;
    this->customerId = customerId;
    this->employeeId = employeeId;
    this->subtotal = 0.0;
    this->discount = 0.0;
    this->fee = 0.0;
    this->total = 0.0;
    this->closed = false;

    this->validateBasic();
    this->validateTotals();
}

int Order::getId() const
{
    return this->id;
}

bool Order::hasCustomer() const
{
    return this->customerId.has_value();
}

optional<int> Order::getCustomerId() const
{
    return this->customerId;
}

void Order::setCustomerId(int customerId)
{
    this->customerId = customerId;
    this->validateAssociation();
}

void Order::clearCustomer()
{
    this->customerId.reset();
}

bool Order::hasEmployee() const
{
    return this->employeeId.has_value();
}

optional<int> Order::getEmployeeId() const
{
    return this->employeeId;
}

void Order::setEmployeeId(int employeeId)
{
    this->employeeId = employeeId;
    this->validateAssociation();
}

void Order::clearEmployee()
{
    this->employeeId.reset();
}

int Order::getWaiterId() const
{
    return this->waiterId;
}

void Order::setWaiterId(int waiterId)
{
    this->waiterId = waiterId;
    this->validateBasic();
}

int Order::getTableId() const
{
    return this->tableId;
}

void Order::setTableId(int tableId)
{
    this->tableId = tableId;
    this->validateBasic();
}

PaymentType Order::getPaymentType() const
{
    return this->paymentType;
}

void Order::setPaymentType(PaymentType paymentType)
{
    this->paymentType = paymentType;
}

double Order::getSubtotal() const
{
    return this->subtotal;
}

void Order::setSubtotal(double subtotal)
{
    this->subtotal = subtotal;
    this->validateTotals();
}

double Order::getDiscount() const
{
    return this->discount;
}

void Order::setDiscount(double discount)
{
    this->discount = discount;
    this->validateTotals();
}

double Order::getFee() const
{
    return this->fee;
}

void Order::setFee(double fee)
{
    this->fee = fee;
    this->validateTotals();
}

double Order::getTotal() const
{
    return this->total;
}

void Order::setTotal(double total)
{
    this->total = total;
    this->validateTotals();
}

bool Order::isClosed() const
{
    return this->closed;
}

void Order::setClosed(bool closed)
{
    this->closed = closed;
}

int Order::calculateLoyaltyPoints() const
{
    double effectiveAmount = this->total;

    if (effectiveAmount < 0.0) {
        effectiveAmount = 0.0;
    }

    int points = (int)(effectiveAmount / 10.0);
    return points;
}

void Order::validateBasic()
{
    if (this->tableId <= 0) {
        throw ValidationException("Order 'tableId' must be greater than zero.");
    }

    if (this->waiterId <= 0) {
        throw ValidationException("Order 'waiterId' must be greater than zero.");
    }

    this->validateAssociation();
}

void Order::validateTotals()
{
    if (this->subtotal < 0.0) {
        this->subtotal = 0.0;
    }

    if (this->discount < 0.0) {
        this->discount = 0.0;
    }

    if (this->fee < 0.0) {
        this->fee = 0.0;
    }
}

void Order::validateAssociation()
{
    if (this->customerId.has_value() && this->employeeId.has_value()) {
        throw ValidationException(
            "Order cannot be associated with both a customer and an employee for discount."
        );
    }
}
