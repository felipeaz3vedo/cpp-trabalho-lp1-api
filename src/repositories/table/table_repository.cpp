#include "repositories/table/table_repository.h"
#include "shared/exceptions/not_found_exception.h"

vector<Table> TableRepository::tables = {};
int TableRepository::nextId = 1;

Table TableRepository::createTable(int number, int capacity, bool available)
{
    Table table(nextId, number, capacity, available);
    tables.push_back(table);
    nextId++;
    return table;
}

vector<Table> TableRepository::findAll()
{
    return tables;
}

Table TableRepository::findById(int id)
{
    for (Table table : tables)
    {
        if (table.getId() == id)
        {
            return table;
        }
    }

    throw NotFoundException("Table not found.");
}

Table TableRepository::updateTable(int id, int number, int capacity, bool available)
{
    for (Table& table : tables)
    {
        if (table.getId() == id)
        {
            table.setNumber(number);
            table.setCapacity(capacity);
            table.setAvailable(available);
            return table;
        }
    }

    throw NotFoundException("Table not found.");
}

void TableRepository::deleteTable(int id)
{
    for (size_t i = 0; i < tables.size(); i++)
    {
        if (tables[i].getId() == id)
        {
            tables.erase(tables.begin() + i);
            return;
        }
    }

    throw NotFoundException("Table not found.");
}
