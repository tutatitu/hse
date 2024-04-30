#include "../models/models.cpp"
#include <algorithm>
#include <set>
#include <vector>

struct SegmentTree {
    std::vector<Rectangle> rectangles;
    std::vector<int> X, Y, Roots;
    std::vector<Node *> roots;

    SegmentTree(std::vector<Rectangle> &rectangles) : rectangles(rectangles) {
        compressCoordinates();
        buildTree();
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
            int mid = (l + r) / 2;
            if (v[mid] > target)
                r = mid - 1;
            else
                l = mid + 1;
        }

        return l - 1;
    }

    void buildTree() {
        std::vector<Side> sides;

        for (Rectangle &rectangle : rectangles) {
            sides.push_back(Side(lower_bound(X, rectangle.down.x),
                                 lower_bound(Y, rectangle.down.y),
                                 lower_bound(Y, rectangle.up.y),
                                 true));
            sides.push_back(Side(lower_bound(X, rectangle.up.x),
                                 lower_bound(Y, rectangle.down.y),
                                 lower_bound(Y, rectangle.up.y),
                                 false));
        }
        std::sort(sides.begin(), sides.end(), [](Side &a, Side &b) { return a.X < b.X; });

        Node *root = new Node();
        int prevX = sides[0].X;

        for (Side &side : sides) {
            if (side.X != prevX) {
                roots.push_back(root);
                Roots.push_back(prevX);
                prevX = side.X;
            }
            root = root->add(0, Y.size(), side.upY, side.downY, side.isOpening);
        }

        roots.push_back(root);
        Roots.push_back(prevX);
    }

    int solve(Point &point) {
        if (point.x < X[0] || point.y < Y[0] || point.x > X[X.size() - 1] || point.y > Y[Y.size() - 1])
            return 0;

        Point compressed(lower_bound(X, point.x), lower_bound(Y, point.y));

        return roots[lower_bound(Roots, compressed.x)]->get(0, Y.size(), compressed.y);
    }
};