#ifndef DELAUANYTRIANGULATIONCORE_H
#define DELAUANYTRIANGULATIONCORE_H
#include <Andrea/Headers/dag.h>
#include <Andrea/Headers/adjacencies.h>
#include <viewer/objects/objects.h>
#include <utils/delaunay_checker.h>

class DelaunayTriangulationCore
{
public:
    DelaunayTriangulationCore();

    //Dag per poter navigare le varie triangolazioni per sapere dove cade il prossimo punto che inserirò
    Dag dag;
    Adjacencies adj;

    // Vettore di puntatori a Point2Dd, per i punti che inserisco nella mia triangolazione
    std::vector<Point2Dd*> points;
    // Vettore di puntatori Node per i triangoli che inserisco nella mia triangolazione, i child qui saranno le adiacenze
    std::vector<Node*> triangles;
    // Vettore di puntatori Node per i triangoli che inserisco nella mia dag, i child qui saranno sotto triangoli
    std::vector<Node*> dagNodes;


    //Aggiungo un punto alla triangolazione e controllo che il punto non sia già presente prima di inserirlo
    bool addPoint(const Point2Dd& p);

    // Pulisco tutta la mia triangolazione
    void cleanDelaunayTriangulation();

    // Gestisco i punti che vengono caricati dal file
    void loadPointFromVector(std::vector<Point2Dd> p);

    // Setto i punto del Bounding Triangle
    void setBoundingTrianglePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

    // Controllo che un punto non cada su un edge già esistente
    bool pointLieInALine(const Point2Dd& p, const Point2Dd& a, const Point2Dd& b);
    // Legalizzazione degli edge
    void LegalizeEdge(const Point2Dd& newP, const Point2Dd& p1, const Point2Dd& p2, int e);

    Node* EdgeFlip();

    bool operator == (const Point2Dd& p1);

    std::vector<Node*> getTriangles();
};

#endif // DELAUANYTRIANGULATIONCORE_H
