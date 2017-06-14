#include "fileutils.h"

#include <fstream>
#include <random>
#include <iomanip>

namespace FileUtils {

std::vector<Point2Dd> getPointsFromFile(const std::string& filename) {

    std::vector<Point2Dd> points;
    std::ifstream infile;
    infile.open(filename);

    int n;
    infile >> n;

    for (int i = 0; i < n; i++) {
        double x = 0.0;
        double y = 0.0;
        infile >> std::setprecision(10) >> x >> std::setprecision(10) >> y;
        Point2Dd p(x,y);
        points.push_back(p);
    }

    infile.close();

    return points;
}

void generateRandomPointFile(const std::string& filename, double limit, int n) {
    std::setprecision(10);
    std::ofstream outfile;
    outfile.open(filename);

    double lower_bound = -limit;
    double upper_bound = limit;

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<double> dist(lower_bound,upper_bound); // distribution in range [0, 100]

    outfile << n << std::endl;

    for (int i = 0; i < n; i++) {
        double x = dist(rng);
        double y = dist(rng);
        outfile << std::setprecision(10) << x << " " << std::setprecision(10) << y << std::endl;
    }

    outfile.close();
}


}
