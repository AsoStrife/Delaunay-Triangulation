#include "Andrea/Headers/Drawable/drawablevoronoidiagram.h"

DrawableVoronoiDiagram::DrawableVoronoiDiagram(){ }

// DrawableObject interface
void DrawableVoronoiDiagram::draw() const{

    if(this->triangles.size() > 0){
        for(unsigned int i = 0; i < this->triangles.size(); i++){

            if(this->triangles.at(i)->getIsDeleted() == false){

                Viewer::drawPoint2D( this->getCircumcircle(triangles.at(i)), this->voronoiLineColor, this->pointSize);

                if(triangles.at(i)->getTriangleAdjacentA() != nullptr)
                    Viewer::drawLine2D( this->getCircumcircle(triangles.at(i)), this->getCircumcircle(triangles.at(i)->getTriangleAdjacentA()), this->voronoiLineColor, this->lineSize);
                if(triangles.at(i)->getTriangleAdjacentB() != nullptr)
                    Viewer::drawLine2D( this->getCircumcircle(triangles.at(i)), this->getCircumcircle(triangles.at(i)->getTriangleAdjacentB()), this->voronoiLineColor, this->lineSize);
                if(triangles.at(i)->getTriangleAdjacentC() != nullptr)
                  Viewer::drawLine2D( this->getCircumcircle(triangles.at(i)), this->getCircumcircle(triangles.at(i)->getTriangleAdjacentC()), this->voronoiLineColor, this->lineSize);
            } // if(*triangles[i]->getIsDeleted == false)
        } //for
    } // size() > 0
}

Pointd DrawableVoronoiDiagram::sceneCenter() const {

}

double DrawableVoronoiDiagram::sceneRadius() const {

}

/**
 * @brief getCircumcircle
 * @param t
 * @link https://en.wikipedia.org/wiki/Circumscribed_circle#Circumcenter_coordinates
 */
Point2Dd DrawableVoronoiDiagram::getCircumcircle(Triangle *t) const{
    Point2Dd a = *t->getA();
    Point2Dd b = *t->getB();
    Point2Dd c = *t->getC();

    double D = 2 * ( a.x() * (b.y() - c.y()) + b.x() * (c.y() - a.y()) + c.x() * (a.y() - b.y()));

    double x = (1 / D) * ( (pow(a.x(),2) + pow(a.y(),2)) * (b.y() - c.y()) +  (pow(b.x(),2) + pow(b.y(),2)) * (c.y() - a.y()) +  (pow(c.x(),2) + pow(c.y(),2)) * (a.y() - b.y()));

    double y = (1 / D) * ( (pow(a.x(),2) + pow(a.y(),2)) * (c.x() - b.x()) +  (pow(b.x(),2) + pow(b.y(),2)) * (a.x() - c.x()) +  (pow(c.x(),2) + pow(c.y(),2)) * (b.x() - a.x()));

    /*
    std::cout << "xa: " << a.x() << " - yb " << a.y() << std::endl;
    std::cout << "xb: " << b.x() << " - yb " << b.y() << std::endl;
    std::cout << "xc: " << c.x() << " - yb " << c.y() << std::endl;
    std::cout << "x: " << x << " - y " << y << std::endl;
    */
    return Point2Dd(x, y);

}

void DrawableVoronoiDiagram::setTriangles(std::vector<Triangle *> t){
    this->triangles = t;
}

void DrawableVoronoiDiagram::clearVoronoi(){
    this->triangles.clear();
}
