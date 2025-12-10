#pragma once

#include <vector>
#include <string>
#include "models/category/category.h"

using std::vector;
using std::string;

class CategoryService
{
public:
    static Category createCategory(
        const string& name,
        const string& description,
        bool active = true);

    static vector<Category> listCategories();

    static Category getCategoryById(int id);

    static Category updateCategory(
        int id,
        const string& name,
        const string& description,
        bool active);

    static void deleteCategory(int id);

private:
    static class ICategoryRepository& getRepository();
};
