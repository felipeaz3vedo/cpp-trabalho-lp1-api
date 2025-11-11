#include "services/table/table_service.h"
#include "repositories/table/table_repository.h"

Table TableService::createTable(
    int number,
    int capacity,  
    bool available)
{
    return TableRepository::createTable(number, capacity, available);
}

vector<Table> TableService::listTables()
{
    return TableRepository::findAll();
}

Table TableService::getTableById(int id)
{
    return TableRepository::findById(id);
}

Table TableService::updateTable(
    int id,
    int number, 
    int capacity, 
    bool available)
{
    return TableRepository::updateTable(id, number, capacity, available);
}

void TableService::deleteTable(int id)
{
    TableRepository::deleteTable(id);
}
