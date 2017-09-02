#ifndef DRAWABLEVORONOIDIAGRAM_H
#define DRAWABLEVORONOIDIAGRAM_H

#include <viewer/objects/objects.h>
#include <viewer/interfaces/drawable_object.h>
#include <Andrea/Headers/DataStructures/triangle.h>

class DrawableVoronoiDiagram : public DrawableObject{

public:
    DrawableVoronoiDiagram();

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    Point2Dd getCircumcircle(Triangle* t) const;

    void setTriangles(std::vector<Triangle*> t);
    void clearVoronoi();

private:
    std::vector<Triangle*> triangles;

    QColor voronoiPointColor = QColor(1, 120 , 255);
    QColor voronoiLineColor = QColor(1, 120 , 255);

    int lineSize = 1;
    int pointSize = 10;
};

#endif // DRAWABLEVORONOIDIAGRAM_H
