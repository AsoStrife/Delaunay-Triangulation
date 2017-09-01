#include "Andrea/Headers/dag.h"

Dag::Dag() {}

Dag::Dag(Triangle* t){
    this->t = t;
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

/**
 * @brief Dag::checkIfPointAlreadyExist
 * @param root
 * @param p
 * @return bool
 * Controlla che un punto sia già presente nella triangolazione. Lavora in maniera
 * simile alla navigazione della dag, soltanto che ad ogni nodo controlla
 * che il punto non sia un vertice del triangolo stesso
 */
bool Dag::checkIfPointAlreadyExist(Dag* dagNode, const Point2Dd& p){

    bool hasChild = true;
    while(hasChild){

        if(dagNode == nullptr){
            return false; // Check di controllo, non dovrebbe mai verificarsi di entrare nella navigate con un puntatore nullo
        }

        // Se il punto è contenuto in questo triangolo, controllo i suoi figli. Se è contenuto nei suoi figli aggiorno il puntatore e iterativamente continuo il ciclo
        if(dagNode->getChildA() != nullptr){
            if(Dag::pointInTriangle(p, dagNode->getChildA()->getTriangle() )){
                if(Dag::checkPointInTriangle(p, dagNode->getChildA()->getTriangle()) == true)
                    return true;
                else
                    dagNode = dagNode->getChildA();
            }
        }

         if(dagNode->getChildB() != nullptr){
            if(Dag::pointInTriangle(p, dagNode->getChildB()->getTriangle())){
                if(Dag::checkPointInTriangle(p, dagNode->getChildB()->getTriangle()) == true)
                    return true;
                else
                    dagNode = dagNode->getChildB();
            }
         }
         if(dagNode->getChildC() != nullptr){
            if(Dag::pointInTriangle(p, dagNode->getChildC()->getTriangle())){
                if(Dag::checkPointInTriangle(p, dagNode->getChildC()->getTriangle()) == true)
                    return true;
                else
                    dagNode = dagNode->getChildC();
            }
        }

        if(dagNode->getChildA() == nullptr && dagNode->getChildB() == nullptr && dagNode->getChildC() == nullptr)
            hasChild = false;

    }

    // Quando non ho più figli restituisco l'ultimo triangolo (il più piccolo) che contiene il mio punto
    return false; // restituisco l'ultimo l'indirizzo del triangolo più piccolo che contiene il punto appena inserito}


}

/**
 * @brief Dag::checkPointInTriangle
 * @param p
 * @param triangle
 * @return bool
 * Controllo che il punto non sia uno dei vertici del triangolo, se lo è restituisco TRUE, FALSE altrimenti
 */
bool Dag::checkPointInTriangle(const Point2Dd& p, Triangle* triangle){
    if(p.x() == triangle->getA()->x() && p.y() == triangle->getA()->y())
        return true;
    else if(p.x() == triangle->getB()->x() && p.y() == triangle->getB()->y())
        return true;
    else if(p.x() == triangle->getC()->x() && p.y() == triangle->getC()->y())
        return true;
    else
        return false;
}

/**
 * @brief Dag::navigate
 * @param dagNode*
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


Triangle* Dag::navigateAdj(Dag* dagNode, Triangle* tr){

    bool hasChild = true;
    while(hasChild){

        if(dagNode == nullptr){
            return nullptr; // Check di controllo, non dovrebbe mai verificarsi di entrare nella navigate con un puntatore nullo
        }

        if(dagNode->getChildA() != nullptr){
            if(Adjacencies::isAdjacencies(tr,dagNode->getChildA()->getTriangle() ) == true)
                dagNode = dagNode->getChildA();
        }

         if(dagNode->getChildB() != nullptr){
            if(Adjacencies::isAdjacencies(tr,dagNode->getChildB()->getTriangle() ) == true)
                dagNode = dagNode->getChildB();
         }
         if(dagNode->getChildC() != nullptr){
            if(Adjacencies::isAdjacencies(tr,dagNode->getChildC()->getTriangle() ) == true)
                dagNode = dagNode->getChildC();
        }

        if(dagNode->getChildA() == nullptr && dagNode->getChildB() == nullptr && dagNode->getChildC() == nullptr)
            hasChild = false;

    }
    // Quando non ho più figli restituisco l'ultimo triangolo (il più piccolo) che contiene il mio punto
    return dagNode->getTriangle(); // restituisco l'ultimo l'indirizzo del triangolo più piccolo che contiene il punto appena inserito}
}

void Dag::addNode(Dag* node, Dag* dagNodefather){

    if(dagNodefather->getChildA() == nullptr){
        dagNodefather->setChildA(node);
        return;
    }
    else if(dagNodefather->getChildB() == nullptr){
        dagNodefather->setChildB(node);
        return;
    }
    else if(dagNodefather->getChildC() == nullptr){
        dagNodefather->setChildC(node);
        return;
    }
    else
        std::cout << "sto provando a riempire un nodo pieno" << std::endl;
}

//
// Getter & Setter per gli attributi
//

Dag* Dag::getChildA(){
    return this->childA;
}

Dag* Dag::getChildB(){
    return this->childB;
}

Dag* Dag::getChildC(){
    return this->childC;
}

Triangle* Dag::getTriangle(){
    return this->t;
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

void Dag::setTriangle(Triangle* t){
    this->t = t;
}
