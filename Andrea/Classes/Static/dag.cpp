#include <Andrea/Headers/Static/dag.h>

Dag::Dag() {}

/**
 * @brief Dag::pointInTriangle
 * @param p is the point that will be insede or outside the triangle
 * @param a is the first vertex of the triangle
 * @param b is the second vertex of the triangle
 * @param c is the third vertex of the triangle
 * @return true if a point is insede a triangle, else otherwise
 * @link https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
 */
bool Dag::pointInTriangle (const Point2Dd& p, const Point2Dd& a, const Point2Dd& b, const Point2Dd& c){

    double Area = 0.5 *(-b.y()*c.x() + a.y()*(-b.x() + c.x()) + a.x()*(b.y() - c.y()) + b.x()*c.y());

    double s = 1/(2*Area)*(a.y()*c.x() - a.x()*c.y() + (c.y() - a.y())*p.x() + (a.x() - c.x())*p.y());

    double t = 1/(2*Area)*(a.x()*b.y() - a.y()*b.x() + (a.y() - b.y())*p.x() + (b.x() - a.x())*p.y());

    if(s > 0 && t > 0 && (1-s-t) > 0)
        return true;
    else
        return false;

}

/**
 * @brief Dag::checkPointIsVertexOfTriangle
 * @param p is the point that will be a vertex of the triangle
 * @param a is the first vertex of the triangle
 * @param b is the second vertex of the triangle
 * @param c is the third vertex of the triangle
 * @return true is p is equal to a, b or c, else otherwise
 * Check if a point is a vertex of the triangle
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
 * @param dagNode is a pointer to the DagNode from which the search will start (often is the root of the Dag)
 * @param p is the point that lie insede one of the triangle of the Dag
 * @return the smallest Triangle (his DagNode ponter) that contain the point p
 * Navigate the Dag, starting by dagNode (often is the root). If a point is inside the triangle
 * check is three children, update dagNode e repeat the process until exist a child
 */
DagNode* Dag::navigate(DagNode* dagNode, const Point2Dd& p){

    bool hasChild = true;

    DagNode copy;

    while(hasChild){

        if(dagNode == nullptr)
            return nullptr;

        copy = *dagNode;

        Triangle* tr = nullptr;

        // If the point is inside this triangle, check is children. If it is contain by one of his children, update the pointer e repeat the loop
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

         // There's not more children. Stop the loop
        if(dagNode->getChildA() == nullptr && dagNode->getChildB() == nullptr && dagNode->getChildC() == nullptr)
            hasChild = false;
    }

    return dagNode;
}

/**
 * @brief Dag::addNode
 * @param node is a pointer to the node that will be setted as a child of dagNodeFather
 * @param dagNodeFather is a pointer to the dag node father to which we will set the child.
 * Add a node as a child of dagNodeFather, setting the node in the first nullptr
 */
void Dag::addNode(DagNode* node, DagNode* dagNodeFather){

    if(dagNodeFather->getChildA() == nullptr){
        dagNodeFather->setChildA(node);
        return;
    }
    else if(dagNodeFather->getChildB() == nullptr){
        dagNodeFather->setChildB(node);
        return;
    }
    else if(dagNodeFather->getChildC() == nullptr){
        dagNodeFather->setChildC(node);
        return;
    }

}
