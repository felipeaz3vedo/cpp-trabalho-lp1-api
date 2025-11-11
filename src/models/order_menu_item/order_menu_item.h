#pragma once

#include "shared/exceptions/validation_exception.h"

class OrderMenuItem {
public:
    OrderMenuItem(
        int id,
        int orderId,
        int menuItemId,
        int quantity,
        double unitPrice
    );

    int getId() const;
    int getOrderId() const;
    void setOrderId(int orderId);
    int getMenuItemId() const;
    void setMenuItemId(int menuItemId);
    int getQuantity() const;
    void setQuantity(int quantity);
    double getUnitPrice() const;
    void setUnitPrice(double unitPrice);
    double getTotalPrice() const;

private:
    int id;
    int orderId;
    int menuItemId;
    int quantity;
    double unitPrice;

    void validate();
    void validateQuantity();
    void validateUnitPrice();
};
