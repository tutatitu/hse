#include "brute-force.cpp"
#include "compressed-map.cpp"
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
    std::vector<int> prepare[3], run[3];
    std::vector<std::string> solution = {"BruteForce", "CompressedMap", ""};

    Benchmark() {
        int N[] = {10, 20, 50, 80, 100, 150, 250, 300, 400};
        std::cout << "                                      Prepare\n"
                  << "            ";
        for (int n : N) {
            std::cout << n << ' ';
            test(n);
        }
        for (int i = 0; i < 3; i++) {
            std::cout << '\n'
                      << solution[i] << ' ';
            for (int time : prepare[i]) {
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
            for (int time : run[i]) {
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
        BruteForce bruteforce = BruteForce(rectangles);
        auto end = std::chrono::steady_clock::now();
        int prepareBrute = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        prepare[0].push_back(prepareBrute);

        start = std::chrono::steady_clock::now();
        CompressedMap compressedmap = CompressedMap(rectangles);
        end = std::chrono::steady_clock::now();
        int prepareMap = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        prepare[1].push_back(prepareMap);

        // run
        start = std::chrono::steady_clock::now();
        for (Point &point : points)
            bruteforce.solve(point);
        end = std::chrono::steady_clock::now();
        int runBrute = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        run[0].push_back(runBrute);

        start = std::chrono::steady_clock::now();
        for (Point &point : points)
            compressedmap.solve(point);
        end = std::chrono::steady_clock::now();
        int runMap = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        run[1].push_back(runMap);
    }

private:
    Generate generate;
};