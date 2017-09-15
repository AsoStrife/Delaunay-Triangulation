#ifndef DRAWABLEVORONOIDIAGRAM_H
#define DRAWABLEVORONOIDIAGRAM_H

#include <viewer/objects/objects.h>
#include <viewer/interfaces/drawable_object.h>
#include <Andrea/Headers/DataStructures/triangle.h>

/**
 * @brief The DrawableVoronoiDiagram class
 */
class DrawableVoronoiDiagram : public DrawableObject{

public:
    DrawableVoronoiDiagram();

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    Point2Dd getCircumcircle(const Triangle& t) const;

    void setTriangles(const std::vector<Triangle*>& t);
    void clearVoronoi();

private:
    std::vector<Triangle*> triangles;

    QColor const voronoiPointColor = QColor(1, 120 , 255);
    QColor const voronoiLineColor = QColor(1, 120 , 255);

    int lineSize = 1;
    int pointSize = 10;
};

#endif // DRAWABLEVORONOIDIAGRAM_H
