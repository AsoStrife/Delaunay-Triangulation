#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include <viewer/objects/objects.h>
#include <Andrea/Headers/DataStructures/triangle.h>
#include <viewer/interfaces/drawable_object.h>
#include <math.h>

/**
 * @brief The DrawableDelaunayTriangulation class
 */
class DrawableDelaunayTriangulation : public DrawableObject {

public:
    DrawableDelaunayTriangulation();

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    void setTriangles(const std::vector<Triangle*>& t);

    void setBoundingTriangleActive(bool b);

    bool needToPrintPoint(const Point2Dd& p) const;

    bool needToPrintLine(const Point2Dd& p1, const Point2Dd& p2) const;

    void clearTriangles();

private:
    bool boundingTriangleActive = false;

    QColor const delaunayPointColor = QColor(255, 0 ,0);
    QColor const delaunayLineColor = QColor(0, 0 ,0);

    int const lineSize = 1;
    int const pointSize = 10;

    Point2Dd BT_P1; //(1e+10, 0)
    Point2Dd BT_P2; //(0, 1e+10)
    Point2Dd BT_P3; //(-1e+10, -1e+10)

    std::vector<Triangle*> triangles;

};

#endif // DELAUNAYTRIANGULATION_H
