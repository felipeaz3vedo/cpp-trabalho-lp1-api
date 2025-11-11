#pragma once

#include <vector>
#include <optional>
#include "models/order/order.h"
#include "shared/enums/payment_type.h"

using std::vector;
using std::optional;

class OrderRepository {
public:
    static Order createOrder(
        int tableId,
        int waiterId,
        PaymentType paymentType,
        optional<int> customerId,
        optional<int> employeeId
    );

    static vector<Order> findAll();

    static Order findById(int id);

    static Order updateOrder(
        int id,
        int tableId,
        int waiterId,
        PaymentType paymentType,
        optional<int> customerId,
        optional<int> employeeId,
        bool closed
    );

    static Order updateTotals(
        int id,
        double subtotal,
        double discount,
        double fee,
        double total
    );

    static void deleteOrder(int id);

private:
    static vector<Order> orders;
    static int nextId;
};
