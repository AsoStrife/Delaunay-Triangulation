#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include <viewer/objects/objects.h>
#include <utils/delaunay_checker.h>
#include <Andrea/Headers/dag.h>
#include <Andrea/Headers/node.h>

#include <Andrea/Headers/Drawable/drawableline.h>
#include <Andrea/Headers/Drawable/drawablepoint.h>
#include <Andrea/Headers/Drawable/drawableboundingtriangle.h>

class DrawableDelaunayTriangulation : public DrawableObject{
public:
    DrawableDelaunayTriangulation();

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    void setTriangles(std::vector<Triangle> t);

    void setBoundingTriangleActive(bool b);
private:
    std::vector<Triangle> triangles;
    bool boundingTriangleActive = false;

};

#endif // DELAUNAYTRIANGULATION_H
