#pragma once

#include <vector>
#include <string>
#include "models/menu_item/menu_item.h"

using std::vector;
using std::string;

class MenuItemRepository {
public:
    static MenuItem createMenuItem(
        string name,
        string description,
        double price,
        bool active = true
    );

    static vector<MenuItem> findAll();

    static MenuItem findById(int id);

    static MenuItem updateMenuItem(
        int id,
        string name,
        string description,
        double price,
        bool active
    );

    static void deleteMenuItem(int id);

private:
    static vector<MenuItem> menuItems;
    static int nextId;
};
