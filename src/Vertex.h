#pragma once

#include "triangle.h"

struct Vertex
{
    vec3d wpos;
    vec3d wnormal;
    vec2d tpos;
};

struct VSOutput : public Vertex
{
    vec3d cpos;
};

class VertexTriangle : public triangle<Vertex>
{
public:
    VertexTriangle(Tri3d world_tri, Tri3d wnormal_tri, Tri2d tpos_tri)
    {
        pts[0].wpos = world_tri[0];
        pts[1].wpos = world_tri[1];
        pts[2].wpos = world_tri[2];

        pts[0].wnormal = wnormal_tri[0];
        pts[1].wnormal = wnormal_tri[1];
        pts[2].wnormal = wnormal_tri[2];

        pts[0].tpos = tpos_tri[0];
        pts[1].tpos = tpos_tri[1];
        pts[2].tpos = tpos_tri[2];
    }

    Tri3d wnormalTriangle(void) const
    {
        return Tri3d{ pts[0].wnormal, pts[1].wnormal, pts[2].wnormal };
    }
    Tri3d wposTriangle(void) const
    {
        return Tri3d{ pts[0].wpos, pts[1].wpos, pts[2].wpos };
    }
    Tri2d tposTriangle(void) const
    {
        return Tri2d{ pts[0].tpos, pts[1].tpos, pts[2].tpos };
    }
};

class VSTriangle : public triangle<VSOutput>
{
public:
    VSTriangle(const triangle<vec3d>& world_tri,
               const triangle<vec3d>& wnormal_tri,
               const triangle<vec2d>& tpos_tri,
               const triangle<vec3d>& clipped_tri)
    {
        pts[0].cpos = clipped_tri[0];
        pts[1].cpos = clipped_tri[1];
        pts[2].cpos = clipped_tri[2];

        pts[0].wpos = world_tri[0];
        pts[1].wpos = world_tri[1];
        pts[2].wpos = world_tri[2];

        pts[0].wnormal = wnormal_tri[0];
        pts[1].wnormal = wnormal_tri[1];
        pts[2].wnormal = wnormal_tri[2];

        pts[0].tpos = tpos_tri[0];
        pts[1].tpos = tpos_tri[1];
        pts[2].tpos = tpos_tri[2];
    }

    Tri3d cposTriangle(void) const
    {
        return Tri3d{ pts[0].cpos, pts[1].cpos, pts[2].cpos };
    }
    Tri3d wposTriangle(void) const
    {
        return Tri3d{ pts[0].wpos, pts[1].wpos, pts[2].wpos };
    }
    Tri3d wnormalTriangle(void) const
    {
        return Tri3d{ pts[0].wnormal, pts[1].wnormal, pts[2].wnormal };
    }
    Tri2d tposTriangle(void) const
    {
        return Tri2d{ pts[0].tpos, pts[1].tpos, pts[2].tpos };
    }
};
