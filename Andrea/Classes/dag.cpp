#include "Andrea/Headers/dag.h"


Dag::Dag() {}

/**
  *@link https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
 * @brief sign
 * @param p1
 * @param p2
 * @param p3
 * @return float
 * I due seguenti metodi sono stati implementati per poter controllare che un punto si trovi all'interno di un triangolo
 */
float Dag::sign (const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3){
    return (p1.x() - p3.x()) * (p2.y() - p3.y()) - (p2.x() - p3.x()) * (p1.y() - p3.y());
}

bool Dag::pointInTriangle (const Point2Dd& pt, Node* t){
    if(t == nullptr)
        return false;

    bool b1, b2, b3;

    b1 = Dag::sign(pt, *t->getA(), *t->getB()) < 0.0f;
    b2 = Dag::sign(pt, *t->getB(), *t->getC()) < 0.0f;
    b3 = Dag::sign(pt, *t->getC(), *t->getA()) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

bool Dag::checkIfPointAlreadyExist(Node* root, const Point2Dd& p){
    Node* n = Dag::navigate(root, p);

    if(p.x() == n->getA()->x() && p.y() == n->getA()->y())
        return true;
    else if(p.x() == n->getB()->x() && p.y() == n->getB()->y())
        return true;
    else if(p.x() == n->getC()->x() && p.y() == n->getC()->y())
        return true;
    else
        return false;
}



/**
 * @brief Dag::navigate
 * @param Node*
 * @param Point2Dd p
 * @return Triangle*
 *
 * Passo come parametro la radice della dag ed un punto, e restituisco il più piccolo triangolo che lo contiene. Nel caso in cui
 * sia il primo punto inserito nella triangolazione, restituirà la radice della Dag, ovvero il Bounding Triangle
 */
Node* Dag::navigate(Node* dagNode, const Point2Dd& p){

    bool hasChild = true;

        while(hasChild){

            if(dagNode == nullptr){
                return nullptr; // Check di controllo, non dovrebbe mai verificarsi di entrare nella navigate con un puntatore nullo
            }

            // Se il punto è contenuto in questo triangolo, controllo i suoi figli. Se è contenuto nei suoi figli aggiorno il puntatore e iterativamente continuo il ciclo
            if(Dag::pointInTriangle(p, dagNode->getChildA()))
                dagNode = dagNode->getChildA();
            else if(Dag::pointInTriangle(p, dagNode->getChildB()))
                dagNode = dagNode->getChildB();
            else if(Dag::pointInTriangle(p, dagNode->getChildC()))
                dagNode = dagNode->getChildC();
            else
            hasChild = false;

        }
        // Quando non ho più figli restituisco l'ultimo triangolo (il più piccolo) che contiene il mio punto
        return dagNode; // restituisco l'ultimo l'indirizzo del triangolo più piccolo che contiene il punto appena inserito}
}


void Dag::addNode(Node* node, Node* Father, int nChild){

    switch(nChild){
        case(1): Father->setChildA(node); break;
        case(2): Father->setChildB(node); break;
        case(3): Father->setChildC(node); break;

    }
}

void Dag::addNodes(Node* nodeA, Node* nodeB, Node* nodeC, Node* Father){
    Father->setChildA(nodeA);
    Father->setChildB(nodeB);
    Father->setChildC(nodeC);
}
