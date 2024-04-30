#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

struct Rectangle {
    Point down, up;

    Rectangle(int x1, int y1, int x2, int y2) : down(Point(x1, y1)), up(Point(x2, y2)) {}
};

struct Node {
    int sum;
    Node *left, *right;

    Node(Node *left, Node *right, int sum) : left(left), right(right), sum(sum) {}

    Node(Node *node) : left(node->left), right(node->right), sum(node->sum) {}

    Node() : left(nullptr), right(nullptr), sum(0) {}

    Node *add(int l, int r, int start, int end, bool isOpening) {
        if (l >= end || r <= start)
            return this;

        Node *node = new Node(this);
        if (start <= l && r <= end) {

            node->sum += (isOpening ? 1 : -1);
            return node;
        }

        int mid = (l + r) / 2;
        // Node *node(this);

        if (left == nullptr)
            left = new Node();

        if (right == nullptr)
            right = new Node();

        node->left = left->add(l, mid, start, end, isOpening);
        node->right = right->add(mid, r, start, end, isOpening);

        return node;
    }

    int get(int l, int r, int target) {
        if (r - l == 1)
            return sum;

        int mid = (l + r) / 2;

        if (target < mid) {
            if (left == nullptr)
                return sum;
            return sum + left->get(l, mid, target);
        }
        if (right == nullptr)
            return sum;
        return sum + right->get(mid, r, target);
    }
};

struct Side {
    int X, upY, downY;
    bool isOpening;

    Side(int X, int upY, int downY, bool isOpening) : X(X), upY(upY), downY(downY), isOpening(isOpening) {}
};

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

int main() {
    std::vector<Rectangle> rectangles;
    std::vector<Point> points;
    int n, m, x1, y1, x2, y2;

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        rectangles.push_back(Rectangle(x1, y1, x2, y2));
    }

    std::cin >> m;

    if (n == 0) {
        for (int i = 0; i < m; ++i)
            std::cout << 0 << ' ';
        return 0;
    }

    for (int i = 0; i < m; i++) {
        std::cin >> x1 >> y1;
        points.push_back(Point(x1, y1));
    }

    SegmentTree segment_tree = SegmentTree(rectangles);

    for (Point &point : points) {
        std::cout << segment_tree.solve(point) << ' ';
    }
}