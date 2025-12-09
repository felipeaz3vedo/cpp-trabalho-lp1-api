#pragma once

#include <string>
#include "shared/exceptions/validation_exception.h"

using std::string;

enum class SettingValueType
{
    String,
    Bool,
    Int
};

class Setting
{
public:
    Setting(int id,
            const string& key,
            SettingValueType type);

    Setting(int id,
            const string& key,
            SettingValueType type,
            const string& stringValue);

    int getId() const;

    const string& getKey() const;
    void setKey(const string& key);

    SettingValueType getType() const;
    void setType(SettingValueType type);

    const string& getStringValue() const;
    void setStringValue(const string& value);

    bool getBoolValue() const;
    void setBoolValue(bool value);

    int getIntValue() const;
    void setIntValue(int value);

private:
    int id;
    string key;
    SettingValueType type;

    string stringValue;
    bool boolValue;
    int intValue;

    void validate();
    void validateKey() const;
    void validateValueByType() const;
};
