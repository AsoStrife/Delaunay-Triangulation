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

    /*
     * Getter & setter per i 3 figli
     */
    void setChildA(Triangle* t);
    void setChildB(Triangle* t);
    void setChildC(Triangle* t);
    void setChildren(Triangle* A, Triangle* B, Triangle* C);

    Triangle* getChildA();
    Triangle* getChildB();
    Triangle* getChildC();

private:
    Point2Dd A;
    Point2Dd B;
    Point2Dd C;

    Triangle* childA = nullptr;
    Triangle* childB = nullptr;
    Triangle* childC = nullptr;

};

#endif // TRIANGLE_H
