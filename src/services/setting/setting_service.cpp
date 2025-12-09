#include "services/setting/setting_service.h"
#include "repositories/setting/setting_repository.h"
#include "services/setting/csv_settings_file_parser.h"
#include "shared/exceptions/validation_exception.h"
#include "shared/exceptions/not_found_exception.h"

#include <algorithm>

vector<Setting> SettingService::listSettings()
{
    return SettingRepository::findAll();
}

void SettingService::applyValidatedValue(Setting& setting, const string& value)
{
    const string& key = setting.getKey();
    SettingValueType type = setting.getType();

    if (key == "theme")
    {
        string v = value;
        std::transform(v.begin(), v.end(), v.begin(), ::tolower);

        if (v != "dark" && v != "light")
        {
            throw ValidationException("Invalid value for 'theme'. Use 'dark' or 'light'.");
        }

        if (type != SettingValueType::String)
        {
            throw ValidationException("'theme' setting must be of type string.");
        }

        setting.setStringValue(v);
        return;
    }

    if (key == "display_name_en")
    {
        if (type != SettingValueType::String)
        {
            throw ValidationException("'display_name_en' setting must be of type string.");
        }

        setting.setStringValue(value);
        return;
    }

    switch (type)
    {
        case SettingValueType::String:
            setting.setStringValue(value);
            break;

        case SettingValueType::Bool:
        {
            string v = value;
            std::transform(v.begin(), v.end(), v.begin(), ::tolower);

            if (v == "true" || v == "1")
            {
                setting.setBoolValue(true);
            }
            else if (v == "false" || v == "0")
            {
                setting.setBoolValue(false);
            }
            else
            {
                throw ValidationException("Invalid bool value for setting '" + key + "'.");
            }
            break;
    }

    case SettingValueType::Int:
        try
        {
            int parsed = std::stoi(value);
            setting.setIntValue(parsed);
        }
        catch (...)
        {
            throw ValidationException("Invalid int value for setting '" + key + "'.");
        }
        break;

    default:
        throw ValidationException("Unsupported type for setting '" + key + "'.");
    }
}

vector<Setting> SettingService::importFromCsv(const string& csvContent)
{
    CsvSettingsFileParser parser;
    auto keyValuePairs = parser.parse(csvContent);

    if (keyValuePairs.empty())
    {
        throw ValidationException("No settings found in CSV file.");
    }

    vector<Setting> updatedSettings;

    for (const auto& kv : keyValuePairs)
    {
        const string& key = kv.first;
        const string& value = kv.second;

        try
        {
            Setting existing = SettingRepository::findByKey(key);

            applyValidatedValue(existing, value);
            SettingRepository::upsert(existing);
            updatedSettings.push_back(existing);
        }
        catch (const NotFoundException&)
        {
            throw ValidationException(
                "Cannot update setting '" + key +
                "' from CSV because it does not exist in the application.");
        }
    }

    if (updatedSettings.empty())
    {
        throw ValidationException("No existing settings were updated from CSV.");
    }

    return updatedSettings;
}

Setting SettingService::createSetting(
    const string& key,
    const string& typeName,
    const string& value)
{
    try
    {
        (void)SettingRepository::findByKey(key);
        throw ValidationException("Setting with key '" + key + "' already exists.");
    }
    catch (const NotFoundException&)
    {
        // ok, can create
    }

    SettingValueType type = parseTypeName(typeName);

    Setting setting = SettingRepository::create(key, type);

    applyValidatedValue(setting, value);

    SettingRepository::upsert(setting);

    return setting;
}

Setting SettingService::updateSetting(const string& key, const string& value)
{
    Setting existing = SettingRepository::findByKey(key);

    applyValidatedValue(existing, value);

    SettingRepository::upsert(existing);

    return existing;
}

void SettingService::deleteSetting(const string& key)
{
    SettingRepository::deleteByKey(key);
}

SettingValueType SettingService::parseTypeName(const string& typeName)
{
    string lower = typeName;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower == "string")
        return SettingValueType::String;
    if (lower == "bool" || lower == "boolean")
        return SettingValueType::Bool;
    if (lower == "int" || lower == "integer")
        return SettingValueType::Int;

    throw ValidationException("Unknown setting type: " + typeName +
                              ". Valid types are: string, bool, int.");
}
