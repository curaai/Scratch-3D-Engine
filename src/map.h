#pragma once 

#include "block.h"

#include <string>
#include <vector>
#include <fstream>


class Map
{
public:
    void ParseMapFromFile(std::string filePath);

private:
    std::vector<Block> blocks;
};