#include "Andrea/Headers/dag.h"

Dag::Dag() {}

Dag::Dag(Triangle* t){
    this->t = t;
}


/**
  *@link https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
 * @brief pointInTriangle
 * @param const Point2Dd& pt
 * @param Triangle* t
 * @return bool
 * Check if point is inside a triangle
 */
bool Dag::pointInTriangle (const Point2Dd& pt, Triangle* tr){

    Point2Dd a = *tr->getA();
    Point2Dd b = *tr->getB();
    Point2Dd c = *tr->getC();

    double Area = 0.5 *(-b.y()*c.x() + a.y()*(-b.x() + c.x()) + a.x()*(b.y() - c.y()) + b.x()*c.y());
    double s = 1/(2*Area)*(a.y()*c.x() - a.x()*c.y() + (c.y() - a.y())*pt.x() + (a.x() - c.x())*pt.y());

    double t = 1/(2*Area)*(a.x()*b.y() - a.y()*b.x() + (a.y() - b.y())*pt.x() + (b.x() - a.x())*pt.y());

    if(s > 0 && t > 0)
        return true;
    else
        return false;

}

/**
 * @brief Dag::checkPointIsVertexOfTriangle
 * @param const Point2Dd& p
 * @param Triangle* triangle
 * @return bool
 * Check if a point is a vertex of a triangle
 */
bool Dag::checkPointIsVertexOfTriangle(const Point2Dd& p, Triangle* triangle){
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
 * @param Dag* dagNode
 * @param const Point2Dd& p
 * @return Dag*
 *
 * Navigate the Dag, starting by dagNode (often is the root). If a point is inside the triangle
 * check the children, update dagNode e repeat the process until exist a child
 */
Dag* Dag::navigate(Dag* dagNode, const Point2Dd& p){

    bool hasChild = true;
    while(hasChild){

        if(dagNode == nullptr)
            return nullptr;

        // Se il punto è contenuto in questo triangolo, controllo i suoi figli. Se è contenuto nei suoi figli aggiorno il puntatore e iterativamente continuo il ciclo
        if(dagNode->getChildA() != nullptr){
            if(Dag::pointInTriangle(p, dagNode->getChildA()->getTriangle() )){
                if(Dag::checkPointIsVertexOfTriangle(p, dagNode->getChildA()->getTriangle()) == true)
                    return nullptr;
                else
                    dagNode = dagNode->getChildA();
            }
        }

         if(dagNode->getChildB() != nullptr){
            if(Dag::pointInTriangle(p, dagNode->getChildB()->getTriangle())){
                if(Dag::checkPointIsVertexOfTriangle(p, dagNode->getChildB()->getTriangle()) == true)
                    return nullptr;
                else
                    dagNode = dagNode->getChildB();
            }
         }

         if(dagNode->getChildC() != nullptr){
            if(Dag::pointInTriangle(p, dagNode->getChildC()->getTriangle())){
                if(Dag::checkPointIsVertexOfTriangle(p, dagNode->getChildC()->getTriangle()) == true)
                    return nullptr;
                else
                    dagNode = dagNode->getChildC();

            }
         }

        if(dagNode->getChildA() == nullptr && dagNode->getChildB() == nullptr && dagNode->getChildC() == nullptr)
            hasChild = false;

    }

    return dagNode;
}

/**
 * @brief Dag::addNode
 * @param Dag* node
 * @param Dag* dagNodefather
 * Add a node as a child of dagNodeFather, setting the node in the first nullptr
 */
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
}

//
// Getter & Setter
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
