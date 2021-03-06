#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include <pthread.h>

#include "Timer.h"

struct circle {
    double x;
    double y;
    double r;
};

std::vector<circle> circles;
double minx = std::numeric_limits<double>::max();
double miny = std::numeric_limits<double>::max();
double maxx = std::numeric_limits<double>::min();
double maxy = std::numeric_limits<double>::min();

bool inCircles(double x, double y) {
    for (auto it : circles) {
        auto dx = std::abs(x - it.x);
        auto dy = std::abs(y - it.y);
        if (dx * dx + dy * dy - it.r * it.r < 0) return true;
    }
    return false;
}


void* thread(void* arg) {
    auto numRepeats = *(int*)arg;
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
    pthread_exit((void*) countIn);
}

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cout << "Usage: ./parallel *input file* *num dots* *num threads* " << std::endl;
        return -1;
    }
    std::string inpFile = std::string(argv[1]);
    auto numDots = atoi(argv[2]);
    auto numThreads = atoi(argv[3]);

    if (numDots < 1 || numThreads < 1) {
        std::cout << "Num dots and num threads must be bigger than 0" << std::endl;
        return -1;
    }
    if (numDots < numThreads) {
        std::cout << "Num dots must be more than num threads" << std::endl;
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


    int dotsPerThread = numDots / numThreads;
    pthread_t* threads = new pthread_t[numThreads];

    Timer timer{};
    for (auto i = 0; i < numThreads; ++i) {
        if (pthread_create(&threads[i], NULL, thread, &dotsPerThread)) {
            std::cout << "Cannot create thread" << std::endl;
            return -1;
        }
    }

    int numDotsIn = 0;
    int retVal = 0;

    for (auto i = 0; i < numThreads; ++i) {
        if (pthread_join(threads[i], (void**)&retVal)) {
            std::cout << "Cannot join thread" << std::endl;
            return -1;
        }

        numDotsIn += retVal;
    }
    delete[] threads;
    auto elapsedTime = timer.elapsed();

    double squareArea = (maxx - minx) * (maxy - miny);
    auto allDots = dotsPerThread * numThreads;
    std::cout << "Total generated dots: " << dotsPerThread * numThreads << std::endl;
    std::cout << "Total dots in: " << numDotsIn << std::endl;
    std::cout << "Square area: " << squareArea << std::endl;
    std::cout << "Circles area: " << ((double)numDotsIn / allDots) * squareArea << std::endl;
    std::cout << "Elapsed time: " << elapsedTime << std::endl;
    return 0;
}