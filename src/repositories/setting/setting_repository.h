#pragma once

#include <vector>
#include <string>
#include "models/setting/setting.h"

using std::string;
using std::vector;

class SettingRepository
{
public:
    static void initializeDefaults();

    static vector<Setting> findAll();
    static Setting findByKey(const string& key);
    static void upsert(const Setting& setting);
    static Setting create(const string& key, SettingValueType type);
    static void deleteByKey(const string& key);

private:
    static vector<Setting> settings;
    static int nextId;

    static int findIndexByKey(const string& key);
};
