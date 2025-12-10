#include "repositories/category/category_repository.h"
#include "shared/exceptions/not_found_exception.h"

CategoryRepository::CategoryRepository()
{
    this->nextId = 1;
    this->categories = {};
}

int CategoryRepository::findIndexById(int id) const
{
    for (size_t i = 0; i < categories.size(); ++i)
    {
        if (categories[i].getId() == id)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

Category CategoryRepository::createCategory(
    const string& name,
    const string& description,
    bool active)
{
    Category category(nextId, name, description, active);
    categories.push_back(category);
    nextId++;
    return category;
}

vector<Category> CategoryRepository::findAll()
{
    return categories;
}

Category CategoryRepository::findById(int id)
{
    int index = findIndexById(id);
    if (index < 0)
    {
        throw NotFoundException("Category not found.");
    }

    return categories[index];
}

Category CategoryRepository::updateCategory(
    int id,
    const string& name,
    const string& description,
    bool active)
{
    int index = findIndexById(id);
    if (index < 0)
    {
        throw NotFoundException("Category not found.");
    }

    Category& category = categories[index];
    category.setName(name);
    category.setDescription(description);
    category.setActive(active);

    return category;
}

void CategoryRepository::deleteCategory(int id)
{
    int index = findIndexById(id);
    if (index < 0)
    {
        throw NotFoundException("Category not found.");
    }

    categories.erase(categories.begin() + static_cast<long>(index));
}
