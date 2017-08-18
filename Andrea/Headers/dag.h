#ifndef DAG_H
#define DAG_H

#include <common/arrays.h>
#include <viewer/objects/objects.h>
#include <Andrea/Headers/node.h>

class Dag
{

    public:
        Dag();

        // Funzioni per controllare che un punto sia in un triangolo
        static float sign (const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3);
        static bool pointInTriangle (const Point2Dd& pt, Node* t);

        static bool checkIfPointAlreadyExist(Node* root, const Point2Dd& p);

        // Cerco in quale triangolo cade il nuovo punto
        static  Node* navigate(Node* dagNode, const Point2Dd& p);

        // Aggiungo un nodo figlio al padre oppure tutti e 3 i figli di un padre
        static void addNode(Node* node, Node* Father, int nChild);
        static void addNodes(Node* nodeA, Node* nodeB, Node* nodeC, Node* Father);

};

#endif // DAG_H
