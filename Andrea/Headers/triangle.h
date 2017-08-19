#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <viewer/objects/objects.h>
#include <Andrea/Headers/adjacencies.h>
#include <Andrea/Headers/dag.h>

class Dag;
class Adjacencies;

class Triangle{
private:
    Point2Dd* vA = nullptr;
    Point2Dd* vB = nullptr;
    Point2Dd* vC = nullptr;

    Dag* dagNode            = nullptr;
    Adjacencies* adjNode    = nullptr;

public:
    Triangle();
    Triangle(Point2Dd* p1, Point2Dd* p2, Point2Dd*  p3);

    /*
     * Getter & setter per i 3 punti del triangolo
     */
    Point2Dd* getA() const;
    Point2Dd* getB() const;
    Point2Dd* getC() const;

    void setA(Point2Dd* p);
    void setB(Point2Dd* p);
    void setC(Point2Dd* p);



};

#endif // TRIANGLE_H
