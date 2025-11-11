#pragma once

#include <optional>
#include <ostream>
#include "shared/enums/payment_type.h"
#include "shared/exceptions/validation_exception.h"

using std::optional;

class Order {
public:
    Order(
        int id,
        int tableId,
        int waiterId,
        PaymentType paymentType,
        optional<int> customerId = optional<int>(),
        optional<int> employeeId = optional<int>());

    int getId() const;
    bool hasCustomer() const;
    optional<int> getCustomerId() const;
    void setCustomerId(int customerId);
    void clearCustomer();
    bool hasEmployee() const;
    optional<int> getEmployeeId() const;
    void setEmployeeId(int employeeId);
    void clearEmployee();
    int getWaiterId() const;
    void setWaiterId(int waiterId);
    int getTableId() const;
    void setTableId(int tableId);
    PaymentType getPaymentType() const;
    void setPaymentType(PaymentType paymentType);
    double getSubtotal() const;
    void setSubtotal(double subtotal);
    double getDiscount() const;
    void setDiscount(double discount);
    double getFee() const;
    void setFee(double fee);
    double getTotal() const;
    void setTotal(double total);
    bool isClosed() const;
    void setClosed(bool closed);

    int calculateLoyaltyPoints() const;

private:
    int id;
    int tableId;
    int waiterId;
    optional<int> customerId;
    optional<int> employeeId;
    PaymentType paymentType;
    double subtotal;
    double discount;
    double fee;
    double total;
    bool closed;

    void validateBasic();
    void validateTotals();
    void validateAssociation();
};
