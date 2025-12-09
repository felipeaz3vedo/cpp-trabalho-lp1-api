#pragma once

#include <json/json.h>
#include <string>
#include "models/setting/setting.h"

class SettingResponseDto
{
public:
    int id;
    std::string key;
    std::string type;
    std::string value;

    static SettingResponseDto fromModel(const Setting& model);
    Json::Value toJson() const;
};
