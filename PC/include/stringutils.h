#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace str
{
    bool equals(char c1, char c2, bool ignoreCase = false);
    bool equals(std::string_view s1, std::string_view s2, bool ignoreCase = false);

    std::vector<std::string> split(std::string_view s, char delimiter);
    
    bool startsWith(std::string_view s, std::string_view start, bool ignoreCase = false);
    inline bool startsWith(std::string_view s, char start, bool ignoreCase = false)
    {
        return startsWith(s, std::string(1, start), ignoreCase);
    }

    bool endsWith(std::string_view s, std::string_view end, bool ignoreCase = false);
    inline bool endsWith(std::string_view s, char end, bool ignoreCase = false)
    {
        return endsWith(s, std::string(1, end), ignoreCase);
    }
}