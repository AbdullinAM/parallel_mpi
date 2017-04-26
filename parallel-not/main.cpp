#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include "Timer.h"

struct circle {
    double x;
    double y;
    double r;
};

double minx = std::numeric_limits<double>::max();
double miny = std::numeric_limits<double>::max();
double maxx = std::numeric_limits<double>::min();
double maxy = std::numeric_limits<double>::min();
std::vector<circle> circles;

bool inCircles(double x, double y) {
    for (auto it : circles) {
        auto dx = std::abs(x - it.x);
        auto dy = std::abs(y - it.y);
        if (dx * dx + dy * dy - it.r * it.r < 0) return true;
    }
    return false;
}


int thread(int numRepeats) {
    std::random_device r;
    std::default_random_engine re(r());
    std::uniform_real_distribution<double> xrand(minx, maxx);
    std::uniform_real_distribution<double> yrand(miny, maxy);
    int countIn = 0;
    for (auto i = 0; i < numRepeats; ++i) {
        double x = xrand(re);
        double y = yrand(re);
        if (inCircles(x, y)) ++countIn;
    }
    return countIn;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: ./parallel *input file* *num dots*" << std::endl;
        return -1;
    }
    std::string inpFile = std::string(argv[1]);
    int numDots = atoi(argv[2]);

    if (numDots < 1) {
        std::cout << "Num dots and num threads must be bigger than 0" << std::endl;
        return -1;
    }

    double x, y, r;
    std::ifstream in(inpFile);
    while (in >> x) {
        in >> y >> r;
        circles.push_back({x, y, r});
    }

    for (auto it : circles) {
        if (it.x - it.r < minx) minx = it.x - it.r;
        if (it.x + it.r > maxx) maxx = it.x + it.r;
        if (it.y - it.r < miny) miny = it.y - it.r;
        if (it.y + it.r > maxy) maxy = it.y + it.r;
    }

    Timer timer{};
    int numDotsIn = thread(numDots);
    auto elapsedTime = timer.elapsed();

    double squareArea = (maxx - minx) * (maxy - miny);
    std::cout << "Total generated dots: " << numDots << std::endl;
    std::cout << "Total dots in: " << numDotsIn << std::endl;
    std::cout << "Square area: " << squareArea << std::endl;
    std::cout << "Circles area: " << ((double) numDotsIn / numDots) * squareArea << std::endl;
    std::cout << "Elapsed time: " << elapsedTime << std::endl;

    return 0;
}