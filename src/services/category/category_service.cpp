#include "services/category/category_service.h"
#include "repositories/category/category_repository.h"

using std::vector;
using std::string;

namespace
{
    CategoryRepository categoryRepositoryInstance;
}

ICategoryRepository& CategoryService::getRepository()
{
    return categoryRepositoryInstance;
}

Category CategoryService::createCategory(
    const string& name,
    const string& description,
    bool active)
{
    return getRepository().createCategory(name, description, active);
}

vector<Category> CategoryService::listCategories()
{
    return getRepository().findAll();
}

Category CategoryService::getCategoryById(int id)
{
    return getRepository().findById(id);
}

Category CategoryService::updateCategory(
    int id,
    const string& name,
    const string& description,
    bool active)
{
    return getRepository().updateCategory(id, name, description, active);
}

void CategoryService::deleteCategory(int id)
{
    getRepository().deleteCategory(id);
}
