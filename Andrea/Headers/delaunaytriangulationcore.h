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
    //Dag dag;
    //Adjacencies adj;

    // Vettore di puntatori a Point2Dd, per i punti che inserisco nella mia triangolazione
    std::vector<Point2Dd*> points;
    // Vettore di puntatori Triangle per i triangoli che inserisco nella mia triangolazione
    std::vector<Triangle*> triangles;
    std::vector<Dag*> dagNodes;

    // Mappa utiizzata per la validazione, non per la triangolazione
    std::map<Point2Dd, int> map;

    //Aggiungo un punto alla triangolazione e controllo che il punto non sia già presente prima di inserirlo
    bool addPoint(const Point2Dd& p);

    // Pulisco tutta la mia triangolazione
    void cleanDelaunayTriangulation();

    // Gestisco i punti che vengono caricati dal file
    void loadPointFromVector(const std::vector<Point2Dd> &vectorPoints);

    // Setto i punto del Bounding Triangle
    void setBoundingTrianglePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

    // Controllo che un punto non cada su un edge già esistente
    bool pointLieInALine(const Point2Dd& p, const Point2Dd& a, const Point2Dd& b);

    // Legalizzazione degli edge
    void legalizeEdge(Point2Dd* pr, Point2Dd* pi, Point2Dd* pj, Triangle* tr);

    void edgeFlip(Triangle* tr1, Triangle* tr2, Point2Dd* pr, Point2Dd* pi, Point2Dd* pj);

    //void LegalizeTriangle(Triangle* t);
    Triangle* generateTriangle(Point2Dd *p, Point2Dd *p1, Point2Dd *p2, Dag* dagNodeFather);

    Triangle* generateTriangle(Point2Dd *p, Point2Dd *p1, Point2Dd *p2, Dag* dagNodeFather1, Dag* dagNodeFather2);

    // Metodi per la validazione, non per la triangolazione
    std::vector<Point2Dd> getPointsForValidation();
    Array2D<unsigned int> getTrianglesForValidation();
    int countNumberOfTriangles();

    bool operator == (const Point2Dd& p1);

    std::vector<Triangle*> getTriangles();

};

#endif // DELAUANYTRIANGULATIONCORE_H
