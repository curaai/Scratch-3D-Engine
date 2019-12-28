#include "utils.h"
#include "point.h"
#include "map.h"

#include <algorithm>


void Map::ParseMapFromFile(std::string filePath)
{
    // read from files
    std::vector<std::string> lines;
    std::string line;

    std::ifstream rf(filePath.c_str());
    while(rf.eof()) {
        getline(rf, line);
        lines.push_back(line);
        line.clear();
    }

    // convert line to map 
    for(auto& line : lines) {
        {
            using namespace util::str;

            auto splited = split(trim(line), ' ');
            std::vector<Pt3d> v;
            std::transform(splited.begin(), splited.end(), std::back_inserter(v), 
                [](const string& s) -> Pt3d { 
                    auto v = split(s, ',');
                    return Pt3d {std::stoi(v[0]), std::stoi(v[1])}; 
                }
            );

            this->blocks.push_back( Block{v} );
        }
    }
}
