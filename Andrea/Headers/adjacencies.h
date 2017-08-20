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
    Adjacencies(Triangle* t);

    //void addNodes(Triangle* t1, Triangle* t2, Triangle* t3);
    static void setAdjacencies(Triangle* adj1, Triangle* adj2, Adjacencies* father);
    static void setAdjacency(Triangle* adj, Adjacencies* father);
    static bool isAdjacencies(Triangle* t1, Triangle* t2);

    // Getter & Setter
    Triangle* getTriangle();
    Triangle* getAdjA();
    Triangle* getAdjB();
    Triangle* getAdjC();

    void setTriangle(Triangle* t);
    void setAdjA(Triangle* t);
    void setAdjB(Triangle* t);
    void setAdjC(Triangle* t);
};

#endif // ADJACENCIES_H
