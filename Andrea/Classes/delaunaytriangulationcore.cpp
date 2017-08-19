#include "Andrea/Headers/delaunaytriangulationcore.h"

DelaunayTriangulationCore::DelaunayTriangulationCore(){}

bool DelaunayTriangulationCore::addPoint(const Point2Dd& p){


    // Se il punto non esiste posso proseguire
    if( Dag::checkIfPointAlreadyExist(dagNodes.back(), p) == true )
        return false;

    // Pusho il punto appena inserito
    points.push_back(new Point2Dd(p));

    std::cout << "Punto inserito: "; std::cout << p.x(); std::cout << " " ; std::cout << p.y() << std::endl;


    // Ottengo il più piccolo triangolo che contiene il mio punto
    Dag* father = Dag::navigate(dagNodes.back(), p);


    Dag* nA = new Dag(this->points.back(), father->getTriangle()->getA(), father->getTriangle()->getB() );
    Dag* nB = new Dag(this->points.back(), father->getTriangle()->getB(), father->getTriangle()->getC() );
    Dag* nC = new Dag(this->points.back(), father->getTriangle()->getC(), father->getTriangle()->getA() );

    //if(triangles.size() > 1)
        //triangles.pop_back();

    triangles.push_back(new Triangle( this->points.back(), father->getTriangle()->getA(), father->getTriangle()->getB() ));
    triangles.push_back(new Triangle( this->points.back(), father->getTriangle()->getB(), father->getTriangle()->getC() ));
    triangles.push_back(new Triangle( this->points.back(), father->getTriangle()->getC(), father->getTriangle()->getA() ));

    //LegalizeEdge( *this->points.back(), *father->getA(), *father->getB(), 1 );
    //LegalizeEdge( *this->points.back(), *father->getB(), *father->getC(), 2 );
    //LegalizeEdge( *this->points.back(), *father->getC(), *father->getA(), 3 );

    Dag::addNodes(nA, nB,nC, father);


    return true;
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
    this->dagNodes.push_back( new Dag(triangles.back()) );

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
