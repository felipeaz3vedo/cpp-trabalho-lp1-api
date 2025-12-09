#include "shared/dtos/setting/setting_response_dto.h"

SettingResponseDto SettingResponseDto::fromModel(const Setting& model)
{
    SettingResponseDto dto;
    dto.id = model.getId();
    dto.key = model.getKey();

    switch (model.getType())
    {
    case SettingValueType::String:
        dto.type = "string";
        dto.value = model.getStringValue();
        break;
    case SettingValueType::Bool:
        dto.type = "bool";
        dto.value = model.getBoolValue() ? "true" : "false";
        break;
    case SettingValueType::Int:
        dto.type = "int";
        dto.value = std::to_string(model.getIntValue());
        break;
    default:
        dto.type = "unknown";
        dto.value = "";
        break;
    }

    return dto;
}

Json::Value SettingResponseDto::toJson() const
{
    Json::Value json;
    json["id"] = this->id;
    json["key"] = this->key;
    json["type"] = this->type;
    json["value"] = this->value;
    return json;
}
