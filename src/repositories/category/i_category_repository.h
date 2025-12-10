#pragma once

#include <vector>
#include <string>
#include "models/category/category.h"

using std::vector;
using std::string;

class ICategoryRepository
{
public:
    virtual ~ICategoryRepository() = default;

    virtual Category createCategory(
        const string& name,
        const string& description,
        bool active) = 0;

    virtual vector<Category> findAll() = 0;

    virtual Category findById(int id) = 0;

    virtual Category updateCategory(
        int id,
        const string& name,
        const string& description,
        bool active) = 0;

    virtual void deleteCategory(int id) = 0;
};
