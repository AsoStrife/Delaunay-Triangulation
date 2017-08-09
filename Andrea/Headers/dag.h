#ifndef DAG_H
#define DAG_H
#include <viewer/objects/objects.h>
#include <common/arrays.h>
#include <Andrea/Headers/triangle.h>

class Dag
{
    public:
        Dag();
        float sign (const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);
        bool PointInTriangle (const Point2Dd& pt, const Triangle& t);

        /*
         * Definisco un vettore di punti Point2Dd e un Array2D di interi per gestire la triangolazione
         * Utilizzo la stessa struttura dati che viene richiesta poi in on_checkTriangulationPushButton_clicked() nel file delaunaymanager.cpp
         */
        std::vector<Point2Dd> points; // Lista dei punti che inserisco
        std::vector<Triangle> nodes; // Un triangolo è un nodo

        void addPoint2Dd(const Point2Dd& p);

        void addRoot(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

        std::vector<Point2Dd> getPoints();
        Array2D<unsigned int> getTriangles();

        void addTrianglesIntoDag(const Point2Dd& p);


};

#endif // DAG_H
