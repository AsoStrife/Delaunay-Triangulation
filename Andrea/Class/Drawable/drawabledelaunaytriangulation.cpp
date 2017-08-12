#include <Andrea/Headers/Drawable/drawabledelaunaytriangulation.h>

DrawableDelaunayTriangulation::DrawableDelaunayTriangulation(){}

// DrawableObject interface
void DrawableDelaunayTriangulation::draw() const{

    for (int i = 0; i < points.size(); i++){

        points[i].draw();
    }


}

Pointd DrawableDelaunayTriangulation::sceneCenter() const {}
double DrawableDelaunayTriangulation::sceneRadius() const {}

void DrawableDelaunayTriangulation::addDrawablePoint(const Point2Dd& p){
   // this->dag.addPoint2Dd(p);

    this->points.push_back( DrawablePoint(p) );
    Node* node = dag.navigate(p);

    /*
    std::cout << "P: "; std::cout << p.x(); std::cout << " " ; std::cout << p.y() << std::endl;
    std::cout << "V1: "; std::cout << node->getA().x(); std::cout << " " ; std::cout << node->getA().y() << std::endl;
    std::cout << "V2: "; std::cout << node->getC().x(); std::cout << " " ; std::cout << node->getB().y() << std::endl;
    std::cout << "V2: "; std::cout << node->getB().x(); std::cout << " " ; std::cout << node->getC().y() << std::endl;
    */
    //std::cout << "Indirizzo triangolo inserito: "; std::cout << node << std::endl;
}

void DrawableDelaunayTriangulation::addDrawableLine(Point2Dd p1, Point2Dd p2){
    lines.push_back( DrawableLine(p1, p2));
}

bool DrawableDelaunayTriangulation::checkIfPointAlreadyExist(const Point2Dd& p){
    if (std::find(points.begin(), points.end(), DrawablePoint(p)) != points.end())
        return true;
    else
        return false;
}

void DrawableDelaunayTriangulation::cleanDelaunayTriangulation(){
    //p.clear();
    //t.clear();
    points.clear();
    lines.clear();
}

void DrawableDelaunayTriangulation::loadPointFromVector(const std::vector<Point2Dd>& p){
    int size = p.size();

    if(size > 0){
        for (int i = 0; i < size; i++){

            if(!checkIfPointAlreadyExist(p[i])){
                addDrawablePoint(p[i]);
            }
        }
    }
}

void DrawableDelaunayTriangulation::setBoundingTrianglePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3){
    this->BT_P1 = p1;
    this->BT_P2 = p2;
    this->BT_P3 = p3;

    this->dag.addRoot(p1, p2, p3);
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
bool DrawableDelaunayTriangulation::pointLieInALine(const Point2Dd& p, const Point2Dd& a, const Point2Dd& b){
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
