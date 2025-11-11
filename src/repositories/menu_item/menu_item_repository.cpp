#include "repositories/menu_item/menu_item_repository.h"
#include "shared/exceptions/not_found_exception.h"

std::vector<MenuItem> MenuItemRepository::menuItems = {};
int MenuItemRepository::nextId = 1;

MenuItem MenuItemRepository::createMenuItem(
    string name,
    string description,
    double price,
    bool active)
{
    MenuItem item(
        nextId,
        name,
        description,
        price,
        active
    );

    menuItems.push_back(item);
    nextId++;

    return item;
}

std::vector<MenuItem> MenuItemRepository::findAll()
{
    return menuItems;
}

MenuItem MenuItemRepository::findById(int id)
{
    for (MenuItem item : menuItems)
    {
        if (item.getId() == id)
        {
            return item;
        }
    }

    throw NotFoundException("Menu item not found.");
}

MenuItem MenuItemRepository::updateMenuItem(
    int id,
    string name,
    string description,
    double price,
    bool active)
{
    for (MenuItem& item : menuItems)
    {
        if (item.getId() == id)
        {
            item.setName(name);
            item.setDescription(description);
            item.setPrice(price);
            item.setActive(active);

            return item;
        }
    }

    throw NotFoundException("Menu item not found.");
}

void MenuItemRepository::deleteMenuItem(int id)
{
    for (MenuItem& item : menuItems)
    {
        if (item.getId() == id)
        {
            item.setActive(false);
            return;
        }
    }

    throw NotFoundException("Menu item not found.");
}
