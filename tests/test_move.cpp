#include "../src/User.h"
#include "gtest/gtest.h"

class UserControlTest : public ::testing::Test
{
public:
    UserControlTest()
        : Test()
    {
        user = new User(vec3d{ 0, 0, 0 }, 4 / 3, 60);
    }

protected:
    virtual void SetUp()
    {
        user->setCameraPos(vec3d{ 0, 0, 0 });
        user->setCameraRotation(vec3d{ 0, 0, 0 });
    }

    User* user;
};

TEST_F(UserControlTest, turn)
{
    const float turn_speed = user->turn_speed;

    user->turn(EUserTurn::LEFT);
    vec3d v{ 0, -turn_speed, 0 };
    EXPECT_EQ(user->rotation, v);

    user->turn(EUserTurn::RIGHT);
    v += vec3d{ 0, turn_speed, 0 };
    EXPECT_EQ(user->rotation, v);

    user->turn(EUserTurn::UP);
    v += vec3d{ -turn_speed, 0, 0 };
    EXPECT_EQ(user->rotation, v);

    user->turn(EUserTurn::DOWN);
    v += vec3d{ turn_speed, 0, 0 };
    EXPECT_EQ(user->rotation, v);
}

TEST_F(UserControlTest, move)
{
    const float move_speed = user->move_speed;
    vec3d v{ 0, 0, 0 };

    user->move(EUserMove::FORWARD);
    v += vec3d{ 0, 0, move_speed };
    EXPECT_EQ(user->pos, v);

    user->move(EUserMove::BACKWARD);
    v += vec3d{ 0, 0, -move_speed };
    EXPECT_EQ(user->pos, v);

    user->move(EUserMove::RIGHT);
    v += vec3d{ move_speed, 0, 0 };
    EXPECT_EQ(user->pos, v);

    user->move(EUserMove::LEFT);
    v += vec3d{ -move_speed, 0, 0 };
    EXPECT_EQ(user->pos, v);
}

TEST_F(UserControlTest, turn_and_move1)
{
    const float move_speed = user->move_speed;
    vec3d v{ 0, 0, 0 };

    // turn 90 degree to x axis
    for (int i = 0; i < 18; i++)
        user->turn(EUserTurn::LEFT);
    user->move(EUserMove::FORWARD);
    // v += vec3d{ 0, 0, move_speed };
    EXPECT_EQ(user->pos[0], -move_speed);
}

TEST_F(UserControlTest, turn_and_move2)
{
    const float move_speed = user->move_speed;
    vec3d v{ 0, 0, 0 };

    // turn 90 degree to x axis
    for (int i = 0; i < 9; i++)
        user->turn(EUserTurn::LEFT);
    for (int i = 0; i < 9; i++)
        user->turn(EUserTurn::UP);
    user->move(EUserMove::FORWARD);
    // v += vec3d{ 0, 0, move_speed };
    EXPECT_FLOAT_EQ(user->pos[0], -move_speed / 2);
    EXPECT_FLOAT_EQ(user->pos[2], move_speed / 2);
}
