#ifndef POINTTEST_H
#define POINTTEST_H
#include <viewer/interfaces/drawable_object.h>
#include <viewer/objects/objects.h>

class pointtest : public DrawableObject{

public:

    pointtest();
    pointtest(double x, double y);
    //pointtest(const Point2Dd& p);

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    double x;
    double y;
    //const Point2Dd& p;
    double getx();
    double gety();

    void setx(double value);
    void sety(double value);

protected:

private:



};

#endif // POINTTEST_H
