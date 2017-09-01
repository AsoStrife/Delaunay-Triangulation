#ifndef DAG_H
#define DAG_H

#include <common/arrays.h>
#include <viewer/objects/objects.h>
#include <Andrea/Headers/triangle.h>
#include <Andrea/Headers/adjacencies.h>

class Triangle;

class Dag {

private:
        Triangle* t = nullptr;
        Dag* childA = nullptr;
        Dag* childB = nullptr;
        Dag* childC = nullptr;

public:
    Dag();
    Dag(Triangle* t);

    static bool pointInTriangle (const Point2Dd& pt, Triangle* tr);

    static bool checkPointIsVertexOfTriangle(const Point2Dd& p, Triangle* triangle);

    static Dag* navigate(Dag* dagNode, const Point2Dd& p);

    static void addNode(Dag* node, Dag* dagNodefather);

    // Getter & Setter
    Dag* getChildA();
    Dag* getChildB();
    Dag* getChildC();
    Triangle* getTriangle();

    void setChildA(Dag* t);
    void setChildB(Dag* t);
    void setChildC(Dag* t);
    void setTriangle(Triangle* t);
};

#endif // DAG_H
