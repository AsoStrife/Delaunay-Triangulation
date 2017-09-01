#ifndef ADJACENCIES_H
#define ADJACENCIES_H

#include <Andrea/Headers/triangle.h>

class Triangle;

class Adjacencies{

public:
    Adjacencies();

    static void setAdjacencies(Triangle* tr1, Triangle* tr2, Triangle* tr3, Triangle* trFather);

    static void setAdjacency(Triangle *triangle, Triangle *adjTriangle);

    static void setAdjacenciesAfterFlip(Triangle* tr1, Triangle* tr2, Triangle* trFather1, Triangle* trFather2);

    static bool isAdjacencies(Triangle* tr1, Triangle* tr2);

    static bool isAdjacenciesForTwoPoints(Triangle* tr, const Point2Dd& p1, const Point2Dd& p2);

    static Point2Dd* getThirdPoint(Triangle* tr, Point2Dd* p1, Point2Dd* p2);

    static void overrideAdjacency(Triangle* triangle, Triangle *adjTriangle);


};

#endif // ADJACENCIES_H
