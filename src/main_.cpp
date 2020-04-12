#include "IDrawable.h"

int main(int argc, char* argv[])
{
    // draw cube
	std::vector<vec3d> pts = {
		{0, 0, 0}, {1, 0, 0},
		{0, 0, 1}, {1, 0, 1},
		{0, 1, 0}, {1, 1, 0},
		{0, 1, 1}, {1, 1, 1},
	};
    
    std::vector<vecIdx> idxArr = {
        {0, 4, 5}, {0, 5, 1}, // south
        {1, 5, 7}, {1, 3, 7}, // east
        {2, 6, 7}, {2, 7, 3}, // north
        {0, 4, 6}, {0, 2, 6}, // west
        {4, 6, 7}, {4, 7, 5}, // top
        {0, 2, 3}, {0, 3, 1}, // bottom
    };
	mesh cube {pts, idxArr};
	
	mat44  translationMat, scaleMat, projectionMat; 

	return 0;
}
