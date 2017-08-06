#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include <viewer/objects/objects.h>
#include <Andrea/Headers/drawableline.h>
#include <Andrea/Headers/drawablepoint.h>
#include <Andrea/Headers/dag.h>
#include <Andrea/Headers/drawableboundingtriangle.h>
#include <common/arrays.h>

class DrawableDelaunayTriangulation : public DrawableObject{
public:
    DrawableDelaunayTriangulation();

    Dag dag;
    /*
     * Imposto un vettore di DrawablePoint e DrawableLine per gestire
     * i punti e le linee che verranno disegnati all'interno della canvas
     */
    std::vector<DrawablePoint> points;
    std::vector<DrawableLine> lines;

    // DrawableObject interface
    void draw() const;
    Pointd sceneCenter() const;
    double sceneRadius() const;

    /*
     * Quando clicco sulla canvas aggiungo un punto al mio array
     * e controllo che il punto non sia già presente prima di inserirlo
     */
    void addDrawablePoint(const Point2Dd& p);
    bool checkIfPointAlreadyExist(const Point2Dd& p);

    // Funzione per poter disegnare una linea tra due punti
    void addDrawableLine(Point2Dd p1, Point2Dd p2);

    void cleanDelaunayTriangulation();

    // Gestisco i punti che vengono caricati dal file
    void loadPointFromVector(const std::vector<Point2Dd>& p);

    // Setto i punto del Bounding Triangle
    void setBoundingTrianglePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);
private:
    Point2Dd BT_P1;
    Point2Dd BT_P2;
    Point2Dd BT_P3;
};

#endif // DELAUNAYTRIANGULATION_H
