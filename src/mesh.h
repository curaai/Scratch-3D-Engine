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
#include "util_vec.h"

struct mat44
{
    mat44() {}
    mat44(const vec3d& a, const vec3d& b, const vec3d& c, const vec3d& d)
    {
        m[0][0] = a[0];
        m[1][0] = a[1];
        m[2][0] = a[2];
        m[0][1] = b[0];
        m[1][1] = b[1];
        m[2][1] = b[2];
        m[0][2] = c[0];
        m[1][2] = c[1];
        m[2][2] = c[2];
        m[0][3] = d[0];
        m[1][3] = d[1];
        m[2][3] = d[2];
    }

    float m[4][4] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    mat44 operator*(const mat44& mat) const
    {
        mat44 res;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    res.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }
        return res;
    }
    vec3d operator*(const vec3d& vec) const
    {
        vec3d res;
        res[0] =
            vec[0] * m[0][0] + vec[1] * m[0][1] + vec[2] * m[0][2] + m[0][3];
        res[1] =
            vec[0] * m[1][0] + vec[1] * m[1][1] + vec[2] * m[1][2] + m[1][3];
        res[2] =
            vec[0] * m[2][0] + vec[1] * m[2][1] + vec[2] * m[2][2] + m[2][3];
        float w =
            vec[0] * m[3][0] + vec[1] * m[3][1] + vec[2] * m[3][2] + m[3][3];
        if (w != 0.0f)
            res[0] /= w;
        res[1] /= w;
        res[2] /= w;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const mat44& mat)
    {
        os << mat.m[0][0] << ' ' << mat.m[0][1] << ' ' << mat.m[0][2] << ' '
           << mat.m[0][3] << std::endl;
        os << mat.m[1][0] << ' ' << mat.m[1][1] << ' ' << mat.m[1][2] << ' '
           << mat.m[1][3] << std::endl;
        os << mat.m[2][0] << ' ' << mat.m[2][1] << ' ' << mat.m[2][2] << ' '
           << mat.m[2][3] << std::endl;
        os << mat.m[3][0] << ' ' << mat.m[3][1] << ' ' << mat.m[3][2] << ' '
           << mat.m[3][3] << std::endl;
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
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos)
            pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}
}; // namespace

struct mesh
{
    const std::vector<vec3d> verts;
    const std::vector<verIdx> ver_indices;
    const std::vector<vec3d> texs;
    const std::vector<verIdx> tex_indices;
    const std::vector<vec3d> norms;
    const std::vector<verIdx> norm_indices;

    mesh(const std::vector<vec3d>& verts,
         const std::vector<verIdx>& ver_indices,
         const std::vector<vec3d>& texs,
         const std::vector<verIdx>& tex_indices,
         const std::vector<vec3d>& norms,
         const std::vector<verIdx>& norm_indices)
        : verts(verts)
        , ver_indices(ver_indices)
        , texs(texs)
        , tex_indices(tex_indices)
        , norms(norms)
        , norm_indices(norm_indices)
    {}

    std::vector<Tri3d> triangles(void) const
    {
        std::vector<Tri3d> tris;
        for (const verIdx& idx : ver_indices) {
            tris.push_back(Tri3d{ verts[std::get<0>(idx)],
                                  verts[std::get<1>(idx)],
                                  verts[std::get<2>(idx)] });
        }
        return tris;
    }
    Tri3d vertex(int i) const
    {
        auto v_indices = ver_indices[i];
        Tri3d _vertex;

        _vertex.pts[0] = verts[std::get<0>(v_indices)];
        _vertex.pts[1] = verts[std::get<1>(v_indices)];
        _vertex.pts[2] = verts[std::get<2>(v_indices)];
        return _vertex;
    }
    Tri3d texture(int i) const
    {
        auto t_indices = tex_indices[i];
        Tri3d texels;

        texels.pts[0] = texs[std::get<0>(t_indices)];
        texels.pts[1] = texs[std::get<1>(t_indices)];
        texels.pts[2] = texs[std::get<2>(t_indices)];
        return texels;
    };
    Tri3d normal(int i) const
    {
        auto n_indices = norm_indices[i];
        Tri3d norm;

        norm.pts[0] = norms[std::get<0>(n_indices)];
        norm.pts[1] = norms[std::get<1>(n_indices)];
        norm.pts[2] = norms[std::get<2>(n_indices)];
        return norm;
    }

    static mesh load_from_obj(const char* path)
    {

        std::ifstream in(path);
        std::vector<vec3d> verts;
        std::vector<verIdx> ver_indices;
        std::vector<vec3d> texs;
        std::vector<verIdx> tex_indices;
        std::vector<vec3d> norms;
        std::vector<verIdx> norm_indices;

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
                    norms.push_back(vertex);
                else if (line[1] == 't')
                    texs.push_back(vertex);
                else if (line[1] == ' ')
                    verts.push_back(vertex);
            }

            else if (line[0] == 'f') {
                std::string f[3];
                ss >> _type >> f[0] >> f[1] >> f[2];

                verIdx ver_idx, tex_idx, norm_idx;
                verIdx* idx;

                for (uint i = 0; i < 3; i++) {
                    std::vector<std::string> tokens;
                    for (uint j = 0; j < 3; j++) {
                        tokens.push_back(split(f[j], "/")[i]);
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
                ver_indices.push_back(ver_idx);
                tex_indices.push_back(tex_idx);
                norm_indices.push_back(norm_idx);
            }
        }

        return mesh{
            verts, ver_indices, texs, tex_indices, norms, norm_indices
        };
    }
};
