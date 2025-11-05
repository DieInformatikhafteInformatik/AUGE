#include <iostream>
#include <sstream>
#include <algorithm>

#include "stringutils.h"

bool str::equals(char c1, char c2, bool ignoreCase)
{
    return ignoreCase ?
        std::tolower(c1) == std::tolower(c2) :
        c1 == c2;
}

bool str::equals(std::string_view s1, std::string_view s2, bool ignoreCase)
{
    return s1.size() == s2.size() && 
        std::equal(s1.begin(), s1.end(), s2.begin(), [&ignoreCase](auto& c1, auto& c2) { return equals(c1, c2, ignoreCase); });
}

std::vector<std::string> str::split(std::string_view s, char delimiter)
{
    std::vector<std::string> result;
    std::istringstream iss{std::string(s)};

    std::string temp;
    while(std::getline(iss, temp, delimiter))
    {
        result.push_back(temp);
    }

    return result;
}

bool str::startsWith(std::string_view s, std::string_view start, bool ignoreCase)
{
    return std::equal(start.begin(), start.end(), s.begin(), 
        [&ignoreCase](char c1, char c2)
        {
            return equals(c1, c2, ignoreCase);
        }
    );
}

bool str::endsWith(std::string_view s, std::string_view end, bool ignoreCase)
{
    return std::equal(end.begin(), end.end(), s.end() - end.length(),
        [&ignoreCase](char c1, char c2)
        {
            return equals(c1, c2, ignoreCase);
        }
    );
}
