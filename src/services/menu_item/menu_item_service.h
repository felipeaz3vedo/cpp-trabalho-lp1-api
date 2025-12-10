#pragma once

#include <string>
#include <vector>
#include "models/menu_item/menu_item.h"

using std::string;
using std::vector;

class MenuItemService {
public:
    static MenuItem createMenuItem(
        string name,
        string description,
        double price,
        bool active,
        int categoryId);

    static vector<MenuItem> listMenuItems();
    
    static MenuItem getMenuItemById(int id);

    static MenuItem updateMenuItem(
        int id,
        string name,
        string description,
        double price,
        bool active,
        int categoryId);

    static void deleteMenuItem(int id);
};

