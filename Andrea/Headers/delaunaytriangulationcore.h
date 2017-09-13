#ifndef DELAUANYTRIANGULATIONCORE_H
#define DELAUANYTRIANGULATIONCORE_H
#include <Andrea/Headers/Static/dag.h>
#include <Andrea/Headers/Static/adjacencies.h>
#include <Andrea/Headers/DataStructures/dagnode.h>
#include <Andrea/Headers/DataStructures/triangle.h>
#include <utils/delaunay_checker.h>
#include <float.h>

class DelaunayTriangulationCore
{
public:
    DelaunayTriangulationCore();

    // Points of my triangulation
    std::vector<Point2Dd*> points; /**< enum value 2 */

    // Triangles of my triangulation & Dag
    std::vector<Triangle*> triangles; /**< enum value 2 */

    // Nodes of my Dag
    std::vector<DagNode*> dagNodes; /**< enum value 2 */

    // This attributes is for validation process, not triangulation
    std::map<Point2Dd, int> map;
    Array2D<unsigned int> validTriangles;
    int countValidTriangles = 0;

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
    Triangle* generateTriangle(Point2Dd* p, Point2Dd* p1, Point2Dd* p2, DagNode* dagNodeFather);

    // Create a new triangle, set his dag node and his two pointer of two dag node father
    Triangle* generateTriangle(Point2Dd* p, Point2Dd* p1, Point2Dd* p2, DagNode* dagNodeFather1, DagNode* dagNodeFather2);

    void pointLieAB(Point2Dd* pr, Triangle* triangleFather, DagNode* dagFather);
    void pointLieBC(Point2Dd* pr, Triangle* triangleFather, DagNode* dagFather);
    void pointLieCA(Point2Dd* pr, Triangle* triangleFather, DagNode* dagFather);
    void pointLieInsideTriangle(Point2Dd* pr, Triangle* triangleFather, DagNode* dagFather);

    bool operator == (const Point2Dd& p1);

    // Validation method, not triangulation
    std::vector<Point2Dd> getPointsForValidation();
    void generateTrianglesForValidation();
    int countNumberOfTriangles() const;
    int getCountValidTriangle() const;
    Array2D<unsigned int> getValidTriangles() const;


    std::vector<Triangle*> getTriangles();

};

#endif // DELAUANYTRIANGULATIONCORE_H
