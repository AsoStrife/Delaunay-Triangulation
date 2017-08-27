#include "Andrea/Headers/delaunaytriangulationcore.h"

DelaunayTriangulationCore::DelaunayTriangulationCore(){}

bool DelaunayTriangulationCore::addPoint(const Point2Dd& p){


    // Se il punto non esiste posso proseguire
    if( Dag::checkIfPointAlreadyExist(dagNodes.back(), p) == true )
        return false;

    // Pusho il punto appena inserito
    points.push_back(new Point2Dd(p));

    // Ottengo il più piccolo triangolo che contiene il mio punto
    Dag* dagFather = Dag::navigate(dagNodes.front(), p);

    Triangle* tr1 = generateTriangle(points.back(), dagFather->getTriangle()->getA(), dagFather->getTriangle()->getB(), dagFather );
    Triangle* tr2 = generateTriangle(points.back(), dagFather->getTriangle()->getB(), dagFather->getTriangle()->getC(), dagFather );
    Triangle* tr3 = generateTriangle(points.back(), dagFather->getTriangle()->getC(), dagFather->getTriangle()->getA(), dagFather );

    Adjacencies::setAdjacencies(tr1, tr2, tr3, dagFather->getTriangle());
    Adjacencies::setAdjacencies(tr2, tr3, tr1, dagFather->getTriangle());
    Adjacencies::setAdjacencies(tr3, tr1, tr2, dagFather->getTriangle());

    // Faccio risultare il padre come se fosse cancellato
    dagFather->getTriangle()->setIsDeleted(true);

    //tr1->setIsDeleted(true);
    //std::cout << "Triangolo 1 generato (" << tr1->getA()->x() << ", " << tr1->getA()->y() << ") - (" << tr1->getB()->x() << ", " << tr1->getB()->y() << ") - (" << tr1->getC()->x() << ", " << tr1->getC()->y() << ")" << std::endl;
    //std::cout << "Triangolo 2 generato (" << tr2->getA()->x() << ", " << tr2->getA()->y() << ") - (" << tr2->getB()->x() << ", " << tr2->getB()->y() << ") - (" << tr2->getC()->x() << ", " << tr2->getC()->y() << ")" << std::endl;
    //std::cout << "Triangolo 3 generato (" << tr3->getA()->x() << ", " << tr3->getA()->y() << ") - (" << tr3->getB()->x() << ", " << tr3->getB()->y() << ") - (" << tr3->getC()->x() << ", " << tr3->getC()->y() << ")" << std::endl;
    //std::cout << " " << std::endl;

    LegalizeEdge( this->points.back(), tr1 );
    LegalizeEdge( this->points.back(), tr2 );
    LegalizeEdge( this->points.back(), tr3 );

    return true;
}

Triangle* DelaunayTriangulationCore::generateTriangle(Point2Dd* p, Point2Dd* p1, Point2Dd* p2, Dag* father){
    this->triangles.push_back( new Triangle( p, p1, p2 ) );
    this->dagNodes.push_back( new Dag( triangles.back() ) );

    triangles.back()->setDagNode( dagNodes.back() );

    Dag::addNode(dagNodes.back(), father);

    return triangles.back();
}

// Quando devo generare un triangolo partendo da due dag (dopo un edge flip)
Triangle* DelaunayTriangulationCore::generateTriangle(Point2Dd* p, Point2Dd* p1, Point2Dd* p2, Dag* dagNodeFather1, Dag* dagNodeFather2){
    this->triangles.push_back( new Triangle( p, p1, p2 ) );
    this->dagNodes.push_back( new Dag( triangles.back() ) );
    triangles.back()->setDagNode( dagNodes.back() );

    Dag::addNode(dagNodes.back(), dagNodeFather1);
    Dag::addNode(dagNodes.back(), dagNodeFather2);

    return triangles.back();
}

void DelaunayTriangulationCore::LegalizeEdge(Point2Dd* p, Triangle* t){

    Triangle* adjTriangle = t->getTriangleAdjacentC();

    if(adjTriangle != nullptr){
        if(DelaunayTriangulation::Checker::isPointLyingInCircle(*adjTriangle->getA(),  *adjTriangle->getB(),  *adjTriangle->getC(), *p,false) == true){
            std::cout << "TRIANGOLO INVALIDO" << std::endl;
            EdgeFlip(p, t, adjTriangle);
        }
     }

}

void DelaunayTriangulationCore::EdgeFlip(Point2Dd* p, Triangle* tr1, Triangle* tr2){
    tr1->setIsDeleted(true);
    tr2->setIsDeleted(true);

    Triangle* newTriangle1;
    Triangle* newTriangle2;

    if( tr1->getB() == tr2->getC() && tr1->getC() == tr2->getB() ){ // triangolo BC -  CB ==> trovato & testato
        newTriangle1 = generateTriangle(tr1->getA(), tr1->getB(), tr2->getA(), tr1->getDagNode(), tr2->getDagNode() );
        newTriangle2 = generateTriangle(tr1->getA(), tr2->getA(), tr2->getB(), tr1->getDagNode(), tr2->getDagNode() );
        std::cout << "Sono dentro BC -  CB" << std::endl;
    }

    else if( tr1->getB() == tr2->getA() && tr1->getC() == tr2->getC() ){ // triangolo BC - AC ==> trovato & testato
        newTriangle1 = generateTriangle(tr1->getA(), tr1->getB(), tr2->getB(), tr1->getDagNode(), tr2->getDagNode() );
        newTriangle2 = generateTriangle(tr1->getA(), tr2->getB(), tr1->getC(), tr1->getDagNode(), tr2->getDagNode() );
        std::cout << "Sono dentro BC -  ac" << std::endl;
    }

    else if( tr1->getB() == tr2->getB() && tr1->getC() == tr2->getC() ){ // triangolo BC - BC
        newTriangle1 = generateTriangle(tr1->getA(), tr1->getB(), tr2->getC(), tr1->getDagNode(), tr2->getDagNode() );
        newTriangle2 = generateTriangle(tr1->getA(), tr2->getC(), tr2->getA(), tr1->getDagNode(), tr2->getDagNode() );
        std::cout << "Sono dentro bc, bc" << std::endl;
    }

    else if( tr1->getB() == tr2->getA() && tr1->getC() == tr2->getB() ){ // triangolo BC - AB ==> testato
        newTriangle1 = generateTriangle(tr1->getA(), tr2->getC(), tr2->getA(), tr1->getDagNode(), tr2->getDagNode() );
        newTriangle2 = generateTriangle(tr1->getA(), tr1->getC(), tr2->getC(), tr1->getDagNode(), tr2->getDagNode() );
        std::cout << "Sono dentro bc, ab" << std::endl;
        //\Adjacencies::setAdjacenciesAfterFlip(newTriangle1, newTriangle2, tr1, tr2);
    }

    else if( tr1->getB() == tr2->getB() && tr1->getC() == tr2->getA() ){ // triangolo BC - BA ==> trovato & testato
        newTriangle1 = generateTriangle(tr1->getA(), tr2->getC(), tr2->getA(), tr1->getDagNode(), tr2->getDagNode() );
        newTriangle2 = generateTriangle(tr1->getA(), tr1->getB(), tr2->getC(), tr1->getDagNode(), tr2->getDagNode() );
        std::cout << "Sono dentro bc, ba" << std::endl;
    }

    Adjacencies::setAdjacenciesAfterFlip(newTriangle1, newTriangle2, tr1, tr2);
    Adjacencies::setAdjacenciesAfterFlip(newTriangle2, newTriangle1, tr1, tr2);

    //LegalizeEdge(p, newTriangle1);
    //LegalizeEdge(p, newTriangle2);
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

std::vector<Point2Dd> DelaunayTriangulationCore::getPointsForValidation(){
    std::vector<Point2Dd> v;

    for(int i = 0; i < this->points.size(); i++){
        v.push_back(*this->points.at(i));
        this->map.insert ( std::pair<Point2Dd,int>(*this->points.at(i), i) );
    }
    return v;
}

Array2D<unsigned int> DelaunayTriangulationCore::getTrianglesForValidation(){
    //you can initially resize the matrix "triangles" by calling triangles.resize(n, 3),
    //and then fill the matrix using the assignment operator: triangles(i,j) = a;
    Array2D<unsigned int> t;
    t.resize( countNumberOfTriangles(), 3);

        std::cout << " Triangles size: " << this->triangles.size() << std::endl;
    int index = 0;
        for(int i = 0; i < this->triangles.size(); i++){
            if(this->triangles.at(i)->getIsDeleted() == false){
                t(index, 0) = this->map.find( *this->triangles.at(i)->getA() )->second;
                t(index, 1) = this->map.find( *this->triangles.at(i)->getB() )->second;
                t(index, 2) = this->map.find( *this->triangles.at(i)->getC() )->second;
                index++;
            }
        }

    return t;
}

int DelaunayTriangulationCore::countNumberOfTriangles(){
    int b = 0;

    for(int i = 0; i < this->triangles.size(); i++){
        if(this->triangles.at(i)->getIsDeleted() == false){
            b++;
        }
    }
     return b;
}
