#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <viewer/objects/objects.h>

class Triangle
{
public:
    Triangle();
    Triangle(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

    //Getter
    Point2Dd getP1();
    Point2Dd getP2();
    Point2Dd getP3();

    //Setter
    void setP1(const Point2Dd& p);
    void setP2(const Point2Dd& p);
    void setP3(const Point2Dd& p);

private:
    Point2Dd p1;
    Point2Dd p2;
    Point2Dd p3;

};

#endif // TRIANGLE_H
