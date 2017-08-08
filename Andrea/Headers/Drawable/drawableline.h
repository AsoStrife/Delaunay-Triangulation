#ifndef DRAWABLELINE_H
#define DRAWABLELINE_H

#include <viewer/interfaces/drawable_object.h>
#include <viewer/objects/objects.h>

class DrawableLine : public DrawableObject{

public:
    DrawableLine();
    DrawableLine(double x1, double y1, double x2, double y2);

    DrawableLine(const Point2Dd& p1, const Point2Dd& p2);

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    void setPoints(const Point2Dd& p1, const Point2Dd& p2);

private:
    Point2Dd p1;
    Point2Dd p2;
};

#endif // DRAWABLELINE_H
