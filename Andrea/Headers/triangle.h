#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <viewer/objects/objects.h>
#include <Andrea/Headers/adjacencies.h>
#include <Andrea/Headers/dag.h>

class Dag;

class Triangle{
private:
    Point2Dd* vA;
    Point2Dd* vB;
    Point2Dd* vC;

    Dag* dagNode = nullptr;

    Triangle* triangleAdjacentA = nullptr;
    Triangle* triangleAdjacentB = nullptr;
    Triangle* triangleAdjacentC = nullptr;

    bool isDeleted = false;

public:
    Triangle();
    Triangle(Point2Dd* p1, Point2Dd* p2, Point2Dd*  p3);

    // Getter & setter per i 3 punti del triangolo
    Point2Dd* getA() const;
    Point2Dd* getB() const;
    Point2Dd* getC() const;

    void setA(Point2Dd* p);
    void setB(Point2Dd* p);
    void setC(Point2Dd* p);

    // Getter & setter per il nodo della Dag a cui punta il triangolo e per il suo elemento di adiacenze
    Dag* getDagNode() const;
    void setDagNode(Dag* n);

    Triangle* getTriangleAdjacentA() const;
    Triangle* getTriangleAdjacentB() const;
    Triangle* getTriangleAdjacentC() const;
    void setTriangleAdjacentA(Triangle* tA);
    void setTriangleAdjacentB(Triangle* tB);
    void setTriangleAdjacentC(Triangle* tC);

    // Getter & setter per isDeleted
    void setIsDeleted(bool b);
    bool getIsDeleted() const;

    bool operator ==(const Triangle* t1);
};

#endif // TRIANGLE_H
