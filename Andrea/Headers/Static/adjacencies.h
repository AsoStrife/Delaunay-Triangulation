#ifndef ADJACENCIES_H
#define ADJACENCIES_H

#include <Andrea/Headers/DataStructures/triangle.h>

class Triangle;

class Adjacencies{

public:
    Adjacencies();

    static void setAdjacencies(Triangle* tr1, Triangle* tr2, Triangle* tr3, Triangle* trFather);

    static void setAdjacenciesAfterFlip(Triangle* tr1, Triangle* tr2, Triangle* trFather1, Triangle* trFather2);

    static void setAdjacenciesAfterPointInALine(Triangle* tr1, Triangle* tr2, Triangle* tr3, Triangle* tr1Father, Triangle* tr2Father);

    static void setAdjacency(Triangle* triangle, Triangle* adjTriangle);

    static bool isAdjacencies(const Triangle& tr1, const Triangle& tr2);

    static bool isAdjacenciesForTwoPoints(const Triangle &tr, const Point2Dd& p1, const Point2Dd& p2);

    static Point2Dd* getThirdPoint(const Triangle& tr, const Point2Dd& p1, const Point2Dd& p2);

    static void overrideAdjacency(Triangle* triangle, Triangle* adjTriangle);

    static Triangle* getTriangleAdjacentByTwoPoints(Triangle* tr, const Point2Dd& a, const Point2Dd& b);
};

#endif // ADJACENCIES_H
