#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include <viewer/objects/objects.h>
#include <Andrea/Headers/dag.h>
#include <viewer/interfaces/drawable_object.h>
#include <Andrea/Headers/Drawable/drawablevoronoidiagram.h>
#include <Andrea/Headers/delaunaytriangulationcore.h>

class DrawableDelaunayTriangulation : public DrawableObject {

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

    void setVoronoiActive(bool b);
    bool getVoronoiActive() const;

    void clearTriangles();
private:
    bool boundingTriangleActive = false;

    QColor delaunayPointColor = QColor(255, 0 ,0);
    QColor delaunayLineColor = QColor(0, 0 ,0);

    QColor voronoiPointColor = QColor(1, 120 , 255);
    QColor voronoiLineColor = QColor(255, 153 ,51);

    int lineSize = 1;
    int pointSize = 10;

    // Booleano per disegnare il diagramma di voronoi
    bool voronoiActive = false;

    // setto nuovamente 3 attributi per il bounding triangle
    Point2Dd* BT_P1; //(1e+10, 0);
    Point2Dd* BT_P2; //(0, 1e+10);
    Point2Dd* BT_P3; //(-1e+10, -1e+10)

    std::vector<Triangle*> triangles;

};

#endif // DELAUNAYTRIANGULATION_H
