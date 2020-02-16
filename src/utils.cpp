#include "utils.h"
#include <string>


namespace util {
    namespace str {
        using namespace std;

        string trim(string& s, const string& drop)
        {
            string r=s.erase(s.find_last_not_of(drop)+1);
            return r.erase(0, r.find_first_not_of(drop));
        }
        vector<string> split(const string& s, const char delim)
        {
            vector<string> result;
            stringstream ss (s);
            string item;

            while (getline (ss, item, delim)) {
                result.push_back (item);
            }

            return result;
        }
    }
}
