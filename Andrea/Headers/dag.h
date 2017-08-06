#ifndef DAG_H
#define DAG_H
#include <viewer/objects/objects.h>
#include <common/arrays.h>
class Dag
{
    public:
        Dag();
        float sign (Point2Dd p1, Point2Dd p2, Point2Dd p3);
        bool PointInTriangle (Point2Dd pt, Point2Dd v1, Point2Dd v2, Point2Dd v3);

        /*
         * Definisco un vettore di punti Point2Dd e un Array2D di interi per gestire la triangolazione
         * Utilizzo la stessa struttura dati che viene richiesta poi in on_checkTriangulationPushButton_clicked() nel file delaunaymanager.cpp
         */
        std::vector<Point2Dd> p;
        Array2D<unsigned int> t;

        void addPoint2Dd(const Point2Dd& p);

        void addRoot(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

        std::vector<Point2Dd> getPoints();
        Array2D<unsigned int> getTriangles();
};

#endif // DAG_H
