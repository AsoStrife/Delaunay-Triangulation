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

    // Funzioni per controllare che un punto sia in un triangolo
    static float sign (const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);
    static bool pointInTriangle (const Point2Dd& pt, Triangle* t);

    static bool checkIfPointAlreadyExist(Dag *dagNode, const Point2Dd& p);
    static bool checkPointInTriangle(const Point2Dd& p, Triangle* triangle);

    // Cerco in quale triangolo cade il nuovo punto
    static Dag* navigate(Dag* dagNode, const Point2Dd& p);
    static Triangle* navigateAdj(Dag* dagNode, Triangle* tr);

    // Aggiungo un nodo figlio al padre oppure tutti e 3 i figli di un padre
    static void addNode(Dag* node, Dag* dagNodefather);

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
