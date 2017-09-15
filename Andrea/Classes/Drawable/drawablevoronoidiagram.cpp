#include "Andrea/Headers/Drawable/drawablevoronoidiagram.h"

DrawableVoronoiDiagram::DrawableVoronoiDiagram(){ }

/**
 * @brief DrawableVoronoiDiagram::draw
 * Calculate the circumcenter of all triangles, and for each of them draw
 * an edge which connects with the circumcircle of the three adjacent triangles
 */
void DrawableVoronoiDiagram::draw() const{

    if(this->triangles.size() > 0){
        for(unsigned int i = 0; i < this->triangles.size(); i++){

            if(this->triangles.at(i)->getIsDeleted() == false){

                Viewer::drawPoint2D( this->getCircumcircle(*triangles.at(i)), this->voronoiLineColor, this->pointSize);

                if(triangles.at(i)->getTriangleAdjacentA() != nullptr)
                    Viewer::drawLine2D( this->getCircumcircle(*triangles.at(i)), this->getCircumcircle(*triangles.at(i)->getTriangleAdjacentA()), this->voronoiLineColor, this->lineSize);
                if(triangles.at(i)->getTriangleAdjacentB() != nullptr)
                    Viewer::drawLine2D( this->getCircumcircle(*triangles.at(i)), this->getCircumcircle(*triangles.at(i)->getTriangleAdjacentB()), this->voronoiLineColor, this->lineSize);
                if(triangles.at(i)->getTriangleAdjacentC() != nullptr)
                  Viewer::drawLine2D( this->getCircumcircle(*triangles.at(i)), this->getCircumcircle(*triangles.at(i)->getTriangleAdjacentC()), this->voronoiLineColor, this->lineSize);

            } // if(*triangles[i]->getIsDeleted == false)
        } //for
    } // size() > 0
}

/**
 * @brief DrawableDelaunayTriangulation::sceneCenter
 * @return the center of the scene
 */
Pointd DrawableVoronoiDiagram::sceneCenter() const {
   return Pointd(0, 0);
}

/**
 * @brief DrawableDelaunayTriangulation::sceneRadius
 * @return -1
 */
double DrawableVoronoiDiagram::sceneRadius() const {
    return -1;
}
/**
 * @brief getCircumcircle
 * @param t is the triangle of which will calculate the circumcircle
 * @link https://en.wikipedia.org/wiki/Circumscribed_circle#Circumcenter_coordinates
 */
Point2Dd DrawableVoronoiDiagram::getCircumcircle(const Triangle& t) const{
    Point2Dd a = *t.getA();
    Point2Dd b = *t.getB();
    Point2Dd c = *t.getC();

    double D = 2 * ( a.x() * (b.y() - c.y()) + b.x() * (c.y() - a.y()) + c.x() * (a.y() - b.y()));

    double x = (1 / D) * ( (pow(a.x(),2) + pow(a.y(),2)) * (b.y() - c.y()) +  (pow(b.x(),2) + pow(b.y(),2)) * (c.y() - a.y()) +  (pow(c.x(),2) + pow(c.y(),2)) * (a.y() - b.y()));

    double y = (1 / D) * ( (pow(a.x(),2) + pow(a.y(),2)) * (c.x() - b.x()) +  (pow(b.x(),2) + pow(b.y(),2)) * (a.x() - c.x()) +  (pow(c.x(),2) + pow(c.y(),2)) * (b.x() - a.x()));

    return Point2Dd(x, y);

}

/**
 * @brief DrawableVoronoiDiagram::setTriangles
 * @param t is the vector of pointer of triangles
 */
void DrawableVoronoiDiagram::setTriangles(const std::vector<Triangle *>& t){
    this->triangles = t;
}

/**
 * @brief DrawableVoronoiDiagram::clearVoronoi
 * Clear the vector of triangles
 */
void DrawableVoronoiDiagram::clearVoronoi(){
    this->triangles.clear();
}
