#pragma once 

#include "mesh.h"
#include "resource.h"
#include "util_mat.h"
#include "util_std.h"

#include <math.h>

inline void draw_triangle(SDL_Renderer* rend, triangle tri)
{
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    SDL_RenderDrawLineF(rend, tri.pts[0].x, tri.pts[0].y, tri.pts[1].x, tri.pts[1].y);
    SDL_RenderDrawLineF(rend, tri.pts[1].x, tri.pts[1].y, tri.pts[2].x, tri.pts[2].y);
    SDL_RenderDrawLineF(rend, tri.pts[2].x, tri.pts[2].y, tri.pts[0].x, tri.pts[0].y);

    SDL_SetRenderDrawColor(rend,0,0,0,255);
}

class Drawable
{
public:
    Drawable(const mesh& mesh_, const Resource& rsc)
        : mesh_(mesh_)
        , rsc(rsc)
    {
        rotateMat = mat44::identical();
        translateMat = mat44::identical();
        scaleMat = mat44::identical();
    }
    ~Drawable(){}

    std::vector<triangle> getConverted(const mat44& mat){
        std::vector<triangle> cvtTris; 
        for(auto tri : mesh_.triangles()) {
            triangle newTri;
            newTri.pts[0] = mat * tri.pts[0];
            newTri.pts[1] = mat * tri.pts[1];
            newTri.pts[2] = mat * tri.pts[2];
            cvtTris.push_back(newTri);
        }
        return cvtTris;
    }

    const mat44 world_matrix(void)
    {
        return translateMat * scaleMat * rotateMat;
    }

    void setTranslate(float x, float y, float z)
    {
        translateMat = util::mat::getTranslationMat(vec3d {x, y, z});
    }
    void setScale(float x, float y, float z)
    {
        scaleMat = util::mat::getScaleMat(vec3d {x, y, z});
    }
    void setRotate(float x, float y, float z)
    {
        rotateMat = util::mat::getRotationMat(vec3d {x, y, z});
    }

public:
    const mesh mesh_;
    const Resource rsc;
private:
    mat44 translateMat, scaleMat, rotateMat;
};