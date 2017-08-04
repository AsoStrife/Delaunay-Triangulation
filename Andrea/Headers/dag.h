#ifndef DAG_H
#define DAG_H
#include <viewer/objects/objects.h>

class Dag
{
    public:
        Dag();
        float sign (Point2Dd p1, Point2Dd p2, Point2Dd p3);
        bool PointInTriangle (Point2Dd pt, Point2Dd v1, Point2Dd v2, Point2Dd v3);
};

#endif // DAG_H
