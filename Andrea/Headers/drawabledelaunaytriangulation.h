#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include <viewer/objects/objects.h>
#include <Andrea/Headers/drawableline.h>
#include <Andrea/Headers/drawablepoint.h>
#include <common/arrays.h>

class DrawableDelaunayTriangulation : public DrawableObject{
public:
    DrawableDelaunayTriangulation();

    // Vettori e array utilizzati in delaunay manager
    //std::vector<Point2Dd> points;
    //Array2D<unsigned int> triangles;

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    // Imposto un vettore di punti e linee per gestire la canvas
    std::vector<DrawablePoint> points;
    std::vector<DrawableLine> lines;

    void addDrawablePoint(Point2Dd p);
    bool checkIfPointAlreadyExist(Point2Dd p);

};

#endif // DELAUNAYTRIANGULATION_H
