#ifndef POINTTEST_H
#define POINTTEST_H
#include <viewer/interfaces/drawable_object.h>

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

    void setx(double x);
    void sety(double y);

protected:

private:



};

#endif // POINTTEST_H
