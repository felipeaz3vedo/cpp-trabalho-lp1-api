#pragma once

#include <string>
#include <vector>
#include "models/setting/setting.h"

using std::string;
using std::vector;

class SettingService
{
public:
    static vector<Setting> listSettings();
    
    static vector<Setting> importFromCsv(const string& csvContent);

    static Setting createSetting(const string& key, const string& typeName, const string& value);

    static Setting updateSetting(const string& key, const string& value);

    static void deleteSetting(const string& key);

private:
    static void applyValidatedValue(Setting& setting, const string& value);

    static SettingValueType parseTypeName(const string& typeName);
};

