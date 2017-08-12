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

    //Dag per poter navigare le varie triangolazioni per sapere dove cade il prossimo punto che inserirò
    Dag dag;
    /*
     * Imposto un vettore di DrawablePoint e DrawableLine per gestire
     * i punti e le linee che verranno disegnati all'interno della canvas
     */
    std::vector<DrawablePoint> points;
    std::vector<DrawableLine> lines;
    std::vector<Triangle> triangles;

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

    // Pulisco tutta la mia triangolazione
    void cleanDelaunayTriangulation();

    // Gestisco i punti che vengono caricati dal file
    void loadPointFromVector(const std::vector<Point2Dd>& p);

    // Setto i punto del Bounding Triangle
    void setBoundingTrianglePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

    // Controllo che un punto non cada su un edge già esistente
    bool pointLieInALine(const Point2Dd& p, const Point2Dd& a, const Point2Dd& b);
    // Legalizzazione degli edge
    bool LegalizeEdge();
    bool EdgeFlip();

private:
    Point2Dd BT_P1;
    Point2Dd BT_P2;
    Point2Dd BT_P3;
};

#endif // DELAUNAYTRIANGULATION_H
