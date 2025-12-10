#pragma once

#include "repositories/category/i_category_repository.h"

class CategoryRepository : public ICategoryRepository
{
public:
    CategoryRepository();

    Category createCategory(
        const string& name,
        const string& description,
        bool active) override;

    vector<Category> findAll() override;

    Category findById(int id) override;

    Category updateCategory(
        int id,
        const string& name,
        const string& description,
        bool active) override;

    void deleteCategory(int id) override;

private:
    vector<Category> categories;
    int nextId;

    int findIndexById(int id) const;
};
