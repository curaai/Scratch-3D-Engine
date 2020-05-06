#include "gtest/gtest.h"
#include "../src/util_mat.h"

TEST(MatUtil, rotation) {
    mat44 rotation_mat = util::mat::getRotationMat(vec3d{90, 270, 180});
    vec3d input1 {10, 20, 30};
    auto res1 = rotation_mat * input1;
    EXPECT_EQ(round(res1.x), 20);
    EXPECT_EQ(round(res1.y), 30);
    EXPECT_EQ(round(res1.z), 10);
}

TEST(MatUtil, translate) {
    mat44 translate_mat = util::mat::getTranslationMat(vec3d{1, 2, 3});
    vec3d input1 {10, 20, 30};
    auto res1 = translate_mat * input1;
    EXPECT_EQ(res1.x, 11);
    EXPECT_EQ(res1.y, 22);
    EXPECT_EQ(res1.z, 33);
}

TEST(MatUtil, scale) {
    mat44 scale_mat = util::mat::getScaleMat(vec3d {2, 3, 4});
    vec3d input1 {10, 20, 30};
    auto res1 = scale_mat * input1;
    EXPECT_EQ(res1.x, 20);
    EXPECT_EQ(res1.y, 60);
    EXPECT_EQ(res1.z, 120);
}

TEST(MatUtil, combination) {
    mat44 scale_mat = util::mat::getScaleMat(vec3d {2, 3, 4});
    mat44 translate_mat = util::mat::getTranslationMat(vec3d {1, 2, 3});
    mat44 rotate_mat = util::mat::getRotationMat(vec3d {90, 270, 180});
    mat44 final_mat = rotate_mat * translate_mat * scale_mat;

    vec3d input1 {1, 2, 3};
    // scale 
    // 1, 2, 3 -> 2, 6, 12
    // translate  
    // 2, 6, 12 -> 3, 8, 15
    // rotate 
    // 3, 8, 15 -> 8, 15, 3

    auto res1 = final_mat * input1;
    EXPECT_EQ(round(res1.x), 8);
    EXPECT_EQ(round(res1.y), 15);
    EXPECT_EQ(round(res1.z), 3);
}