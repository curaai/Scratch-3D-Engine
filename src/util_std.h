#pragma once

#include <string>

namespace util {
namespace str {
inline bool endswith(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
           0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}
}; // namespace std
}; // namespace util