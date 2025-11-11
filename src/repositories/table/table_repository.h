#pragma once

#include <vector>
#include "models/table/table.h"

using std::vector;

class TableRepository {
public:
    static Table createTable(int number, int capacity, bool available);
    static vector<Table> findAll();
    static Table findById(int id);
    static Table updateTable(int id, int number, int capacity, bool available);
    static void deleteTable(int id);

private:
    static vector<Table> tables;
    static int nextId;
};
