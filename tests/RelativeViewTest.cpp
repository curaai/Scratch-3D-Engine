#include "gtest/gtest.h"

#include "../src/user.h"
#include "../src/wall.h"
 

TEST(RelativeViewTest, WallTestOri00) {
    // identical 
    User* user = new User(30, 30, rgba{0, 0, 0, 0});
    user->ori = 0;
    Wall w {Point{10, 10}, Point{10, 20}, rgba{0, 0, 0, 0}}; 
    Point res = w.getRelativeCoord(w.a, user);
    EXPECT_EQ (res.x, w.a.x);
    EXPECT_EQ (res.y, w.a.y);
}

TEST(RelativeViewTest, WallTestOri90) {
    // rotation anti-clockwise 90 degrees
    User* user = new User(300, 300, rgba{0, 0, 0, 0});
    user->ori = 90;
    Wall w {Point{280, 280}, Point{280, 290}, rgba{0, 0, 0, 0}}; 
    Point res = w.getRelativeCoord(w.a, user);
    EXPECT_EQ (res.x, 280);
    EXPECT_EQ (res.y, 320);
}