#include <Andrea/Headers/Static/dag.h>

Dag::Dag() {}


/**
  *@link https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
 * @brief pointInTriangle
 * @param const Point2Dd& pt
 * @param Triangle* t
 * @return bool
 * Check if point is inside a triangle
 */
bool Dag::pointInTriangle (const Point2Dd& p, const Point2Dd& a, const Point2Dd& b, const Point2Dd& c){

    double Area = 0.5 *(-b.y()*c.x() + a.y()*(-b.x() + c.x()) + a.x()*(b.y() - c.y()) + b.x()*c.y());

    double s = 1/(2*Area)*(a.y()*c.x() - a.x()*c.y() + (c.y() - a.y())*p.x() + (a.x() - c.x())*p.y());

    double t = 1/(2*Area)*(a.x()*b.y() - a.y()*b.x() + (a.y() - b.y())*p.x() + (b.x() - a.x())*p.y());

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
bool Dag::checkPointIsVertexOfTriangle(const Point2Dd& p, const Point2Dd& a, const Point2Dd& b, const Point2Dd& c){
    if(p.x() == a.x() && p.y() == a.y())
        return true;
    else if(p.x() == b.x() && p.y() == b.y())
        return true;
    else if(p.x() == c.x() && p.y() == c.y())
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
DagNode* Dag::navigate(DagNode* dagNode, const Point2Dd& p){

    bool hasChild = true;
        while(hasChild){

            if(dagNode == nullptr)
                return nullptr;

            Triangle* tr = nullptr;

            // Se il punto è contenuto in questo triangolo, controllo i suoi figli. Se è contenuto nei suoi figli aggiorno il puntatore e iterativamente continuo il ciclo
            if(dagNode->getChildA() != nullptr){
                tr = dagNode->getChildA()->getTriangle();

                if(Dag::checkPointIsVertexOfTriangle(p, *tr->getA(), *tr->getB(), *tr->getC() ) == true)
                    return nullptr;

                if(Dag::pointInTriangle(p, *tr->getA(), *tr->getB(), *tr->getC() )){
                    dagNode = dagNode->getChildA();
                }
            }

             if(dagNode->getChildB() != nullptr){
                 tr = dagNode->getChildB()->getTriangle();

                 if(Dag::checkPointIsVertexOfTriangle(p, *tr->getA(), *tr->getB(), *tr->getC() ) == true)
                     return nullptr;

                 if(Dag::pointInTriangle(p, *tr->getA(), *tr->getB(), *tr->getC() )){
                     dagNode = dagNode->getChildB();
                }
             }

             if(dagNode->getChildC() != nullptr){
                 tr = dagNode->getChildC()->getTriangle();

                 if(Dag::checkPointIsVertexOfTriangle(p, *tr->getA(), *tr->getB(), *tr->getC() ) == true)
                     return nullptr;

                 if(Dag::pointInTriangle(p, *tr->getA(), *tr->getB(), *tr->getC() )){
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
void Dag::addNode(DagNode* node, DagNode* dagNodefather){

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
