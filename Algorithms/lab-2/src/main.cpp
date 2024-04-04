#include "benchmark.cpp"

int main() {
    Benchmark();

    std::vector<Rectangle> rectangles;
    int x1, y1, x2, y2;

    for (int i = 0; i < 4; i++) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        rectangles.push_back(Rectangle(x1, y1, x2, y2));
    }

    BruteForce bruteforce = BruteForce(rectangles);
    CompressedMap compressedmap = CompressedMap(rectangles);

    for (int i = 0; i < 6; i++) {
        std::cin >> x1 >> y1;
        Point point(x1, y1);
        std::cout << bruteforce.solve(point) << ' ';
        std::cout << compressedmap.solve(point) << '\n';
    }
}