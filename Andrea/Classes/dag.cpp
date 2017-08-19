#include "Andrea/Headers/dag.h"


Dag::Dag() {}
Dag::Dag(Triangle* t){
    this->t = t;
}

Dag::Dag(Point2Dd* p1, Point2Dd* p2, Point2Dd*  p3){
    this->t = new Triangle(p1, p2, p3);
}

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

bool Dag::pointInTriangle (const Point2Dd& pt, Triangle* t){

    if(t == nullptr)
        return false;

    bool b1, b2, b3;

    b1 = sign(pt, *t->getA(), *t->getB()) < 0.0f;
    b2 = sign(pt, *t->getB(), *t->getC()) < 0.0f;
    b3 = sign(pt, *t->getC(), *t->getA()) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

bool Dag::checkIfPointAlreadyExist(Dag* root, const Point2Dd& p){

    Dag* n = Dag::navigate(root, p);

    std::cout << n->t->getA()->x(); std::cout <<  " "; std::cout << n->t->getA()->y() << std::endl;
    std::cout << n->t->getB()->x(); std::cout <<  " "; std::cout << n->t->getB()->y() << std::endl;
    std::cout << n->t->getC()->x(); std::cout <<  " "; std::cout << n->t->getC()->y() << std::endl;

    if(p.x() == n->t->getA()->x() && p.y() == n->t->getA()->y())
        return true;
    else if(p.x() == n->t->getB()->x() && p.y() == n->t->getB()->y())
        return true;
    else if(p.x() == n->t->getC()->x() && p.y() == n->t->getC()->y())
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
Dag* Dag::navigate(Dag* dagNode, const Point2Dd& p){

    bool hasChild = true;
    while(hasChild){

        if(dagNode == nullptr){
            return nullptr; // Check di controllo, non dovrebbe mai verificarsi di entrare nella navigate con un puntatore nullo
        }

        // Se il punto è contenuto in questo triangolo, controllo i suoi figli. Se è contenuto nei suoi figli aggiorno il puntatore e iterativamente continuo il ciclo
        if(dagNode->getChildA() != nullptr){
            if(Dag::pointInTriangle(p, dagNode->getChildA()->getTriangle() ))
                dagNode = dagNode->getChildA();
        }

         if(dagNode->getChildB() != nullptr){
            if(Dag::pointInTriangle(p, dagNode->getChildB()->getTriangle()))
                dagNode = dagNode->getChildB();
         }
         if(dagNode->getChildC() != nullptr){
            if(Dag::pointInTriangle(p, dagNode->getChildC()->getTriangle()))
                dagNode = dagNode->getChildC();
        }

        if(dagNode->getChildA() == nullptr && dagNode->getChildB() == nullptr && dagNode->getChildC() == nullptr)
            hasChild = false;

    }
    // Quando non ho più figli restituisco l'ultimo triangolo (il più piccolo) che contiene il mio punto
    return dagNode; // restituisco l'ultimo l'indirizzo del triangolo più piccolo che contiene il punto appena inserito}
}


void Dag::addNode(Dag* node, Dag* Father){

    if(Father->getChildA() == nullptr)
        Father->setChildA(node);

    if(Father->getChildB() == nullptr)
        Father->setChildB(node);

    if(Father->getChildC() == nullptr)
        Father->setChildC(node);


}

void Dag::addNodes(Dag* nodeA, Dag* nodeB, Dag* nodeC, Dag* Father){
    Father->setChildA(nodeA);
    Father->setChildB(nodeB);
    Father->setChildC(nodeC);
}


//
// Getter & Setter per gli attributi
//

Dag* Dag::getChildA(){
    if(this->childA != nullptr)
        return this->childA;
    else
        return nullptr;
}

Dag* Dag::getChildB(){
    if(this->childB != nullptr)
        return this->childB;
    else
        return nullptr;
}

Dag* Dag::getChildC(){
    if(this->childC != nullptr)
        return this->childC;
    else
        return nullptr;
}

Triangle* Dag::getTriangle(){
    if(this->t != nullptr)
        return this->t;
    else
        return nullptr;
}

void Dag::setChildA(Dag* t){
    this->childA = t;
}

void Dag::setChildB(Dag* t){
    this->childB = t;
}

void Dag::setChildC(Dag* t){
    this->childC = t;
}

void Dag::setChildren(Dag* A, Dag* B, Dag* C){
    this->childA = A;
    this->childB = B;
    this->childC = C;
}

void Dag::setTriangle(Triangle* t){
    this->t = t;
}
