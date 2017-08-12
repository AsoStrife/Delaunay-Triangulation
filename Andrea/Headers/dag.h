#ifndef DAG_H
#define DAG_H

#include <common/arrays.h>
#include <viewer/objects/objects.h>
#include <Andrea/Headers/node.h>

class Dag
{
    private:

        /*
         * Definisco un vettore di punti Point2Dd e un Array2D di interi per gestire la triangolazione
         * Utilizzo la stessa struttura dati che viene richiesta poi in on_checkTriangulationPushButton_clicked() nel file delaunaymanager.cpp
         */
        //std::vector<Point2Dd> points; // Lista dei punti che inserisco
        std::vector<Node> nodes; // Un triangolo è un nodo


    public:
        Dag();

        // Funzioni per controllare che un punto sia in un triangolo
        float sign (const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);
        bool PointInTriangle (const Point2Dd& pt, const Node* t);


        // void addPoint2Dd(const Point2Dd& p);

        // Creo la radice della mia dag
        void addRoot(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);

        //std::vector<Point2Dd> getPoints();
        Array2D<unsigned int> getTriangles();

        // Cerco in quale triangolo cade il nuovo punto
        Node* navigate(const Point2Dd& p);

        void addNode(Node* node, Node* Father, int nChild);

};

#endif // DAG_H
