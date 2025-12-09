#pragma once

#include "services/setting/i_settings_file_parser.h"

class CsvSettingsFileParser : public ISettingsFileParser
{
public:
    vector<std::pair<std::string, std::string>> parse(const std::string& content) const override;

private:
    static std::string trim(const std::string& s);
};
