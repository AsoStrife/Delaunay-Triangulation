#include "Andrea/Headers/delaunaytriangulationcore.h"

DelaunayTriangulationCore::DelaunayTriangulationCore(){}

bool DelaunayTriangulationCore::addPoint(const Point2Dd& p){


    // Se il punto non esiste posso proseguire
    if( Dag::checkIfPointAlreadyExist(dagNodes.back(), p) == true )
        return false;

    // Pusho il punto appena inserito
    points.push_back(new Point2Dd(p));

    // Ottengo il più piccolo triangolo che contiene il mio punto
    Dag* father = Dag::navigate(dagNodes.front(), p);

    Triangle* t1 = generateTriangle(points.back(), father->getTriangle()->getA(), father->getTriangle()->getB(), father );
    Triangle* t2 = generateTriangle(points.back(), father->getTriangle()->getB(), father->getTriangle()->getC(), father );
    Triangle* t3 = generateTriangle(points.back(), father->getTriangle()->getC(), father->getTriangle()->getA(), father );

    // Faccio risultare il padre come se fosse cancellato
    father->getTriangle()->setIsDeleted(true);

    Adjacencies::setAdjacencies(t1, t2, father->getTriangle()->getAdjNode() );
    Adjacencies::setAdjacencies(t2, t3, father->getTriangle()->getAdjNode() );
    Adjacencies::setAdjacencies(t3, t1, father->getTriangle()->getAdjNode() );

    //LegalizeEdge( *this->points.back(), *father->getA(), *father->getB(), 1 );
    //LegalizeEdge( *this->points.back(), *father->getB(), *father->getC(), 2 );
    //LegalizeEdge( *this->points.back(), *father->getC(), *father->getA(), 3 );

    return true;
}

Triangle* DelaunayTriangulationCore::generateTriangle(Point2Dd* p, Point2Dd* p1, Point2Dd* p2, Dag* father){


    this->triangles.push_back( new Triangle( p, p1, p2 ) );
    this->dagNodes.push_back( new Dag( triangles.back() ) );
    this->adjacencies.push_back( new Adjacencies( triangles.back() ) );

    triangles.back()->setAdjNode( adjacencies.back() );
    triangles.back()->setDagNode( dagNodes.back() );

    Dag::addNode(dagNodes.back(), father);

    return triangles.back();
    /*
    t1->setAdjNode(a1);
    t1->setDagNode(d1);

    t2->setAdjNode(a2);
    t2->setDagNode(d2);

    t3->setAdjNode(a3);
    t3->setDagNode(d3);

    a1->setAdjacencies(t2, t3, father->getTriangle()->getAdjNode() );
    a2->setAdjacencies(t3, t1, father->getTriangle()->getAdjNode() );
    a3->setAdjacencies(t1, t2, father->getTriangle()->getAdjNode() );

    adjacencies.push_back(a1);
    adjacencies.push_back(a2);
    adjacencies.push_back(a3);
    */
}

void DelaunayTriangulationCore::LegalizeEdge(const Point2Dd& newP, const Point2Dd& p1, const Point2Dd& p2, int e){

}


void DelaunayTriangulationCore::cleanDelaunayTriangulation(){
    points.clear();
    triangles.clear();
    dagNodes.clear();
}

void DelaunayTriangulationCore::loadPointFromVector(std::vector<Point2Dd> p){

    for (unsigned int i = 0; i < p.size(); i++){
        addPoint(p[i]);
    }

}

void DelaunayTriangulationCore::setBoundingTrianglePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3){
    this->points.push_back(new Point2Dd(p1));
    this->points.push_back(new Point2Dd(p2));
    this->points.push_back(new Point2Dd(p3));

    this->triangles.push_back( new Triangle( this->points.at(0), this->points.at(1), this->points.at(2)) );
    this->dagNodes.push_back( new Dag( triangles.back() ) );
    this->adjacencies.push_back( new Adjacencies( triangles.back() ) );

    triangles.back()->setAdjNode( adjacencies.back() );
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
    return this->triangles;
}
