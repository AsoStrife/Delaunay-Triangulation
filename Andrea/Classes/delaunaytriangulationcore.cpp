#include <Andrea/Headers/delaunaytriangulationcore.h>

DelaunayTriangulationCore::DelaunayTriangulationCore(){}

DelaunayTriangulationCore::~DelaunayTriangulationCore(){ }

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

    DagNode* dagFather = Dag::navigate(dagNodes.front(), p);

    if(dagFather == nullptr) // Point already exist
        return false;

    points.push_back(new Point2Dd(p.x(), p.y()) );

    Triangle* triangleFather = dagFather->getTriangle();


    if(pointLieInALine(*points.back(), *triangleFather->getA(), *triangleFather->getB())){
        std::cout << " AB " << std::endl;
        pointLieAB(points.back(), triangleFather, dagFather);
    }
    else if(pointLieInALine(*points.back(), *triangleFather->getB(), *triangleFather->getC())){
        std::cout << " BC " << std::endl;
        pointLieBC(points.back(), triangleFather, dagFather);

    }
    else if(pointLieInALine(*points.back(), *triangleFather->getC(), *triangleFather->getA())){
        std::cout << " CA " << std::endl;
        pointLieCA(points.back(), triangleFather, dagFather);
    }
    else{
        pointLieInsideTriangle(points.back(), triangleFather, dagFather);
    }

    return true;
}

/**
* @brief DelaunayTriangulationCore::generateTriangle
* @param Point2Dd* p
* @param Point2Dd* p1
* @param Point2Dd* p2
* @param DagNode*dagNodeFather
* @return Triangle*
* Generate a triangle using 3 point. After push_back of triangle, create his corresponding dag node,
* and set as a child of dagNodeFather
*/
Triangle* DelaunayTriangulationCore::generateTriangle(Point2Dd* p,Point2Dd* p1, Point2Dd* p2, DagNode* dagNodeFather){
    this->triangles.push_back( new Triangle( p, p1, p2 ) );
    this->dagNodes.push_back( new DagNode( triangles.back() ) );

    triangles.back()->setDagNode( dagNodes.back() );

    Dag::addNode(dagNodes.back(), dagNodeFather);

    return triangles.back();
}

/**
* @brief DelaunayTriangulationCore::generateTriangle
* @param Point2Dd* p
* @param Point2Dd* p1
* @param Point2Dd* p2
* @param DagNode*dagNodeFather1
* @param DagNode*dagNodeFather2
* @return Triangle*
* Generate a triangle using 3 point after edge flip. After push_back of triangle, create his corresponding dag node,
* and set as a child of dagNodeFather1 and dagNodeFather2
*/
Triangle* DelaunayTriangulationCore::generateTriangle(Point2Dd* p,Point2Dd* p1, Point2Dd* p2, DagNode* dagNodeFather1, DagNode* dagNodeFather2){
    this->triangles.push_back( new Triangle( p, p1, p2 ) );
    this->dagNodes.push_back( new DagNode( triangles.back() ) );
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

    if(tr->getTriangleAdjacentA() != nullptr){
        if(Adjacencies::isAdjacenciesForTwoPoints(tr->getTriangleAdjacentA(), *pi, *pj) == true)
                adjTriangle = tr->getTriangleAdjacentA();
    }

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

    Point2Dd* pk =  Adjacencies::getThirdPoint(*tr2, *pi, *pj);

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
    validTriangles.resize(0,3);
    countValidTriangles = 0;
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
    this->dagNodes.push_back( new DagNode( triangles.back() ) );

    triangles.back()->setDagNode( dagNodes.back() );
}

/**
 * @brief DrawableDelaunayTriangulation::pointLieInALine
 * @param const Point2Dd& p
 * @param const Point2Dd& a
 * @param const Point2Dd& b
 * @return bool
 * Check if point lie in a line
 */
bool DelaunayTriangulationCore::pointLieInALine(const Point2Dd& p, const Point2Dd& a, const Point2Dd& b){

    double tollerance = 0.000001;
    //double tollerance = 0.01;
    //double tollerance = 0.001;

    double pab = a.dist(p) + p.dist(b);

    double ab = a.dist(b);

    if( (pab - ab) < tollerance)
        return true;
    else
        return false;

}

void DelaunayTriangulationCore::pointLieInsideTriangle(Point2Dd* pr, Triangle* triangleFather, DagNode* dagFather){
    Triangle* tr1 = generateTriangle(pr, triangleFather->getA(), triangleFather->getB(), dagFather );
    Triangle* tr2 = generateTriangle(pr, triangleFather->getB(), triangleFather->getC(), dagFather );
    Triangle* tr3 = generateTriangle(pr, triangleFather->getC(), triangleFather->getA(), dagFather );

    triangleFather->setIsDeleted(true);

    Adjacencies::setAdjacencies(tr1, tr2, tr3, triangleFather);
    Adjacencies::setAdjacencies(tr2, tr3, tr1, triangleFather);
    Adjacencies::setAdjacencies(tr3, tr1, tr2, triangleFather);

    legalizeEdge( tr1->getA(), tr1->getB(), tr1->getC(), tr1 );
    legalizeEdge( tr2->getA(), tr2->getB(), tr2->getC(), tr2 );
    legalizeEdge( tr3->getA(), tr3->getB(), tr3->getC(), tr3 );
}
void DelaunayTriangulationCore::pointLieAB(Point2Dd* pr, Triangle* triangleFather, DagNode* dagFather){

    Triangle* adjacentTriangle = Adjacencies::getTriangleAdjacentByTwoPoints(triangleFather, *triangleFather->getA(), *triangleFather->getB());

    DagNode* adjacentDagNode = adjacentTriangle->getDagNode();

    triangleFather->setIsDeleted(true);
    adjacentTriangle->setIsDeleted(true);


    Point2Dd* pl = Adjacencies::getThirdPoint(*adjacentTriangle, *triangleFather->getA(), *triangleFather->getB());

    Triangle* tr1 = generateTriangle(pr, triangleFather->getB(), triangleFather->getC(), dagFather);
    Triangle* tr2 = generateTriangle(pr, triangleFather->getC(), triangleFather->getA(), dagFather);
    Triangle* tr3 = generateTriangle(pr, triangleFather->getA(), pl, adjacentDagNode );
    Triangle* tr4 = generateTriangle(pr, pl, triangleFather->getB(), adjacentDagNode );


    Adjacencies::setAdjacencies(tr1, tr2, tr4, triangleFather);
    Adjacencies::setAdjacencies(tr2, tr3, tr1, triangleFather);
    Adjacencies::setAdjacencies(tr3, tr4, tr2, adjacentTriangle);
    Adjacencies::setAdjacencies(tr4, tr1, tr3, adjacentTriangle);

    legalizeEdge( tr4->getA(), tr4->getB(), tr4->getC(), tr4 );
    legalizeEdge( tr3->getA(), tr3->getB(), tr3->getC(), tr3 );
    legalizeEdge( tr2->getA(), tr2->getB(), tr2->getC(), tr2 );
    legalizeEdge( tr1->getA(), tr1->getB(), tr1->getC(), tr1 );
}

void DelaunayTriangulationCore::pointLieBC(Point2Dd* pr, Triangle* triangleFather, DagNode* dagFather){
    Triangle* adjacentTriangle = Adjacencies::getTriangleAdjacentByTwoPoints(triangleFather, *triangleFather->getB(), *triangleFather->getC());

    DagNode* adjacentDagNode = adjacentTriangle->getDagNode();

    triangleFather->setIsDeleted(true);
    adjacentTriangle->setIsDeleted(true);

    Point2Dd* pl = Adjacencies::getThirdPoint(*adjacentTriangle, *triangleFather->getB(), *triangleFather->getC());

    Triangle* tr1 = generateTriangle(pr, triangleFather->getC(), triangleFather->getA(), dagFather);
    Triangle* tr2 = generateTriangle(pr, triangleFather->getA(), triangleFather->getB(), dagFather);
    Triangle* tr3 = generateTriangle(pr, triangleFather->getB(), pl, adjacentDagNode );
    Triangle* tr4 = generateTriangle(pr, pl, triangleFather->getC(), adjacentDagNode );

    Adjacencies::setAdjacencies(tr1, tr2, tr4, triangleFather);
    Adjacencies::setAdjacencies(tr2, tr3, tr1, triangleFather);
    Adjacencies::setAdjacencies(tr3, tr4, tr2, adjacentTriangle);
    Adjacencies::setAdjacencies(tr4, tr1, tr3, adjacentTriangle);

    legalizeEdge( tr4->getA(), tr4->getB(), tr4->getC(), tr4 );
    legalizeEdge( tr3->getA(), tr3->getB(), tr3->getC(), tr3 );
    legalizeEdge( tr2->getA(), tr2->getB(), tr2->getC(), tr2 );
    legalizeEdge( tr1->getA(), tr1->getB(), tr1->getC(), tr1 );
}

void DelaunayTriangulationCore::pointLieCA(Point2Dd* pr, Triangle* triangleFather, DagNode* dagFather){
    Triangle* adjacentTriangle = Adjacencies::getTriangleAdjacentByTwoPoints(triangleFather, *triangleFather->getC(), *triangleFather->getA());

    DagNode* adjacentDagNode = adjacentTriangle->getDagNode();

    triangleFather->setIsDeleted(true);
    adjacentTriangle->setIsDeleted(true);

    Point2Dd* pl = Adjacencies::getThirdPoint(*adjacentTriangle, *triangleFather->getC(), *triangleFather->getA());

    Triangle* tr1 = generateTriangle(pr, triangleFather->getA(), triangleFather->getB(), dagFather);
    Triangle* tr2 = generateTriangle(pr, triangleFather->getB(), triangleFather->getC(), dagFather);
    Triangle* tr3 = generateTriangle(pr, triangleFather->getC(), pl, adjacentDagNode  );
    Triangle* tr4 = generateTriangle(pr, pl, triangleFather->getA(), adjacentDagNode );

    Adjacencies::setAdjacencies(tr1, tr2, tr4, triangleFather);
    Adjacencies::setAdjacencies(tr2, tr3, tr1, triangleFather);
    Adjacencies::setAdjacencies(tr3, tr4, tr2, adjacentTriangle);
    Adjacencies::setAdjacencies(tr4, tr1, tr3, adjacentTriangle);

    legalizeEdge( tr4->getA(), tr4->getB(), tr4->getC(), tr4 );
    legalizeEdge( tr3->getA(), tr3->getB(), tr3->getC(), tr3 );
    legalizeEdge( tr2->getA(), tr2->getB(), tr2->getC(), tr2 );
    legalizeEdge( tr1->getA(), tr1->getB(), tr1->getC(), tr1 );
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
void DelaunayTriangulationCore::generateTrianglesForValidation(){

    int index = 0;

    for(unsigned int i = 0; i < this->triangles.size(); i++){
        if(this->triangles.at(i)->getIsDeleted() == false){

            this->countValidTriangles++;

            this->validTriangles.resize( this->countValidTriangles, 3);

            this->validTriangles(index, 0) = this->map.find( *this->triangles.at(i)->getA() )->second;
            this->validTriangles(index, 1) = this->map.find( *this->triangles.at(i)->getB() )->second;
            this->validTriangles(index, 2) = this->map.find( *this->triangles.at(i)->getC() )->second;
            index++;
        }
    }
}

int DelaunayTriangulationCore::getCountValidTriangle() const{
    return this->countValidTriangles;
}

Array2D<unsigned int> DelaunayTriangulationCore::getValidTriangles() const{
    return this->validTriangles;
}
