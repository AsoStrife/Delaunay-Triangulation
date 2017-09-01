#include "Andrea/Headers/delaunaytriangulationcore.h"

DelaunayTriangulationCore::DelaunayTriangulationCore(){}

/**
 * @brief DelaunayTriangulationCore::addPoint
 * @param const Point2Dd p
 * @return bool
 * Add a point inside triagulation.
 * Add point p inside vector of points, and check using Dag structure where the point lie.
 * If point already exist inside the triangulation, return false else generate 3 new triangle
 * and legalize the edge.
 */
bool DelaunayTriangulationCore::addPoint(const Point2Dd& p){

    Dag* dagFather = Dag::navigate(dagNodes.front(), p);

    if(dagFather == nullptr) // Point already exist
        return false;

    points.push_back(new Point2Dd(p.x(), p.y()) );

    Triangle* triangleFather = dagFather->getTriangle();

    Triangle* tr1 = generateTriangle(points.back(), triangleFather->getA(), triangleFather->getB(), dagFather );
    Triangle* tr2 = generateTriangle(points.back(), triangleFather->getB(), triangleFather->getC(), dagFather );
    Triangle* tr3 = generateTriangle(points.back(), triangleFather->getC(), triangleFather->getA(), dagFather );

    triangleFather->setIsDeleted(true);

    Adjacencies::setAdjacencies(tr1, tr2, tr3, triangleFather);
    Adjacencies::setAdjacencies(tr2, tr3, tr1, triangleFather);
    Adjacencies::setAdjacencies(tr3, tr1, tr2, triangleFather);

    legalizeEdge( tr1->getA(), tr1->getB(), tr1->getC(), tr1 );
    legalizeEdge( tr2->getA(), tr2->getB(), tr2->getC(), tr2 );
    legalizeEdge( tr3->getA(), tr3->getB(), tr3->getC(), tr3 );

    return true;
}

/**
* @brief DelaunayTriangulationCore::generateTriangle
* @param Point2Dd* p
* @param Point2Dd* p1
* @param Point2Dd* p2
* @param Dag*dagNodeFather
* @return Triangle*
* Generate a triangle using 3 point. After push_back of triangle, create his corresponding dag node,
* and set as a child of dagNodeFather
*/
Triangle* DelaunayTriangulationCore::generateTriangle(Point2Dd* p,Point2Dd* p1, Point2Dd* p2, Dag* dagNodeFather){
    this->triangles.push_back( new Triangle( p, p1, p2 ) );
    this->dagNodes.push_back( new Dag( triangles.back() ) );

    triangles.back()->setDagNode( dagNodes.back() );

    Dag::addNode(dagNodes.back(), dagNodeFather);

    return triangles.back();
}

/**
* @brief DelaunayTriangulationCore::generateTriangle
* @param Point2Dd* p
* @param Point2Dd* p1
* @param Point2Dd* p2
* @param Dag*dagNodeFather1
* @param Dag*dagNodeFather2
* @return Triangle*
* Generate a triangle using 3 point after edge flip. After push_back of triangle, create his corresponding dag node,
* and set as a child of dagNodeFather1 and dagNodeFather2
*/Triangle* DelaunayTriangulationCore::generateTriangle(Point2Dd* p,Point2Dd* p1, Point2Dd* p2, Dag* dagNodeFather1, Dag* dagNodeFather2){
    this->triangles.push_back( new Triangle( p, p1, p2 ) );
    this->dagNodes.push_back( new Dag( triangles.back() ) );
    triangles.back()->setDagNode( dagNodes.back() );

    Dag::addNode(dagNodes.back(), dagNodeFather1);
    Dag::addNode(dagNodes.back(), dagNodeFather2);

    return triangles.back();
}

/**
 * @brief DelaunayTriangulationCore::legalizeEdge
 * @param Point2Dd* pr
 * @param Point2Dd* pi
 * @param Point2Dd* pj
 * @param Triangle* tr
 * Check if a edge is legal or not, using the adjacencies of a triangle tr
 */
void DelaunayTriangulationCore::legalizeEdge(Point2Dd* pr, Point2Dd* pi, Point2Dd* pj, Triangle* tr){

    Triangle* adjTriangle = nullptr;

    if(tr->getTriangleAdjacentB() != nullptr){
        if(Adjacencies::isAdjacenciesForTwoPoints(tr->getTriangleAdjacentB(), *pi, *pj) == true)
                adjTriangle = tr->getTriangleAdjacentB();
    }

    if(tr->getTriangleAdjacentC() != nullptr){
        if(Adjacencies::isAdjacenciesForTwoPoints(tr->getTriangleAdjacentC(), *pi, *pj) == true)
                adjTriangle = tr->getTriangleAdjacentC();
    }

    if(adjTriangle != nullptr){
        if(DelaunayTriangulation::Checker::isPointLyingInCircle(*adjTriangle->getA(),  *adjTriangle->getB(),  *adjTriangle->getC(), *pr,false) == true){
            edgeFlip(tr, adjTriangle, pr, pi, pj);
        }
     }

}

/**
 * @brief DelaunayTriangulationCore::edgeFlip
 * @param Triangle* tr1
 * @param Triangle* tr2
 * @param Point2Dd* pr
 * @param Point2Dd* pi
 * @param Point2Dd* pj
 * If legalizeEdge find an illegal edge, edgeFlip generate two new triangle using third point of the
 * adjacent triangle. After flip, chek the new edge using legalizeEdge again
 */
void DelaunayTriangulationCore::edgeFlip(Triangle* tr1, Triangle* tr2, Point2Dd* pr, Point2Dd* pi, Point2Dd* pj){
    tr1->setIsDeleted(true);
    tr2->setIsDeleted(true);

    Triangle* newTriangle1 = nullptr;
    Triangle* newTriangle2 = nullptr;

    Point2Dd* pk =  Adjacencies::getThirdPoint(tr2, pi, pj);

    if(pk != nullptr){
        newTriangle1 = generateTriangle(pr, pi, pk, tr1->getDagNode(), tr2->getDagNode() );
        newTriangle2 = generateTriangle(pr, pk, pj, tr1->getDagNode(), tr2->getDagNode() );

        Adjacencies::setAdjacenciesAfterFlip(newTriangle1, newTriangle2, tr1, tr2);
        Adjacencies::setAdjacenciesAfterFlip(newTriangle2, newTriangle1, tr1, tr2);


        legalizeEdge(pr, pi, pk, newTriangle1);
        legalizeEdge(pr, pk, pj, newTriangle2);
    }
}

/**
 * @brief DelaunayTriangulationCore::cleanDelaunayTriangulation
 * Clean vector of points, triangulation, dag and map
 */
void DelaunayTriangulationCore::cleanDelaunayTriangulation(){
    points.clear();
    triangles.clear();
    dagNodes.clear();
    map.clear();
}

/**
 * @brief DelaunayTriangulationCore::loadPointFromVector
 * @param std::vector<Point2Dd>& vectorPoints
 * Add one by one a point inside triangulation
 */
void DelaunayTriangulationCore::loadPointFromVector(const std::vector<Point2Dd>& vectorPoints){

    for (unsigned int i = 0; i < vectorPoints.size(); i++){
        addPoint(vectorPoints.at(i));
    }

}

/**
 * @brief DelaunayTriangulationCore::setBoundingTrianglePoints
 * @param const Point2Dd& p1
 * @param const Point2Dd& p2
 * @param const Point2Dd& p3
 * Set the first three points inside the triangulation as bounding triangle
 */
void DelaunayTriangulationCore::setBoundingTrianglePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3){
    this->points.push_back( new Point2Dd (p1.x(), p1.y() ) );
    this->points.push_back( new Point2Dd (p2.x(), p2.y() ) );
    this->points.push_back( new Point2Dd (p3.x(), p3.y() ) );

    this->triangles.push_back( new Triangle( this->points.at(0), this->points.at(1), this->points.at(2)) );
    this->dagNodes.push_back( new Dag( triangles.back() ) );

    triangles.back()->setDagNode( dagNodes.back() );
}

/**
 * @brief DrawableDelaunayTriangulation::pointLieInALine
 * @param const Point2Dd& p
 * @param const Point2Dd& a
 * @param const Point2Dd& b
 * @return bool
 * @link https://stackoverflow.com/questions/11907947/how-to-check-if-a-point-lies-on-a-line-between-2-other-points
 * Check if point lie in a line
 */
bool DelaunayTriangulationCore::pointLieInALine(const Point2Dd& p, const Point2Dd& a, const Point2Dd& b){
    int cross;

    float dxc = p.x() - a.x();
    float dyc = p.y() - a.y();

    float dxl = b.x() - a.x();
    float dyl = b.y() - a.y();

    cross = dxc * dyl - dyc * dxl;

    if (cross != 0)
        return false;
    else
        return true;
}

/**
 * @brief DelaunayTriangulationCore::getTriangles
 * @return std::vector<Triangle*>
 * Return triangulation
 */
std::vector<Triangle*> DelaunayTriangulationCore::getTriangles(){
    return this->triangles;
}

/***
 * ***************************************** *
    Validation method, not triangulation
 * ***************************************** *
***/

/**
 * @brief DelaunayTriangulationCore::getPointsForValidation
 * @return std::vector<Point2Dd> u
 * Convert my vector of points in std::vector<Point2Dd>
 */
std::vector<Point2Dd> DelaunayTriangulationCore::getPointsForValidation(){
    std::vector<Point2Dd> v;

    for(unsigned int i = 0; i < this->points.size(); i++){
        v.push_back(*this->points.at(i));
        this->map.insert ( std::pair<Point2Dd,int>(*this->points.at(i), i) );
    }
    return v;
}

/**
 * @brief DelaunayTriangulationCore::getTrianglesForValidation
 * @return Array2D<unsigned int>
 * Create a Array2D of my triangulation
 */
Array2D<unsigned int> DelaunayTriangulationCore::getTrianglesForValidation(){
    Array2D<unsigned int> validTriangles;
    validTriangles.resize( countNumberOfTriangles(), 3);

    int index = 0;

    for(unsigned int i = 0; i < this->triangles.size(); i++){
        if(this->triangles.at(i)->getIsDeleted() == false){
            validTriangles(index, 0) = this->map.find( *this->triangles.at(i)->getA() )->second;
            validTriangles(index, 1) = this->map.find( *this->triangles.at(i)->getB() )->second;
            validTriangles(index, 2) = this->map.find( *this->triangles.at(i)->getC() )->second;
            index++;
        }
    }

    return validTriangles;
}

/**
 * @brief DelaunayTriangulationCore::countNumberOfTriangles
 * @return int
 * BruteForce, check how many triangle with isDeleted = false exist
 */
int DelaunayTriangulationCore::countNumberOfTriangles(){
    int validTriangle = 0;

    for(unsigned int i = 0; i < this->triangles.size(); i++){
        if(this->triangles.at(i)->getIsDeleted() == false){
            validTriangle++;
        }
    }
    return validTriangle;
}
