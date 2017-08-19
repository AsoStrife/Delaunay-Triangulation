#ifndef ADJACENCIES_H
#define ADJACENCIES_H

#include <Andrea/Headers/triangle.h>
class Triangle;

class Adjacencies{

private:
    Triangle* t = nullptr;
    Triangle* adjA = nullptr;
    Triangle* adjB = nullptr;
    Triangle* adjC = nullptr;

public:
    Adjacencies();

    void addNodes(Triangle* t1, Triangle* t2, Triangle* t3);
    void setAdjacencies(Triangle* adj);

    bool isAdjacencies(Triangle* t1, Triangle* t2);
};

#endif // ADJACENCIES_H
