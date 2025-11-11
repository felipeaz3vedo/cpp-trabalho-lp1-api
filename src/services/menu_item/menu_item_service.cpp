#include "services/menu_item/menu_item_service.h"
#include "repositories/menu_item/menu_item_repository.h"
#include "repositories/order/order_repository.h"
#include "repositories/order_menu_item/order_menu_item_repository.h"
#include "shared/exceptions/business_exception.h"

using std::string;
using std::vector;

namespace {
    void ensureNotAlreadyInactive(const MenuItem& item)
    {
        if (!item.isActive())
        {
            throw BusinessException("Menu item is already inactive.");
        }
    }

    void ensureMenuItemNotUsedInOpenOrders(int menuItemId)
    {
        vector<Order> orders = OrderRepository::findAll();

        for (const Order& order : orders)
        {
            if (order.isClosed())
            {
                continue;
            }

            vector<OrderMenuItem> items =
                OrderMenuItemRepository::findByOrderId(order.getId());

            for (const OrderMenuItem& line : items)
            {
                if (line.getMenuItemId() == menuItemId)
                {
                    throw BusinessException(
                        "Cannot delete menu item that is used in open orders.");
                }
            }
        }
    }
}

MenuItem MenuItemService::createMenuItem(
    string name,
    string description,
    double price,
    bool active)
{
    return MenuItemRepository::createMenuItem(
        name,
        description,
        price,
        active
    );
}

vector<MenuItem> MenuItemService::listMenuItems()
{
    return MenuItemRepository::findAll();
}

MenuItem MenuItemService::getMenuItemById(int id)
{
    return MenuItemRepository::findById(id);
}

MenuItem MenuItemService::updateMenuItem(
    int id,
    string name,
    string description,
    double price,
    bool active)
{
    return MenuItemRepository::updateMenuItem(
        id,
        name,
        description,
        price,
        active
    );}

void MenuItemService::deleteMenuItem(int id)
{
    MenuItem item = MenuItemRepository::findById(id);

    ensureNotAlreadyInactive(item);

    ensureMenuItemNotUsedInOpenOrders(id);

    MenuItemRepository::deleteMenuItem(id);
}
