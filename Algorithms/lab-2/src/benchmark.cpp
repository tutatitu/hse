#include "../solutions/brute-force.cpp"
#include "../solutions/compressed-map.cpp"
#include "../solutions/segment-tree.cpp"
#include <chrono>
#include <iostream>
#include <string>
typedef unsigned long long ull;

struct Generate {
    int pow_mod(ull a, int x, ull m) {
        ull ans = 1;

        while (x > 0) {
            if (x & 1)
                ans = (ans * a) % m;
            a = (a * a) % m;
            x >>= 1;
        }

        return ans % m;
    }

    std::vector<Rectangle> rectangles(int N) {
        std::vector<Rectangle> ans;

        for (int i = 0; i < N; ++i)
            ans.push_back(Rectangle(10 * i, 10 * i, 10 * (2 * N - i), 10 * (2 * N - i)));

        return ans;
    }

    std::vector<Point> points(int N) {
        int p_x = 1000003, p_y = 1000151;
        std::vector<Point> ans;

        for (int i = 0; i < N; ++i)
            ans.push_back(Point(pow_mod(p_x * i, 31, 20 * N), pow_mod(p_y * i, 31, 20 * N)));

        return ans;
    }
};

class Benchmark {
public:
    std::vector<ull> prepare[3], run[3];
    std::vector<std::string> solution = {"BruteForce", "CompressedMap", "SegmentTree"};

    Benchmark() {
        int N[] = {10, 20, 50, 80, 100, 150, 250, 300, 400, 450,
                   500, 600, 700, 800, 900, 1000, 1300, 1500, 2000};
        std::cout << "                                      Prepare\n"
                  << "            ";
        for (int n : N) {
            std::cout << n << ' ';
            test(n);
        }
        for (int i = 0; i < 3; i++) {
            std::cout << '\n'
                      << solution[i] << ' ';
            for (ull time : prepare[i]) {
                std::cout << time << ' ';
            }
        }
        std::cout << "\n\n                                                              Run\n"
                  << "          ";
        for (int n : N)
            std::cout << n << "    ";
        for (int i = 0; i < 3; i++) {
            std::cout << '\n'
                      << solution[i] << ' ';
            for (ull time : run[i]) {
                std::cout << time << ' ';
            }
        }
    }

    void test(int N) {
        std::vector<Rectangle> rectangles = generate.rectangles(N);
        std::vector<Point> points = generate.points(N);
        // std::cout << N << '\n';

        // prepare
        auto start = std::chrono::steady_clock::now();
        BruteForce brute_force = BruteForce(rectangles);
        auto end = std::chrono::steady_clock::now();
        ull prepareBrute = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        prepare[0].push_back(prepareBrute);

        start = std::chrono::steady_clock::now();
        CompressedMap compressed_map = CompressedMap(rectangles);
        end = std::chrono::steady_clock::now();
        ull prepareMap = (ull)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        prepare[1].push_back(prepareMap);

        start = std::chrono::steady_clock::now();
        SegmentTree segment_tree = SegmentTree(rectangles);
        end = std::chrono::steady_clock::now();
        ull prepareSeg = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        prepare[2].push_back(prepareSeg);

        // run
        start = std::chrono::steady_clock::now();
        for (Point &point : points)
            brute_force.solve(point);
        end = std::chrono::steady_clock::now();
        ull runBrute = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        run[0].push_back(runBrute);

        start = std::chrono::steady_clock::now();
        for (Point &point : points)
            compressed_map.solve(point);
        end = std::chrono::steady_clock::now();
        ull runMap = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        run[1].push_back(runMap);

        start = std::chrono::steady_clock::now();
        for (Point &point : points)
            segment_tree.solve(point);
        end = std::chrono::steady_clock::now();
        ull runSeg = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        run[2].push_back(runSeg);
    }

private:
    Generate generate;
};