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

    //t1->setIsDeleted(true);
    //std::cout << "Triangolo 1 generato (" << t1->getA()->x() << ", " << t1->getA()->y() << ") - (" << t1->getB()->x() << ", " << t1->getB()->y() << ") - (" << t1->getC()->x() << ", " << t1->getC()->y() << ")" << std::endl;
    //std::cout << "Triangolo 2 generato (" << t2->getA()->x() << ", " << t2->getA()->y() << ") - (" << t2->getB()->x() << ", " << t2->getB()->y() << ") - (" << t2->getC()->x() << ", " << t2->getC()->y() << ")" << std::endl;
    //std::cout << "Triangolo 3 generato (" << t3->getA()->x() << ", " << t3->getA()->y() << ") - (" << t3->getB()->x() << ", " << t3->getB()->y() << ") - (" << t3->getC()->x() << ", " << t3->getC()->y() << ")" << std::endl;
    //std::cout << " " << std::endl;

    // Faccio risultare il padre come se fosse cancellato
    father->getTriangle()->setIsDeleted(true);

    // l'errore è nel father->getTriangle()->getAdjNode. Mi prende il padre come 3° adiacenza e non i triangoli delle sue adiacenze
    Adjacencies::setAdjacencies(t1, t2, t3, father->getTriangle()->getAdjNode() );
    Adjacencies::setAdjacencies(t2, t1, t3, father->getTriangle()->getAdjNode() );
    Adjacencies::setAdjacencies(t3, t1, t2, father->getTriangle()->getAdjNode() );

    LegalizeEdge( this->points.back(), t1 );
    LegalizeEdge( this->points.back(), t2 );
    LegalizeEdge( this->points.back(), t3 );

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
}

void DelaunayTriangulationCore::LegalizeEdge(Point2Dd* p, Triangle* t){

    Adjacencies* a = t->getAdjNode();

    if(p != a->getAdjA()->getA()){
        if(DelaunayTriangulation::Checker::isPointLyingInCircle(*a->getAdjA()->getA(),  *a->getAdjA()->getB(),  *a->getAdjA()->getC(), *p, false) == true){
            EdgeFlip(t, a->getAdjA());
        }
    }
    if(p != a->getAdjB()->getA() ){
        if(DelaunayTriangulation::Checker::isPointLyingInCircle(*a->getAdjB()->getA(),  *a->getAdjB()->getB(),  *a->getAdjB()->getC(), *p,false) == true){
            EdgeFlip(t, a->getAdjB());
        }
    }

    if(a->getAdjC() != nullptr){
        if(p != a->getAdjC()->getC()){
            if(DelaunayTriangulation::Checker::isPointLyingInCircle(*a->getAdjC()->getA(),  *a->getAdjC()->getB(),  *a->getAdjC()->getC(), *p,false) == true){
                 EdgeFlip(t, a->getAdjC());
                 //std::cout << "TRIANGOLO INVALIDO" << std::endl;
            }

        }
     }
}

void DelaunayTriangulationCore::EdgeFlip(Triangle* t1, Triangle* t2){
    t1->setIsDeleted(true);
    t2->setIsDeleted(true);

    Triangle* newTriangle1;
    Triangle* newTriangle2;

    if( t1->getB() == t2->getC() && t1->getC() == t2->getB() ){ // triangolo 2 CB
        this->triangles.push_back( new Triangle(t1->getA(), t1->getB(), t2->getA() ));
        this->triangles.push_back( new Triangle(t1->getA(), t2->getA(), t2->getB() ));
    }
    else if( t1->getB() == t2->getA() && t1->getC() == t2->getC() ){ // triangolo 2 AC
        this->triangles.push_back( new Triangle( t1->getA(), t1->getB(), t2->getA() ));
        this->triangles.push_back( new Triangle(t1->getA(), t2->getA(), t2->getC() ));
    }

    else if( t1->getB() == t2->getB() && t1->getC() == t2->getC() ){ // triangolo 2 BC
        this->triangles.push_back( new Triangle( t1->getA(), t1->getB(), t2->getC() ));
        this->triangles.push_back( new Triangle(t1->getA(), t2->getC(), t2->getA() ));
    }

    newTriangle1 = triangles.back()-1;
    newTriangle2 = triangles.back();

    this->dagNodes.push_back( new Dag( newTriangle1 ) );
    this->dagNodes.push_back( new Dag( newTriangle2 ) );

    Dag::addNode(dagNodes.back()-1, t1->getDagNode());
    Dag::addNode(dagNodes.back()-1, t2->getDagNode());
    Dag::addNode(dagNodes.back(), t1->getDagNode());
    Dag::addNode(dagNodes.back(), t2->getDagNode());


    this->adjacencies.push_back( new Adjacencies( newTriangle1) );
    this->adjacencies.push_back( new Adjacencies( newTriangle2) );

    newTriangle1->setAdjNode( adjacencies.back()-1 );
    newTriangle1->setDagNode( dagNodes.back()-1 );

    newTriangle2->setAdjNode( adjacencies.back() );
    newTriangle2->setDagNode( dagNodes.back() );

}

void DelaunayTriangulationCore::cleanDelaunayTriangulation(){
    points.clear();
    triangles.clear();
    dagNodes.clear();
    adjacencies.clear();
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
