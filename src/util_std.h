#pragma once

#include <string>

namespace util {
namespace str {
inline bool Endswith(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
           0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}
inline std::vector<std::string> Split(const std::string& str,
                                      const std::string& delim)
{
    std::vector<std::string> tokens;

    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos)
            pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}
}; // namespace std
}; // namespace util