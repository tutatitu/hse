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
#endif