#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
// #include "SDL2/SDL.h"

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#error Windows_OS
#elif defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include "SDL.h"
#include "SDL_image.h"
#endif

#include "triangle.h"
#include "util_std.h"
#include "util_vec.h"

#include "Vertex.h"

using verIdx = std::tuple<uint, uint, uint>;

struct VertexBuffer
{
    std::vector<vec3d> vertexes;
    std::vector<verIdx> indices;

    Tri3d get(const int i) const
    {
        const auto& idx = indices[i];
        Tri3d tri;
        tri.pts[0] = vertexes[std::get<0>(idx)];
        tri.pts[1] = vertexes[std::get<1>(idx)];
        tri.pts[2] = vertexes[std::get<2>(idx)];
        return tri;
    }
    Tri3d operator[](const int i) const { return this->get(i); }
    std::vector<Tri3d> triangles(void) const
    {
        std::vector<Tri3d> tris;
        for (int i = 0; i < indices.size(); i++)
            tris.push_back(this->get(i));
        return tris;
    }
};

class Mesh
{
public:
    const VertexBuffer vb;
    const VertexBuffer tex_vb;
    const VertexBuffer norm_vb;
    const bool is_textured;

    Mesh(const VertexBuffer& vb,
         const VertexBuffer& tex_vb,
         const VertexBuffer& norm_vb,
         const bool is_textured)
        : vb(vb)
        , tex_vb(tex_vb)
        , norm_vb(norm_vb)
        , is_textured(is_textured)
    {}

    std::vector<VertexTriangle> triangles(void) const
    {
        std::vector<VertexTriangle> res;
        for (int i = 0; i < vb.indices.size(); i++) {
            Tri3d v = vb[i];
            Tri3d n = norm_vb[i];
            Tri3d _t = tex_vb[i];
            Tri2d t{ (vec2d)_t[0], (vec2d)_t[1], (vec2d)_t[2] };

            VertexTriangle vt{ v, n, t };
            res.push_back(vt);
        }
        return res;
    }

    Tri3d vertex(int i) const { return vb[i]; }
    Tri3d texture(int i) const { return tex_vb[i]; }
    Tri3d normal(int i) const { return norm_vb[i]; }

    static Mesh loadFromObj(const char* path, const bool is_textured = true)
    {
        std::ifstream in(path);
        VertexBuffer vb;
        VertexBuffer tvb;
        VertexBuffer nvb;

        char _type[2];
        while (in.good()) {
            char line[128];
            in.getline(line, 128);

            std::stringstream ss;
            ss << line;

            // vertex
            if (line[0] == 'v') {
                vec3d vertex;
                ss >> _type >> vertex[0] >> vertex[1] >> vertex[2];
                if (line[1] == 'n')
                    nvb.vertexes.push_back(vertex);
                else if (line[1] == 't')
                    tvb.vertexes.push_back(vertex);
                else if (line[1] == ' ')
                    vb.vertexes.push_back(vertex);
            }

            else if (line[0] == 'f') {
                if (is_textured) {
                    std::string f[3];
                    ss >> _type >> f[0] >> f[1] >> f[2];

                    verIdx ver_idx, tex_idx, norm_idx;
                    verIdx* idx;

                    for (uint i = 0; i < 3; i++) {
                        std::vector<std::string> tokens;
                        for (uint j = 0; j < 3; j++) {
                            tokens.push_back(util::str::Split(f[j], "/")[i]);
                        }
                        if (i == 0)
                            idx = &ver_idx;
                        else if (i == 1)
                            idx = &tex_idx;
                        else if (i == 2)
                            idx = &norm_idx;

                        std::get<0>(*idx) = std::stoul(tokens[0]) - 1;
                        std::get<1>(*idx) = std::stoul(tokens[1]) - 1;
                        std::get<2>(*idx) = std::stoul(tokens[2]) - 1;
                    }
                    vb.indices.push_back(ver_idx);
                    tvb.indices.push_back(tex_idx);
                    nvb.indices.push_back(norm_idx);
                } else {
                    int ver_idx[3];
                    ss >> _type >> ver_idx[0] >> ver_idx[1] >> ver_idx[2];
                    vb.indices.push_back({
                        ver_idx[0] - 1,
                        ver_idx[1] - 1,
                        ver_idx[2] - 1,
                    });
                }
            }
        }

        return Mesh{ vb, tvb, nvb, is_textured };
    }
};
