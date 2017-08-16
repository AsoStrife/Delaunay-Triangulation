#ifndef DAG_H
#define DAG_H

#include <common/arrays.h>
#include <viewer/objects/objects.h>
#include <Andrea/Headers/node.h>

class Dag
{
    private:

        // Un triangolo è un nodo
        std::vector<Node> nodes;

    public:
        Dag();

        // Funzioni per controllare che un punto sia in un triangolo
        float sign (const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3) const;
        bool PointInTriangle (const Point2Dd& pt, Node* t);

        // Creo la radice della mia dag
        void addRoot(Point2Dd* p1,Point2Dd* p2, Point2Dd* p3);

        // Cerco in quale triangolo cade il nuovo punto
        Node* navigate(const Point2Dd& p);

        // Aggiungo un nodo figlio al padre oppure tutti e 3 i figli di un padre
        void addNode(Node* node, Node* Father, int nChild);
        void addNodes(Node* nodeA, Node* nodeB, Node* nodeC, Node* Father);

        void clear();
};

#endif // DAG_H
