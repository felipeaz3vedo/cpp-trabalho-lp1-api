#include "services/setting/csv_settings_file_parser.h"
#include "shared/exceptions/validation_exception.h"

#include <sstream>
#include <algorithm>

using std::getline;
using std::stringstream;
using std::pair;
using std::string;
using std::vector;

string CsvSettingsFileParser::trim(const string& s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    
    if (start == string::npos) return "";

    return s.substr(start, end - start + 1);
}

vector<pair<string, string>> CsvSettingsFileParser::parse(const string& content) const
{
    if (content.empty())
    {
        throw ValidationException("Settings CSV content is empty.");
    }

    stringstream ss(content);
    string headerLine;

    if (!getline(ss, headerLine))
    {
        throw ValidationException("Settings CSV header line is missing.");
    }

    vector<string> headers;
    {
        stringstream headerStream(headerLine);
        string col;
        while (getline(headerStream, col, ','))
        {
            headers.push_back(trim(col));
        }
    }

    if (headers.empty())
    {
        throw ValidationException("Settings CSV has no columns in header.");
    }

    string dataLine;

    if (!getline(ss, dataLine))
    {
        throw ValidationException("Settings CSV has no data rows.");
    }

    stringstream dataStream(dataLine);
    vector<string> values;
    string value;

    while (getline(dataStream, value, ','))
    {
        values.push_back(trim(value));
    }

    if (values.size() != headers.size())
    {
        throw ValidationException("Settings CSV: number of values does not match header columns.");
    }

    vector<pair<string, string>> result;

    for (size_t i = 0; i < headers.size(); ++i)
    {
        result.emplace_back(headers[i], values[i]);
    }

    return result;
}
