#include "gtest/gtest.h"
#include "../src/window.h"

TEST(ZBuffer, simple) {
    using namespace std;

    int w=640, h=480;
    std::string win_name {"Test Rendering"};
    Window win {win_name, w, h};

    EXPECT_EQ(true, true);
}
