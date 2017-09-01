#include "Andrea/Headers/delaunaytriangulationcore.h"

DelaunayTriangulationCore::DelaunayTriangulationCore(){}

bool DelaunayTriangulationCore::addPoint(const Point2Dd& p){

    // Se il punto non esiste posso proseguire
    if( Dag::checkIfPointAlreadyExist(dagNodes.front(), p) == true )
        return false;

    // Pusho il punto appena inserito
    points.push_back(new Point2Dd(p.x(), p.y()) );

    // Ottengo il più piccolo triangolo che contiene il mio punto, sia il suo nodo DAG che il suo Triangolo
    Dag* dagFather = Dag::navigate(dagNodes.front(), p);
    Triangle* triangleFather = dagFather->getTriangle();

    Triangle* tr1 = generateTriangle(points.back(), triangleFather->getA(), triangleFather->getB(), dagFather );
    Triangle* tr2 = generateTriangle(points.back(), triangleFather->getB(), triangleFather->getC(), dagFather );
    Triangle* tr3 = generateTriangle(points.back(), triangleFather->getC(), triangleFather->getA(), dagFather );

    triangleFather->setIsDeleted(true);

    Adjacencies::setAdjacencies(tr1, tr2, tr3, triangleFather);
    Adjacencies::setAdjacencies(tr2, tr3, tr1, triangleFather);
    Adjacencies::setAdjacencies(tr3, tr1, tr2, triangleFather);

    // Faccio risultare il padre come se fosse cancellato

    legalizeEdge( tr1->getA(), tr1->getB(), tr1->getC(), tr1 );
    legalizeEdge( tr2->getA(), tr2->getB(), tr2->getC(), tr2 );
    legalizeEdge( tr3->getA(), tr3->getB(), tr3->getC(), tr3 );

    return true;
}

// Genero un nuovo triangolo, ovvero creo e aggiungo il puntatore al vettore dei triangoli, creo il suo nodo della dag e associo alla Dag e Triangolo i corrispettivi puntatori
Triangle* DelaunayTriangulationCore::generateTriangle(Point2Dd* p,Point2Dd* p1, Point2Dd* p2, Dag* dagNodeFather){
    this->triangles.push_back( new Triangle( p, p1, p2 ) );
    this->dagNodes.push_back( new Dag( triangles.back() ) );

    triangles.back()->setDagNode( dagNodes.back() );

    Dag::addNode(dagNodes.back(), dagNodeFather);

    return triangles.back();
}

// Quando devo generare un triangolo partendo da due dag (dopo un edge flip)
Triangle* DelaunayTriangulationCore::generateTriangle(Point2Dd* p,Point2Dd* p1, Point2Dd* p2, Dag* dagNodeFather1, Dag* dagNodeFather2){
    this->triangles.push_back( new Triangle( p, p1, p2 ) );
    this->dagNodes.push_back( new Dag( triangles.back() ) );
    triangles.back()->setDagNode( dagNodes.back() );

    Dag::addNode(dagNodes.back(), dagNodeFather1);
    Dag::addNode(dagNodes.back(), dagNodeFather2);

    return triangles.back();
}

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

void DelaunayTriangulationCore::cleanDelaunayTriangulation(){
    points.clear();
    triangles.clear();
    dagNodes.clear();
    map.clear();
}

void DelaunayTriangulationCore::loadPointFromVector(const std::vector<Point2Dd>& vectorPoints){

    for (unsigned int i = 0; i < vectorPoints.size(); i++){
        addPoint(vectorPoints.at(i));
    }

}

void DelaunayTriangulationCore::setBoundingTrianglePoints(const Point2Dd &p1, const Point2Dd &p2, const Point2Dd &p3){
    this->points.push_back( new Point2Dd (p1.x(), p1.y() ) );
    this->points.push_back( new Point2Dd (p2.x(), p2.y() ) );
    this->points.push_back( new Point2Dd (p3.x(), p3.y() ) );

    this->triangles.push_back( new Triangle( this->points.at(0), this->points.at(1), this->points.at(2)) );
    this->dagNodes.push_back( new Dag( triangles.back() ) );

    triangles.back()->setDagNode( dagNodes.back() );
}

/**
 * @brief DrawableDelaunayTriangulation::pointLieInALine
 * @param p
 * @param a
 * @param b
 * @return bool
 * @link https://stackoverflow.com/questions/11907947/how-to-check-if-a-point-lies-on-a-line-between-2-other-points
 * Controllo che un punto non cada su un edge già esistente
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

std::vector<Triangle*> DelaunayTriangulationCore::getTriangles(){
    /*std::vector<Triangle*> newVector;

    for(unsigned i = 0; i < triangles.size(); i++){
        if(triangles.at(i)->getIsDeleted() == false)
            newVector.push_back(triangles.at(i));
    }

    return newVector; */

    return this->triangles;
}

/***
 * ***************************************** *
 * ***************************************** *
 * ***************************************** *
    Metodi per la validazione della
    triangolazione, non propriamente
    ottimali.
 * ***************************************** *
 * ***************************************** *
 * ***************************************** *
***/

/**
 * @brief DelaunayTriangulationCore::getPointsForValidation
 * @return std::vector<Point2Dd> u
 * Converto il mio vettore di puntatori in un vettore di punti
 * aggiungendo gli indici alla mappa per i triangoli
 */
std::vector<Point2Dd> DelaunayTriangulationCore::getPointsForValidation(){
    std::vector<Point2Dd> v;

    for(int i = 0; i < this->points.size(); i++){
        v.push_back(*this->points.at(i));
        this->map.insert ( std::pair<Point2Dd,int>(*this->points.at(i), i) );
    }
    return v;
}

/**
 * @brief DelaunayTriangulationCore::getTrianglesForValidation
 * @return Array2D<unsigned int>
 * Cerco i triangoli ancora validi e li associo i loro vertici
 * agli indici presenti nella mappa dei triangoli
 */
Array2D<unsigned int> DelaunayTriangulationCore::getTrianglesForValidation(){
    Array2D<unsigned int> validTriangles;
    validTriangles.resize( countNumberOfTriangles(), 3);

    int index = 0;

    for(int i = 0; i < this->triangles.size(); i++){
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
 * BruteForce, controllo quanti triangoli validi sono presenti nel vettore dei triangoli, ovvero che hanno isDeleted = false
 */
int DelaunayTriangulationCore::countNumberOfTriangles(){
    int validTriangle = 0;

    for(int i = 0; i < this->triangles.size(); i++){
        if(this->triangles.at(i)->getIsDeleted() == false){
            validTriangle++;
        }
    }
    return validTriangle;
}
