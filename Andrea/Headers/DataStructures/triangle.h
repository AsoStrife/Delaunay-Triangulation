#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <viewer/objects/objects.h>
#include <Andrea/Headers/Static/adjacencies.h>
#include <Andrea/Headers/Static/dag.h>

class DagNode;

class Triangle{
private:
    Point2Dd* vA;
    Point2Dd* vB;
    Point2Dd* vC;

    DagNode* dagNode = nullptr;

    Triangle* triangleAdjacentA = nullptr;
    Triangle* triangleAdjacentB = nullptr;
    Triangle* triangleAdjacentC = nullptr;

    bool isDeleted = false;

public:
    Triangle();
    Triangle(Point2Dd* vA, Point2Dd* vB, Point2Dd* vC);

    // Getter & setter per i 3 punti del triangolo
    Point2Dd* getA() const;
    Point2Dd* getB() const;
    Point2Dd* getC() const;

    void setA(Point2Dd* vA);
    void setB(Point2Dd* vB);
    void setC(Point2Dd* vC);

    // Getter & Setter for dagNode
    DagNode* getDagNode() const;
    void setDagNode(DagNode* dn);

    // Getter & Setter for adjacencies
    Triangle* getTriangleAdjacentA() const;
    Triangle* getTriangleAdjacentB() const;
    Triangle* getTriangleAdjacentC() const;
    void setTriangleAdjacentA(Triangle* trAdjA);
    void setTriangleAdjacentB(Triangle* trAdjB);
    void setTriangleAdjacentC(Triangle* trAdjC);

    // Getter & setter per isDeleted
    void setIsDeleted(bool b);
    bool getIsDeleted() const;

    bool operator ==(const Triangle* tr);
};

#endif // TRIANGLE_H
