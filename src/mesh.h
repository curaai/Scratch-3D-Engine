#pragma once 

#include <tuple>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
// #include "SDL2/SDL.h"
#include "SDL.h"
#include "SDL_image.h"

#include "vec.h"
#include "util_vec.h"

struct triangle
{
    vec3d pts[3];
    vec3d surface_normal(void) const
    {
        auto a = pts[1] - pts[0];
        auto b = pts[2] - pts[0];
        return vec3d {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    bool is_ccw(void) const 
    {
        auto a = pts[1]-pts[0];
        auto b = pts[2]-pts[0];
        auto res = util::vec::cross(a, b);
        return (res.x + res.y + res.z) > 0;
    }
};

struct mat44 
{
    mat44() {}
    mat44(vec3d a, vec3d b, vec3d c, vec3d d)
    {
        m[0][0] = a.x; m[1][0] = a.y; m[2][0] = a.z;
        m[0][1] = b.x; m[1][1] = b.y; m[2][1] = b.z;
        m[0][2] = c.x; m[1][2] = c.y; m[2][2] = c.z;
        m[0][3] = d.x; m[1][3] = d.y; m[2][3] = d.z;
    }

    float m[4][4] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    };
    mat44 operator* (const mat44& mat) const
    {
        mat44 res;
        for(int i=0; i<4; i++) {
            for(int j=0; j<4; j++) {
                for(int k=0; k<4; k++) {
                    res.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }
        return res;
    }
    vec3d operator* (const vec3d& vec) const
    {
        vec3d res;
        res.x = vec.x * m[0][0] + vec.y * m[0][1] + vec.z * m[0][2] + m[0][3];
        res.y = vec.x * m[1][0] + vec.y * m[1][1] + vec.z * m[1][2] + m[1][3];
        res.z = vec.x * m[2][0] + vec.y * m[2][1] + vec.z * m[2][2] + m[2][3];
        float w = vec.x * m[3][0] + vec.y * m[3][1] + vec.z * m[3][2] + m[3][3];
        if(w != 0.0f)
            res.x /= w; res.y /= w; res.z /= w;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const mat44& mat)
    {
        os << mat.m[0][0] << ' ' << mat.m[0][1] << ' ' << mat.m[0][2] << ' ' << mat.m[0][3] << std::endl;
        os << mat.m[1][0] << ' ' << mat.m[1][1] << ' ' << mat.m[1][2] << ' ' << mat.m[1][3] << std::endl;
        os << mat.m[2][0] << ' ' << mat.m[2][1] << ' ' << mat.m[2][2] << ' ' << mat.m[2][3] << std::endl;
        os << mat.m[3][0] << ' ' << mat.m[3][1] << ' ' << mat.m[3][2] << ' ' << mat.m[3][3] << std::endl;
        return os;
    } 

    static mat44 identical(void)
    {
        mat44 mat;
        mat.m[0][0] = 1;
        mat.m[1][1] = 1;
        mat.m[2][2] = 1;
        mat.m[3][3] = 1;
        return mat;
    }
};

using verIdx = std::tuple<uint, uint, uint>;

namespace {
std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;

    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}   
};

struct mesh
{
    const std::vector<vec3d> verts;
    const std::vector<verIdx> ver_indices;
    const std::vector<vec3d> texs;
    const std::vector<verIdx> tex_indices;
    const std::vector<vec3d> norms;
    const std::vector<verIdx> norm_indices;

    mesh(const std::vector<vec3d> &verts, const std::vector<verIdx> &ver_indices,
         const std::vector<vec3d> &texs,  const std::vector<verIdx> &tex_indices,
         const std::vector<vec3d> &norms, const std::vector<verIdx> &norm_indices)
        : verts(verts), ver_indices(ver_indices)
        , texs(texs), tex_indices(tex_indices)
        , norms(norms), norm_indices(norm_indices)
    { }

    std::vector<triangle> triangles(void) const
    {
        std::vector<triangle> tris;
        for(const verIdx& idx : ver_indices) {
            tris.push_back(triangle{
                verts[std::get<0>(idx)], 
                verts[std::get<1>(idx)], 
                verts[std::get<2>(idx)]
            });
        }
        return tris;
    }
    triangle texture(int i) const 
    {
        auto t_indices = tex_indices[i];
        triangle texels;

        texels.pts[0] = texs[std::get<0>(t_indices)];
        texels.pts[1] = texs[std::get<1>(t_indices)];
        texels.pts[2] = texs[std::get<2>(t_indices)];
        return texels;
    };

    // inline const SDL_Color get_color(int tri_idx) const { return colors[tri_idx]; }

    static mesh load_from_obj(const char* path)
    {

        std::ifstream in (path);
        std::vector<vec3d> verts;
        std::vector<verIdx> ver_indices;
        std::vector<vec3d> texs;
        std::vector<verIdx> tex_indices;
        std::vector<vec3d> norms;
        std::vector<verIdx> norm_indices;

        char _type[2];
        while(in.good())
        {
            char line[128];
            in.getline(line, 128);

            std::stringstream ss;
            ss << line;

            // vertex
            if(line[0] == 'v')
            {
                vec3d vertex;
                ss >> _type >> vertex.x >> vertex.y >> vertex.z;
                if(line[1] == 'n')
                    norms.push_back(vertex);
                else if(line[1] == 't')
                    texs.push_back(vertex);
                else if(line[1] == ' ')
                    verts.push_back(vertex);
            }

            else if(line[0] == 'f')
            {
                std::string f[3];
                ss >> _type >> f[0] >> f[1] >> f[2];

                verIdx ver_idx, tex_idx, norm_idx; 
                verIdx* idx;

                for(uint i=0; i<3; i++) {
                    std::vector<std::string> tokens;
                    for (uint j = 0; j < 3; j++) {
                        tokens.push_back(split(f[j], "/")[i]);
                    }
                    if(i == 0)
                        idx = &ver_idx;
                    else if(i == 1)
                        idx = &tex_idx;
                    else if(i == 2)
                        idx = &norm_idx;
                    
                    std::get<0>(*idx) = std::stoul(tokens[0])-1;
                    std::get<1>(*idx) = std::stoul(tokens[1])-1;
                    std::get<2>(*idx) = std::stoul(tokens[2])-1;
                }
                ver_indices.push_back(ver_idx);
                tex_indices.push_back(tex_idx);
                norm_indices.push_back(norm_idx);
            }
        }

        return mesh{verts, ver_indices, texs, tex_indices, norms, norm_indices};
    }
};
