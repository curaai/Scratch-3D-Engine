#include "../src/Mesh.h"
#include "../src/resource.h"
#include "gtest/gtest.h"

TEST(Mesh, loadObject)
{
    auto cube = Mesh::loadFromObj("resource/cube.obj");

    std::vector<vec3d> vertexes = {
        { 1, -1, -1 }, { 1, -1, 1 }, { -1, -1, 1 }, { -1, -1, -1 },
        { 1, 1, -1 },  { 1, 1, 1 },  { -1, 1, 1 },  { -1, 1, -1 },
    };
    std::vector<verIdx> vert_indices = {
        { 2 - 1, 3 - 1, 4 - 1 }, { 8 - 1, 7 - 1, 6 - 1 },
        { 5 - 1, 6 - 1, 2 - 1 }, { 6 - 1, 7 - 1, 3 - 1 },
        { 3 - 1, 7 - 1, 8 - 1 }, { 1 - 1, 4 - 1, 8 - 1 },
        { 1 - 1, 2 - 1, 4 - 1 }, { 5 - 1, 8 - 1, 6 - 1 },
        { 1 - 1, 5 - 1, 2 - 1 }, { 2 - 1, 6 - 1, 3 - 1 },
        { 4 - 1, 3 - 1, 8 - 1 }, { 5 - 1, 1 - 1, 8 - 1 }
    };
    std::vector<vec3d> texture = {
        { 1.000000, 0.333333, 0 }, { 1.000000, 0.666667, 0 },
        { 0.666667, 0.666667, 0 }, { 0.666667, 0.333333, 0 },
        { 0.666667, 0.000000, 0 }, { 0.000000, 0.333333, 0 },
        { 0.000000, 0.000000, 0 }, { 0.333333, 0.000000, 0 },
        { 0.333333, 1.000000, 0 }, { 0.000000, 1.000000, 0 },
        { 0.000000, 0.666667, 0 }, { 0.333333, 0.333333, 0 },
        { 0.333333, 0.666667, 0 }, { 1.000000, 0.000000, 0 },
    };
    std::vector<verIdx> tex_indices = {
        { 1 - 1, 2 - 1, 3 - 1 },   { 1 - 1, 4 - 1, 5 - 1 },
        { 6 - 1, 7 - 1, 8 - 1 },   { 8 - 1, 5 - 1, 4 - 1 },
        { 9 - 1, 10 - 1, 11 - 1 }, { 12 - 1, 13 - 1, 11 - 1 },
        { 4 - 1, 1 - 1, 3 - 1 },   { 14 - 1, 1 - 1, 5 - 1 },
        { 12 - 1, 6 - 1, 8 - 1 },  { 12 - 1, 8 - 1, 4 - 1 },
        { 13 - 1, 9 - 1, 11 - 1 }, { 6 - 1, 12 - 1, 11 - 1 }
    };
    std::vector<vec3d> norm = {
        { 0.000000, -1.000000, 0.000000 },   { 0.000000, 1.000000, 0.000000 },
        { 1.000000, 0.000000, 0.000000 },    { -0.000000, 0.000000, 1.000000 },
        { -1.000000, -0.000000, -0.000000 }, { 0.000000, 0.000000, -1.000000 }
    };
    std::vector<verIdx> norm_indices = {
        { 1 - 1, 1 - 1, 1 - 1 }, { 2 - 1, 2 - 1, 2 - 1 },
        { 3 - 1, 3 - 1, 3 - 1 }, { 4 - 1, 4 - 1, 4 - 1 },
        { 5 - 1, 5 - 1, 5 - 1 }, { 6 - 1, 6 - 1, 6 - 1 },
        { 1 - 1, 1 - 1, 1 - 1 }, { 2 - 1, 2 - 1, 2 - 1 },
        { 3 - 1, 3 - 1, 3 - 1 }, { 4 - 1, 4 - 1, 4 - 1 },
        { 5 - 1, 5 - 1, 5 - 1 }, { 6 - 1, 6 - 1, 6 - 1 },
    };

    for (int i = 0; i < cube.vb.vertexes.size(); i++)
        EXPECT_EQ(cube.vb.vertexes[i], vertexes[i]);
    for (int i = 0; i < cube.vb.indices.size(); i++)
        EXPECT_EQ(cube.vb.indices[i], vert_indices[i]);
    for (int i = 0; i < cube.tex_vb.vertexes.size(); i++)
        EXPECT_EQ(cube.tex_vb.vertexes[i], texture[i]);
    for (int i = 0; i < cube.tex_vb.indices.size(); i++)
        EXPECT_EQ(cube.tex_vb.indices[i], tex_indices[i]);
    for (int i = 0; i < cube.norm_vb.vertexes.size(); i++)
        EXPECT_EQ(cube.norm_vb.vertexes[i], norm[i]);
    for (int i = 0; i < cube.norm_vb.indices.size(); i++)
        EXPECT_EQ(cube.norm_vb.indices[i], norm_indices[i]);
}

TEST(Mesh, pick)
{
    auto cube = Mesh::loadFromObj("resource/cube.obj");

    auto vertex = cube.vertex(0);
    vec3d _vertex[3]{ { 1, -1, 1 }, { -1, -1, 1 }, { -1, -1, -1 } };
    Tri3d t{ _vertex[0], _vertex[1], _vertex[2] };
    EXPECT_EQ(true, t == vertex);

    auto texture = cube.texture(0);
    _vertex[0] = { 1, 0.333333, 0 };
    _vertex[1] = { 1, 0.666667, 0 };
    _vertex[2] = { 0.666667, 0.666667, 0 };
    t = Tri3d{ _vertex[0], _vertex[1], _vertex[2] };
    EXPECT_EQ(true, t == texture);

    auto norm = cube.normal(0);
    _vertex[0] = { 0, -1, 0 };
    _vertex[1] = { 0, -1, 0 };
    _vertex[2] = { 0, -1, 0 };
    t = Tri3d{ _vertex[0], _vertex[1], _vertex[2] };
    EXPECT_EQ(true, t == norm);
}