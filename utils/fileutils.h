#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <vector>
#include <common/point2d.h>

namespace FileUtils {
    std::vector<Point2Dd> getPointsFromFile(const std::string& filename);
    void generateRandomPointFile(
            const std::string& filename,
            double limit,
            int n);
}

#endif // FILEUTILS_H
