#include "Andrea/Headers/delaunaytriangulationcore.h"

DelaunayTriangulationCore::DelaunayTriangulationCore(){}

bool DelaunayTriangulationCore::addPoint(const Point2Dd& p){

    if( dag.checkIfPointAlreadyExist(dagNodes.back(), p) == true )
        return false;

    points.push_back(new Point2Dd(p));

    Node* father = dag.navigate(dagNodes.back(), p);

    Node* nA = new Node(this->points.back(), father->getA(), father->getB() );
    Node* nB = new Node(this->points.back(), father->getB(), father->getC() );
    Node* nC = new Node(this->points.back(), father->getC(), father->getA() );

    //if(triangles.size() > 1)
        //triangles.pop_back();

    triangles.push_back(nA);
    triangles.push_back(nB);
    triangles.push_back(nC);

    //LegalizeEdge( *this->points.back(), *father->getA(), *father->getB(), 1 );
    //LegalizeEdge( *this->points.back(), *father->getB(), *father->getC(), 2 );
    //LegalizeEdge( *this->points.back(), *father->getC(), *father->getA(), 3 );

    //dagNodes.push_back(nA);
    //dagNodes.push_back(nB);
    //dagNodes.push_back(nC);

    dag.addNodes(nA, nB,nC, father);

    std::cout << "Punto inserito: "; std::cout << p.x(); std::cout << " " ; std::cout << p.y() << "  - Indirizzo su funzione addpoint(): " << &p << std::endl;

    return true;
}

void DelaunayTriangulationCore::LegalizeEdge(const Point2Dd& newP, const Point2Dd& p1, const Point2Dd& p2, int e){
    // Edge1 == newP - p1
    // Edge2 == newP - p2
    Node* adjacentNode = nullptr;

    //std::cout << triangles.size() << std::endl;

    for(unsigned int i = 0; i < triangles.size(); i++ ){

        if(e == 1){
            if(newP == *triangles[i]->getA() && p1 == *triangles[i]->getB() || newP == *triangles[i]->getB() && p1 == *triangles[i]->getA() ){
                std::cout << "Adiacenza trovata AB" << std::endl;
                if(DelaunayTriangulation::Checker::isPointLyingInCircle(p1, p2, *triangles.at(i)->getC(), newP, false) == true){
                    //LegalizeEdge(newP, p1, *adjacentNode->getC());
                    std::cout << "Adiacenza AB invalida" << std::endl;
                    break;
                } else{
                    //triangles.push_back( new Node(new Point2Dd(newP), new Point2Dd(p1), adjacentNode->getC() ) );
                    break;
                }
            }
        }


    } // for

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

    this->dagNodes.push_back(new Node(new Point2Dd(p1), new Point2Dd(p2), new Point2Dd(p3)));

    this->triangles.push_back( new Node(this->points.at(0), this->points.at(1), this->points.at(2)) );
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

std::vector<Node*> DelaunayTriangulationCore::getTriangles(){
    return this->triangles;
}
