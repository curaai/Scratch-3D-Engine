#include "../src/window.h"
#include "gtest/gtest.h"

TEST(RenderPipeline, toScreen)
{
    int w = 640, h = 480;
    std::string win_name{ "Test Rendering" };
    // Window win {win_name, w, h};

    // auto screen_mat = win.screen_matrix();

    // // vec3d input[3] {, {0.9, 0.1, 0}, {0.45, 0.9, 0}};

    // vec3d input {0.1, 0.1, 0};
    // auto res = screen_mat * input;
    // EXPECT_EQ(round(res[0]), 352);
    // EXPECT_EQ(round(res[1]), 216);

    // input = {0.9, 0.1, 0};
    // res = screen_mat * input;
    // EXPECT_EQ(round(res[0]), 608);
    // EXPECT_EQ(round(res[1]), 216);

    // input = {0.45, 0.9, 0};
    // res = screen_mat * input;
    // EXPECT_EQ(round(res[0]), 464);
    // EXPECT_EQ(round(res[1]), 24);
}
