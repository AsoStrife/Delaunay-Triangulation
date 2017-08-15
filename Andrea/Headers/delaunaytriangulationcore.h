#ifndef DELAUANYTRIANGULATIONCORE_H
#define DELAUANYTRIANGULATIONCORE_H
#include <Andrea/Headers/dag.h>
#include <viewer/objects/objects.h>

class DelaunayTriangulationCore
{
public:
    DelaunayTriangulationCore();

    //Dag per poter navigare le varie triangolazioni per sapere dove cade il prossimo punto che inserirò
    Dag dag;

    /*
     * Imposto un vettore di Punti e Triangoli per gestire
     * i punti e le linee che verranno disegnati all'interno della canvas
     */
    //std::forward_list<Point2Dd> points;
    std::vector<Point2Dd*> points;
    std::vector<Triangle> triangles;

    /*
     * Aggiungo un punto alla triangolazione
     * e controllo che il punto non sia già presente prima di inserirlo
     */
    void addPoint(const Point2Dd& p);
    bool checkIfPointAlreadyExist(const Point2Dd& p);

    // Pulisco tutta la mia triangolazione
    void cleanDelaunayTriangulation();

    // Gestisco i punti che vengono caricati dal file
    void loadPointFromVector(const std::vector<Point2Dd>& p);

    // Setto i punto del Bounding Triangle
    void setBoundingTrianglePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

    // Controllo che un punto non cada su un edge già esistente
    bool pointLieInALine(const Point2Dd& p, const Point2Dd& a, const Point2Dd& b);
    // Legalizzazione degli edge
    bool LegalizeEdge(const Point2Dd& p, const Point2Dd& pA, const Point2Dd& pB );
    bool EdgeFlip();

    bool operator == (const Point2Dd& p1);

    std::vector<Triangle> getTriangles();
};

#endif // DELAUANYTRIANGULATIONCORE_H
