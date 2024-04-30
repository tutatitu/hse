#ifndef MODELS_CPP
#define MODELS_CPP
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
#endif