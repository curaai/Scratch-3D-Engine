#pragma once 

#include "mesh.h"
#include <SDL.h>

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
    Drawable(mesh _mesh)
        : obj(_mesh)
    {
        translateMat = mat44::identical();
        scaleMat = mat44::identical();
        projMat = mat44::identical();
    }
    ~Drawable(){}

    void draw(SDL_Renderer* rend)
    {
        mat44 worldMat = rotateMat * translateMat * projMat;
        for (auto tri : obj.trig) {
            tri.pts[0] = worldMat * tri.pts[0];
            tri.pts[1] = worldMat * tri.pts[1];
            tri.pts[2] = worldMat * tri.pts[2];

            tri.pts[0].x += 1.0f; tri.pts[0].y += 1.0f; 
            tri.pts[1].x += 1.0f; tri.pts[1].y += 1.0f; 
            tri.pts[2].x += 1.0f; tri.pts[2].y += 1.0f; 

            tri.pts[0] = scaleMat * tri.pts[0];
            tri.pts[1] = scaleMat * tri.pts[1];
            tri.pts[2] = scaleMat * tri.pts[2];

            draw_triangle(rend, tri);
        }
    }

    void setTranslate(float x, float y, float z)
    {
        mat44 m = mat44::identical();
        m.m[3][0] = x;
        m.m[3][1] = y;
        m.m[3][2] = z;
        translateMat = m;
    }
    void setScale(float x, float y, float z)
    {
        mat44 m = mat44::identical();
        m.m[0][0] = x;
        m.m[1][1] = y;
        m.m[2][2] = z;
        scaleMat = m;
    }
    void setRotate(float tX, float tY, float tZ)
    {
        mat44 rX = mat44::identical();
        mat44 rY = rX;
        mat44 rZ = rX;

        // var cos tX, sin tX
        float vcosx = cos(tX); float vsinx = sin(tX);
        rX.m[1][1] = vcosx;
        rX.m[1][2] = -vsinx;
        rX.m[2][1] = vsinx;
        rX.m[2][2] = vcosx;

        // var cos tY, sin tY
        float vcosy = cos(tY); float vsiny = sin(tY);
        rY.m[0][0] = vcosy;
        rY.m[0][2] = vsiny;
        rY.m[2][0] = -vsiny;
        rY.m[2][2] = vcosy;

        // var cos tZ, sin tZ
        float vcosz = cos(tZ); float vsinz = sin(tZ);
        rZ.m[0][0] = vcosz;
        rZ.m[0][1] = -vsinz;
        rZ.m[1][0] = vsinz;
        rZ.m[1][1] = vcosz;

        rotateMat = rZ * rY * rX;
    }
    void setProjection(float aspectRatio, float fov, float fFar, float fNear)
    {
        mat44 proj;
        // convert degree to radian  
        float fovRad = 1.0f / tanf((fov / 180.0f * M_PI) * 0.5f);

        proj.m[0][0] = aspectRatio * fovRad;
        proj.m[1][1] = fovRad;
        proj.m[2][2] = fFar / (fFar - fNear);
        proj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		proj.m[2][3] = 1.0f;
		proj.m[3][3] = 0.0f;
        projMat = proj;
    }

    mesh obj;
    mat44 translateMat, scaleMat, rotateMat, projMat; 
};