#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include <mpi.h>

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
    if (argc < 3) {
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


    int numproc, rank;
    Timer timer{};
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int dotsPerThread = numDots / numproc;
    int numDotsIn = 0, result;

    numDotsIn = thread(dotsPerThread);

    MPI_Reduce(&numDotsIn, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    auto elapsedTime = timer.elapsed();

    if (rank == 0) {
        double squareArea = (maxx - minx) * (maxy - miny);
        auto allDots = dotsPerThread * numproc;
        std::cout << "Total generated dots: " << allDots << std::endl;
        std::cout << "Total dots in: " << result << std::endl;
        std::cout << "Square area: " << squareArea << std::endl;
        std::cout << "Circles area: " << ((double) result / allDots) * squareArea << std::endl;
        std::cout << "Elapsed time: " << elapsedTime << std::endl;
    }

    MPI_Finalize();
    return 0;
}