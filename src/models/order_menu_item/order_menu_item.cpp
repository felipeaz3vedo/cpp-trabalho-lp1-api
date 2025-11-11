#include "models/order_menu_item/order_menu_item.h"

OrderMenuItem::OrderMenuItem(
    int id,
    int orderId,
    int menuItemId,
    int quantity,
    double unitPrice)
{
    this->id = id;
    this->orderId = orderId;
    this->menuItemId = menuItemId;
    this->quantity = quantity;
    this->unitPrice = unitPrice;

    this->validate();
}

int OrderMenuItem::getId() const
{
    return this->id;
}

int OrderMenuItem::getOrderId() const
{
    return this->orderId;
}

void OrderMenuItem::setOrderId(int orderId)
{
    this->orderId = orderId;
}

int OrderMenuItem::getMenuItemId() const
{
    return this->menuItemId;
}

void OrderMenuItem::setMenuItemId(int menuItemId)
{
    this->menuItemId = menuItemId;
}

int OrderMenuItem::getQuantity() const
{
    return this->quantity;
}

void OrderMenuItem::setQuantity(int quantity)
{
    this->quantity = quantity;
    this->validateQuantity();
}

double OrderMenuItem::getUnitPrice() const
{
    return this->unitPrice;
}

void OrderMenuItem::setUnitPrice(double unitPrice)
{
    this->unitPrice = unitPrice;
    this->validateUnitPrice();
}

double OrderMenuItem::getTotalPrice() const
{
    return this->unitPrice * this->quantity;
}

void OrderMenuItem::validate()
{
    this->validateQuantity();
    this->validateUnitPrice();
}

void OrderMenuItem::validateQuantity()
{
    if (this->quantity <= 0) {
        throw ValidationException("OrderMenuItem 'quantity' must be greater than zero.");
    }
}

void OrderMenuItem::validateUnitPrice()
{
    if (this->unitPrice <= 0.0) {
        throw ValidationException("OrderMenuItem 'unitPrice' must be greater than zero.");
    }
}
