#include "repositories/setting/setting_repository.h"
#include "shared/exceptions/not_found_exception.h"

vector<Setting> SettingRepository::settings = {};
int SettingRepository::nextId = 1;

void SettingRepository::initializeDefaults()
{
    settings.clear();
    nextId = 1;

    Setting themeSetting(nextId++, "theme", SettingValueType::String, "light");
    settings.push_back(themeSetting);

    Setting displayNameSetting(nextId++, "display_name_en", SettingValueType::String, "Restaurant");
    settings.push_back(displayNameSetting);
}

vector<Setting> SettingRepository::findAll()
{
    return settings;
}

int SettingRepository::findIndexByKey(const string& key)
{
    for (size_t i = 0; i < settings.size(); ++i)
    {
        if (settings[i].getKey() == key)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

Setting SettingRepository::findByKey(const string& key)
{
    int index = findIndexByKey(key);
    if (index < 0)
    {
        throw NotFoundException("Setting not found: " + key);
    }

    return settings[index];
}

void SettingRepository::upsert(const Setting& setting)
{
    int index = findIndexByKey(setting.getKey());

    if (index < 0)
    {
        Setting newSetting = setting;
        settings.push_back(newSetting);
    }
    else
    {
        settings[index] = setting;
    }
}

// NOVO: cria um Setting com id novo e tipo definido (valor será ajustado no service)
Setting SettingRepository::create(const string& key, SettingValueType type)
{
    Setting setting(nextId++, key, type);
    settings.push_back(setting);
    return setting;
}

// NOVO: deletar por key
void SettingRepository::deleteByKey(const string& key)
{
    int index = findIndexByKey(key);
    if (index < 0)
    {
        throw NotFoundException("Setting not found: " + key);
    }

    settings.erase(settings.begin() + index);
}
