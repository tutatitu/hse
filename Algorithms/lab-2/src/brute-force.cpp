#include "models.cpp"
#include <vector>

struct BruteForce {
    std::vector<Rectangle> rectangles;

    BruteForce(std::vector<Rectangle> &rectangles) : rectangles(rectangles) {}

    int solve(Point &point) {
        int ans = 0;

        for (Rectangle &rectangle : rectangles) {
            if (rectangle.down.x <= point.x && rectangle.up.x > point.x && rectangle.down.y <= point.y && rectangle.up.x >= point.y)
                ++ans;
        }

        return ans;
    }
};