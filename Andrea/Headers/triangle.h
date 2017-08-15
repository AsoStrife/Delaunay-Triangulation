#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <viewer/objects/objects.h>

class Triangle{
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



private:
    Point2Dd* vA = nullptr;
    Point2Dd* vB = nullptr;
    Point2Dd* vC = nullptr;
};

#endif // TRIANGLE_H
