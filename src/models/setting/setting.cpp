#include "models/setting/setting.h"

Setting::Setting(int id,
                 const string& key,
                 SettingValueType type)
{
    this->id = id;
    this->key = key;
    this->type = type;
    this->stringValue = "";
    this->boolValue = false;
    this->intValue = 0;

    this->validate();
}

Setting::Setting(int id,
                 const string& key,
                 SettingValueType type,
                 const string& stringValue)
{
    this->id = id;
    this->key = key;
    this->type = type;
    this->stringValue = stringValue;
    this->boolValue = false;
    this->intValue = 0;

    this->validate();
}

int Setting::getId() const
{
    return this->id;
}

const string& Setting::getKey() const
{
    return this->key;
}

void Setting::setKey(const string& key)
{
    this->key = key;
    this->validateKey();
}

SettingValueType Setting::getType() const
{
    return this->type;
}

void Setting::setType(SettingValueType type)
{
    this->type = type;
    this->validateValueByType();
}

const string& Setting::getStringValue() const
{
    return this->stringValue;
}

void Setting::setStringValue(const string& value)
{
    this->stringValue = value;
    this->validateValueByType();
}

bool Setting::getBoolValue() const
{
    return this->boolValue;
}

void Setting::setBoolValue(bool value)
{
    this->boolValue = value;
    this->validateValueByType();
}

int Setting::getIntValue() const
{
    return this->intValue;
}

void Setting::setIntValue(int value)
{
    this->intValue = value;
    this->validateValueByType();
}

void Setting::validate()
{
    this->validateKey();
    this->validateValueByType();
}

void Setting::validateKey() const
{
    if (this->key.empty())
    {
        throw ValidationException("Setting 'key' must not be empty.");
    }
}

void Setting::validateValueByType() const
{
    switch (this->type)
    {
        case SettingValueType::String:
            break;
        case SettingValueType::Bool:
            break;
        case SettingValueType::Int:
            break;
        default:
            throw ValidationException("Invalid SettingValueType.");
    }
}
