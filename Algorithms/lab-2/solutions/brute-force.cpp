#include "../models/models.cpp"
#include <vector>

struct BruteForce {
    std::vector<Rectangle> rectangles;

    BruteForce(std::vector<Rectangle> &rectangles) : rectangles(rectangles) {}

    int solve(Point &point) {
        int ans = 0;

        for (Rectangle &rectangle : rectangles) {
            if (rectangle.down.x <= point.x && point.x < rectangle.up.x && rectangle.down.y <= point.y && point.y < rectangle.up.y)
                ++ans;
        }

        return ans;
    }
};