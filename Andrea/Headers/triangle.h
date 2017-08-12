#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <viewer/objects/objects.h>

class Triangle
{
public:
    Triangle();
    Triangle(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

    /*
     * Getter & setter per i 3 punti del triangolo
     */
    Point2Dd getA() const;
    Point2Dd getB() const;
    Point2Dd getC() const;

    void setA(const Point2Dd& p);
    void setB(const Point2Dd& p);
    void setC(const Point2Dd& p);



private:
    Point2Dd vA;
    Point2Dd vB;
    Point2Dd vC;
};

#endif // TRIANGLE_H
