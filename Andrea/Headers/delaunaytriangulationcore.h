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

    // Points of my triangulation
    std::vector<Point2Dd*> points;

    // Triangles of my triangulation & Dag
    std::vector<Triangle*> triangles;

    // Node of a Dag
    std::vector<Dag*> dagNodes;

    // This map is used for the validation process, not triangulation
    std::map<Point2Dd, int> map;

    // Add a point inside my triangulation
    bool addPoint(const Point2Dd& p);

    // Clean triangulation
    void cleanDelaunayTriangulation();

    // Load points from a file
    void loadPointFromVector(const std::vector<Point2Dd>& vectorPoints);

    // Set bounding triangle points
    void setBoundingTrianglePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

    // Check if a point lie in a line
    bool pointLieInALine(const Point2Dd& p, const Point2Dd& a, const Point2Dd& b);

    // Check if an Edge is legal
    void legalizeEdge(Point2Dd* pr, Point2Dd* pi, Point2Dd* pj, Triangle* tr);

    // Edge Flip of two triangle
    void edgeFlip(Triangle* tr1, Triangle* tr2, Point2Dd* pr, Point2Dd* pi, Point2Dd* pj);

    // Create a new triangle, set his dag node and his pointer of his dag node father
    Triangle* generateTriangle(Point2Dd *p, Point2Dd *p1, Point2Dd *p2, Dag* dagNodeFather);

    // Create a new triangle, set his dag node and his two pointer of two dag node father
    Triangle* generateTriangle(Point2Dd *p, Point2Dd *p1, Point2Dd *p2, Dag* dagNodeFather1, Dag* dagNodeFather2);

    // Validation method, not triangulation
    std::vector<Point2Dd> getPointsForValidation();
    Array2D<unsigned int> getTrianglesForValidation();
    int countNumberOfTriangles();

    bool operator == (const Point2Dd& p1);

    std::vector<Triangle*> getTriangles();

};

#endif // DELAUANYTRIANGULATIONCORE_H
