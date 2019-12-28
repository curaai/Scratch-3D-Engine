#pragma once 

#include <string>
#include <sstream>
#include <vector>

#define TRIM_SPACE " \t\n\v"

namespace util {
    namespace str {
        using namespace std;
        
        string trim(string& s, const string& drop = TRIM_SPACE);
        vector<string> split(const string& s, const char delim);
    }
}

