#ifndef DRAWABLEBOUNDINGTRIANGLE_H
#define DRAWABLEBOUNDINGTRIANGLE_H
#include <viewer/interfaces/drawable_object.h>
#include <viewer/objects/objects.h>
#include <Andrea/Headers/drawableline.h>

class DrawableBoundingTriangle : public DrawableObject{

public:
    DrawableBoundingTriangle();

    void definePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

    Point2Dd p1;
    Point2Dd p2;
    Point2Dd p3;

    DrawableLine l1;
    DrawableLine l2;
    DrawableLine l3;

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;
};

#endif // DRAWABLEBOUNDINGTRIANGLE_H
