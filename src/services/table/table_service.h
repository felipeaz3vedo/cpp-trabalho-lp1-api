#pragma once

#include <vector>
#include "models/table/table.h"

using std::vector;

class TableService {
public:
    static Table createTable(int number, int capacity, bool available);
    static vector<Table> listTables();
    static Table getTableById(int id);
    static Table updateTable(int id, int number, int capacity, bool available);
    static void deleteTable(int id);
};
