#include "models.cpp"
#include <set>
#include <vector>

struct CompressedMap {
    std::vector<Rectangle> rectangles;
    std::vector<int> X, Y;
    std::vector<std::vector<int>> map;

    CompressedMap(std::vector<Rectangle> &rectangles) : rectangles(rectangles) {
        compressCoordinates();
        buildMap();
    }

    void compressCoordinates() {
        std::set<int> tempX, tempY;

        for (Rectangle &rectangle : rectangles) {
            tempX.insert(rectangle.down.x);
            tempX.insert(rectangle.up.x);
            tempX.insert(rectangle.up.x + 1);
            tempY.insert(rectangle.down.y);
            tempY.insert(rectangle.up.y);
            tempY.insert(rectangle.up.y + 1);
        }

        X.assign(tempX.begin(), tempX.end());
        Y.assign(tempY.begin(), tempY.end());
    }

    int lower_bound(std::vector<int> &v, int target) {
        int l = 0, r = v.size() - 1;

        while (l <= r) {
            int m = (l + r) / 2;
            if (v[m] > target)
                r = m - 1;
            else
                l = m + 1;
        }

        return l;
    }

    void buildMap() {
        map.assign(X.size(), std::vector<int>(Y.size(), 0));

        for (Rectangle &rectangle : rectangles) {
            Point down(lower_bound(X, rectangle.down.x), lower_bound(Y, rectangle.down.y));
            Point up(lower_bound(X, rectangle.up.x), lower_bound(Y, rectangle.up.y));

            for (int i = down.x; i < up.x; ++i) {
                for (int j = down.y; j < up.y; ++j)
                    ++map[i][j];
            }
        }
    }

    int solve(Point &point) {
        if (point.x < X[0] || point.y < Y[0])
            return 0;

        Point compressed(lower_bound(X, point.x), lower_bound(Y, point.y));

        return map[compressed.x][compressed.y];
    }
};