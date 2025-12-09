#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class ISettingsFileParser
{
public:
    virtual ~ISettingsFileParser() = default;
    virtual vector<std::pair<string, string>> parse(const string& content) const = 0;
};
