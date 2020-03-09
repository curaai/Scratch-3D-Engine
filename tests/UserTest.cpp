#include "gtest/gtest.h"

#include "../src/user.h"

TEST(UserTest, moveOnOri0) {
    // identical 
    User user {30, 30, rgba{0, 0, 0, 0}};
    user.ori = 0;
    user.move(SDLK_w);
    EXPECT_EQ (user.pos.x, 40);
    EXPECT_EQ (user.pos.y, 30);
}

TEST(UserTest, moveOnOri90) {
    // identical 
    User user {30, 30, rgba{0, 0, 0, 0}};
    user.ori = 90;
    user.move(SDLK_w);
    EXPECT_EQ (user.pos.x, 30);
    EXPECT_EQ (user.pos.y, 20);
}