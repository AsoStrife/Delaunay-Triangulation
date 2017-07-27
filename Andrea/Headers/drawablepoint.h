#ifndef DRAWABLEPOINT_H
#define DRAWABLEPOINT_H

#include <viewer/interfaces/drawable_object.h>
#include <viewer/objects/objects.h>

class DrawablePoint : public DrawableObject{

public:
    DrawablePoint();
    DrawablePoint(double x, double y);
    DrawablePoint(const Point2Dd& p);

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    void setx(double x);
    void sety(double y);
    double getx() const;
    double gety() const;

    void setPoints(double x, double y);

    bool operator == (const DrawablePoint &p1);

private:
    void updatePoint();

    double x;
    double y;

    Point2Dd point;
};

#endif // DRAWABLEPOINT_H
