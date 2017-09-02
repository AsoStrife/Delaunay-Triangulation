#ifndef DAG_H
#define DAG_H

#include <viewer/objects/objects.h>
#include <Andrea/Headers/Static/adjacencies.h>
#include <Andrea/Headers/DataStructures/dagnode.h>

class DagNode;

class Dag {

public:
    Dag();

    static bool pointInTriangle (const Point2Dd& p, const Point2Dd& a, const Point2Dd& b, const Point2Dd& c);

    static bool checkPointIsVertexOfTriangle(const Point2Dd& p, const Point2Dd& a, const Point2Dd& b, const Point2Dd& c);

    static DagNode *navigate(DagNode *dagNode, const Point2Dd& p);

    static void addNode(DagNode* node, DagNode* dagNodefather);

};

#endif // DAG_H
