#include "gtest/gtest.h"
#include "../src/util_mat.h"

TEST(MatUtil, rotation) {
    mat44 rotation_mat = util::mat::getRotationMat(vec3d{90, 270, 180});
    vec3d input1 {10, 20, 30};
    auto res1 = rotation_mat * input1;
    EXPECT_EQ(res1.x, 20);
    EXPECT_EQ(res1.y, 30);
    EXPECT_EQ(round(res1.z), 10);
}