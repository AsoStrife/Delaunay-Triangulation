#include "Andrea/Headers/delaunaytriangulationcore.h"

DelaunayTriangulationCore::DelaunayTriangulationCore(){}

void DelaunayTriangulationCore::addPoint(const Point2Dd& p){
   // this->dag.addPoint2Dd(p);
     //pointsIT = pushPoint(p);
    //points.emplace_back(new Point2Dd(p.x(), p.y()));

    points.push_back(new Point2Dd(p));

    //std::cout << "Punto inserito: "; std::cout << p.x(); std::cout << " " ; std::cout << p.y() << std::endl;
    //std::cout << "Punto vettore: "; std::cout << points.at(0)->x(); std::cout << " " ; std::cout << points.at(0)->y() << std::endl;

    Node* node = dag.navigate(p);

    Node* nA = new Node(this->points.back(), node->getA(), node->getB() );
    Node* nB = new Node(this->points.back(), node->getB(), node->getC() );
    Node* nC = new Node(this->points.back(), node->getC(), node->getA() );

    dag.addNodes( nA, nB, nC, node);
    triangles.push_back( Triangle( this->points.back(), node->getA(), node->getB() ) );
    triangles.push_back( Triangle( this->points.back(), node->getB(), node->getC() ) );
    triangles.push_back( Triangle( this->points.back(), node->getC(), node->getA() ) );
    //this->LegalizeEdge(p, node->get(), node->getB(), points);

    std::cout << "Punto inserito: "; std::cout << p.x(); std::cout << " " ; std::cout << p.y() << "  - Indirizzo su funzione addpoint(): " << &p << std::endl;

    //std::cout << "V1: "; std::cout << node->getA()->x(); std::cout << " " ; std::cout << node->getA()->y() << std::endl;
    //std::cout << "V2: "; std::cout << node->getB()->x(); std::cout << " " ; std::cout << node->getB()->y() << std::endl;
    //std::cout << "V2: "; std::cout << node->getB()->x(); std::cout << " " ; std::cout << node->getC()->y() << std::endl;

    //std::cout << "Indirizzo triangolo inserito: "; std::cout << node << std::endl;

}

bool DelaunayTriangulationCore::checkIfPointAlreadyExist(const Point2Dd& p){

        for(int i = 0; i < points.size(); i++){
            if(points.at(i)->x() == p.x() && points.at(i)->y() == p.y())
                return true;
        }

        return false;

}


void DelaunayTriangulationCore::cleanDelaunayTriangulation(){
    points.clear();
    triangles.clear();
}

void DelaunayTriangulationCore::loadPointFromVector(const std::vector<Point2Dd>& p){
    int size = p.size();

    if(size > 0){
        for (int i = 0; i < size; i++){

            if(!checkIfPointAlreadyExist(p[i])){
                addPoint(p[i]);
            }
        }
    }
}

void DelaunayTriangulationCore::setBoundingTrianglePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3){
    this->points.push_back(new Point2Dd(p1));
    this->points.push_back(new Point2Dd(p2));
    this->points.push_back(new Point2Dd(p3));

    this->dag.addRoot(new Point2Dd(p1), new Point2Dd(p2), new Point2Dd(p3));
    this->triangles.push_back( Triangle(this->points.at(0), this->points.at(1), this->points.at(2)) );
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

std::vector<Triangle> DelaunayTriangulationCore::getTriangles(){
    return this->triangles;
}
