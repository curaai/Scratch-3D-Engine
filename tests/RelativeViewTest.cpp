#include <cmath>

#include "gtest/gtest.h"

#include "../src/user.h"
#include "../src/wall.h"
 

TEST(RelativeViewTest, WallTestOri00) {
    // identical 
    User* user = new User(30, 30, rgba{0, 0, 0, 0});
    user->ori = 0;
    Wall w {Point{10, 10}, Point{10, 20}, rgba{0, 0, 0, 0}}; 
    Point res = w.getRelativeCoord(w.a, user);
    EXPECT_EQ (round(res.x), 10);
    EXPECT_EQ (res.y, 50);
    Point res2 = w.getRelativeCoord(w.b, user);
    EXPECT_EQ (round(res2.x), 20);
    EXPECT_EQ (round(res2.y), 50);
}

TEST(RelativeViewTest, WallTestOri90) {
    // rotation anti-clockwise 90 degrees
    User* user = new User(300, 300, rgba{0, 0, 0, 0});
    user->ori = 90;
    Wall w {Point{280, 280}, Point{280, 290}, rgba{0, 0, 0, 0}}; 
    Point res2 = w.getRelativeCoord(w.b, user);
    EXPECT_EQ (res2.x, 280);
    EXPECT_EQ (res2.y, 290);
}

TEST(RelativeViewTest, WallTestOri270) {
    User* user = new User(300, 300, rgba{0, 0, 0, 0});
    user->ori = 270;
    Wall w {Point{280, 280}, Point{280, 290}, rgba{0, 0, 0, 0}}; 
    Point res = w.getRelativeCoord(w.a, user);
    EXPECT_EQ (res.x, 320);
    EXPECT_EQ (res.y, 320);
    Point res2 = w.getRelativeCoord(w.b, user);
    EXPECT_EQ (res2.x, 320);
    EXPECT_EQ (res2.y, 310);
}