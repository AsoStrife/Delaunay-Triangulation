#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include <viewer/objects/objects.h>
#include <Andrea/Headers/dag.h>
#include <viewer/objects/drawabledebugobjects.h>

class DrawableDelaunayTriangulation : public DrawableObject{
public:
    DrawableDelaunayTriangulation();

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    void setTriangles(std::vector<Triangle*> t);
    void setBoundingTriangleActive(bool b);

    bool needToPrintPoint(const Point2Dd& p) const;
    bool needToPrintLine(const Point2Dd& p1, const Point2Dd& p2) const;

    void clearTriangles();
private:
    std::vector<Triangle> triangles;
    bool boundingTriangleActive = false;

    QColor pointColor = QColor(255, 0 ,0);
    QColor lineColor = QColor(0, 0 ,0);

    int lineSize = 1;
    int pointSize = 10;

    // setto nuovamente 3 attributi per il bounding triangle
    Point2Dd BT_P1; //(1e+10, 0);
    Point2Dd BT_P2; //(0, 1e+10);
    Point2Dd BT_P3; //(-1e+10, -1e+10)
};

#endif // DELAUNAYTRIANGULATION_H
