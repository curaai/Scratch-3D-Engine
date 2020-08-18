#include "../src/util_mat.h"
#include "gtest/gtest.h"

TEST(MatUtil, rotation)
{
    Mat44 rotation_mat = util::mat::GetRotationMat(vec3d{ 90, 270, 180 });
    vec3d input1{ 10, 20, 30 };
    auto res1 = rotation_mat * input1;
    EXPECT_EQ(round(res1[0]), 20);
    EXPECT_EQ(round(res1[1]), 30);
    EXPECT_EQ(round(res1[2]), 10);
}

TEST(MatUtil, translate)
{
    Mat44 translate_mat = util::mat::GetTranslationMat(vec3d{ 1, 2, 3 });
    vec3d input1{ 10, 20, 30 };
    auto res1 = translate_mat * input1;
    EXPECT_EQ(res1[0], 11);
    EXPECT_EQ(res1[1], 22);
    EXPECT_EQ(res1[2], 33);
}

TEST(MatUtil, scale)
{
    Mat44 scale_mat = util::mat::GetScaleMat(vec3d{ 2, 3, 4 });
    vec3d input1{ 10, 20, 30 };
    auto res1 = scale_mat * input1;
    EXPECT_EQ(res1[0], 20);
    EXPECT_EQ(res1[1], 60);
    EXPECT_EQ(res1[2], 120);
}

TEST(MatUtil, combination)
{
    Mat44 scale_mat = util::mat::GetScaleMat(vec3d{ 2, 3, 4 });
    Mat44 translate_mat = util::mat::GetTranslationMat(vec3d{ 1, 2, 3 });
    Mat44 rotate_mat = util::mat::GetRotationMat(vec3d{ 90, 270, 180 });
    Mat44 final_mat = rotate_mat * translate_mat * scale_mat;

    vec3d input1{ 1, 2, 3 };
    // scale
    // 1, 2, 3 -> 2, 6, 12
    // translate
    // 2, 6, 12 -> 3, 8, 15
    // rotate
    // 3, 8, 15 -> 8, 15, 3

    auto res1 = final_mat * input1;
    EXPECT_EQ(round(res1[0]), 8);
    EXPECT_EQ(round(res1[1]), 15);
    EXPECT_EQ(round(res1[2]), 3);
}