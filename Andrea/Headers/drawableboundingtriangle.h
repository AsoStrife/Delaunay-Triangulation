#ifndef DRAWABLEBOUNDINGTRIANGLE_H
#define DRAWABLEBOUNDINGTRIANGLE_H
#include <viewer/interfaces/drawable_object.h>
#include <viewer/objects/objects.h>

class DrawableBoundingTriangle : public DrawableObject{

public:
    DrawableBoundingTriangle();

    void definePoints(Point2Dd p1, Point2Dd p2, Point2Dd p3);

    Point2Dd p1;
    Point2Dd p2;
    Point2Dd p3;

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;
};

#endif // DRAWABLEBOUNDINGTRIANGLE_H
