#include "repositories/order_menu_item/order_menu_item_repository.h"
#include "shared/exceptions/not_found_exception.h"

vector<OrderMenuItem> OrderMenuItemRepository::orderItems = {};
int OrderMenuItemRepository::nextId = 1;

OrderMenuItem OrderMenuItemRepository::createOrderMenuItem(
    int orderId,
    int menuItemId,
    int quantity,
    double unitPrice)
{
    OrderMenuItem item(
        nextId,
        orderId,
        menuItemId,
        quantity,
        unitPrice
    );

    orderItems.push_back(item);
    nextId++;

    return item;
}

vector<OrderMenuItem> OrderMenuItemRepository::findAll()
{
    return orderItems;
}

vector<OrderMenuItem> OrderMenuItemRepository::findByOrderId(int orderId)
{
    vector<OrderMenuItem> result;

    for (const OrderMenuItem& item : orderItems)
    {
        if (item.getOrderId() == orderId)
        {
            result.push_back(item);
        }
    }

    return result;
}

OrderMenuItem OrderMenuItemRepository::findByOrderIdAndMenuItemId(
    int orderId,
    int menuItemId)
{
    for (const OrderMenuItem& item : orderItems)
    {
        if (item.getOrderId() == orderId &&
            item.getMenuItemId() == menuItemId)
        {
            return item;
        }
    }

    throw NotFoundException("Order menu item not found for this order and menu item.");
}

OrderMenuItem OrderMenuItemRepository::updateOrderMenuItem(
    int id,
    int quantity,
    double unitPrice)
{
    for (OrderMenuItem& item : orderItems)
    {
        if (item.getId() == id)
        {
            item.setQuantity(quantity);
            item.setUnitPrice(unitPrice);
            return item;
        }
    }

    throw NotFoundException("Order menu item not found.");
}

void OrderMenuItemRepository::deleteOrderMenuItem(int id)
{
    for (size_t i = 0; i < orderItems.size(); )
    {
        if (orderItems[i].getId() == id)
        {
            orderItems.erase(orderItems.begin() + static_cast<long>(i));
            return;
        }
        else
        {
            ++i;
        }
    }

    throw NotFoundException("Order menu item not found.");
}

void OrderMenuItemRepository::deleteAllByOrderId(int orderId)
{
    for (size_t i = 0; i < orderItems.size(); )
    {
        if (orderItems[i].getOrderId() == orderId)
        {
            orderItems.erase(orderItems.begin() + static_cast<long>(i));
        }
        else
        {
            ++i;
        }
    }
}
