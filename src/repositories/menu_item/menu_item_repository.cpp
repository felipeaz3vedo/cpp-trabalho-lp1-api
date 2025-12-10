#include "repositories/menu_item/menu_item_repository.h"
#include "shared/exceptions/not_found_exception.h"

vector<MenuItem> MenuItemRepository::menuItems = {};
int MenuItemRepository::nextId = 1;

MenuItem MenuItemRepository::createMenuItem(
    string name,
    string description,
    double price,
    bool active,
    int categoryId)
{
    MenuItem item(
        nextId,
        name,
        description,
        price,
        active,
        categoryId
    );

    menuItems.push_back(item);
    nextId++;

    return item;
}

vector<MenuItem> MenuItemRepository::findAll()
{
    return menuItems;
}

MenuItem MenuItemRepository::findById(int id)
{
    for (const MenuItem& item : menuItems)
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
    bool active,
    int categoryId)
{
    for (MenuItem& item : menuItems)
    {
        if (item.getId() == id)
        {
            item.setName(name);
            item.setDescription(description);
            item.setPrice(price);
            item.setActive(active);
            item.setCategoryId(categoryId);  // 👈 atualiza a categoria também

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
