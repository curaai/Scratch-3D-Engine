#include "gtest/gtest.h"
#include "../src/window.h"

TEST(ZBuffer, simple) {
    using namespace std;

    int w=640, h=480;
    std::string win_name {"Test Rendering"};
    Window win {win_name, w, h};

    // front simple triangle 
    // win.render()

    vector<vec3d> verteces1;
    verteces1.push_back(vec3d {0, 0, 0});
    verteces1.push_back(vec3d {1, 0, 0});
    verteces1.push_back(vec3d {0.5, 1, 0});
    vector<verIdx> indices1;
    indices1.push_back(verIdx{0, 1, 2});
    vector<SDL_Color> colors1;
    colors1.push_back(SDL_Color{255, 0, 0, 255});
    mesh m1 {verteces1, indices1, colors1};
    Drawable obj1{m1};

    vector<vec3d> verteces2;
    verteces2.push_back(vec3d {0, 0, 0.1});
    verteces2.push_back(vec3d {0, 1, 0.1});
    verteces2.push_back(vec3d {0.5, 0, 0.1});
    vector<verIdx> indices2;
    indices2.push_back(verIdx{0, 1, 2});
    vector<SDL_Color> colors2;
    colors2.push_back(SDL_Color{0, 0, 255, 255});
    mesh m2 {verteces2, indices2, colors2};
    Drawable obj2{m2};

    vector<pair<triangle, bool>> t1;
    vector<pair<triangle, bool>> t2;
    for(const auto& t : m1.triangles()) 
        t1.push_back({t, true});
    for(const auto& t : m2.triangles()) 
        t2.push_back({t, true});

    win.render(obj1, t1);
    win.render(obj2, t2);

    auto pixel1 = win.pixel(321, 239);
    EXPECT_EQ(pixel1.r, 255);
    EXPECT_EQ(pixel1.g, 0);
    EXPECT_EQ(pixel1.b, 0);

    auto pixel2 = win.pixel(320, 1);
    EXPECT_EQ(pixel2.r, 0);
    EXPECT_EQ(pixel2.g, 0);
    EXPECT_EQ(pixel2.b, 255);
}


// TEST(ZBuffer, fill_target_indices) {
//     vector<vec3d> v;
//     v.push_back({0, 0, 0});
//     triangle t;
//     t.pts[0] = vec3d {5, 0, 0}; 
//     t.pts[1] = vec3d {2, 4, 0};
//     t.pts[2] = vec3d {8, 7, 0};
//     auto lines = util::draw::triangle_indices(t);
//     for(auto line : lines) {
//         std::cout << (int)line.a.x << ' ' << (int)line.a.y<< ' ';
//         std::cout << (int)line.b.x << ' '<< (int)line.b.y << std::endl;
//     }
// }