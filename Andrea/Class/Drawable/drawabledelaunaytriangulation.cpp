#include <Andrea/Headers/Drawable/drawabledelaunaytriangulation.h>

DrawableDelaunayTriangulation::DrawableDelaunayTriangulation(){}

// DrawableObject interface
void DrawableDelaunayTriangulation::draw() const{
    /*
     * const Point2Dd BT_P1(1e+10, 0);
     * const Point2Dd BT_P2(0, 1e+10);
     * const Point2Dd BT_P3(-1e+10, -1e+10)
     */
    for(int i = 0; i < this->triangles.size(); i++){
        if(this->boundingTriangleActive == true){

            Viewer::drawPoint2D( Point2Dd(*triangles[i].getA()), QColor(255, 0 ,0), 10);
            Viewer::drawPoint2D( Point2Dd(*triangles[i].getB()), QColor(255, 0 ,0), 10);
            Viewer::drawPoint2D( Point2Dd(*triangles[i].getC()), QColor(255, 0 ,0), 10);

            Viewer::drawLine2D( Point2Dd(*triangles[i].getA()), Point2Dd(*triangles[i].getB()), QColor(0, 0 ,0), 1);
            Viewer::drawLine2D( Point2Dd(*triangles[i].getB()), Point2Dd(*triangles[i].getC()), QColor(0, 0 ,0), 1);
            Viewer::drawLine2D( Point2Dd(*triangles[i].getC()), Point2Dd(*triangles[i].getA()), QColor(0, 0 ,0), 1);
        }
        else{

        }
    }

   //Viewer::drawPoint2D(this->point, QColor(255, 0 ,0), 10);
   //Viewer::drawLine2D(this->p1, this->p2, QColor(0, 0 ,0), 1);
}

Pointd DrawableDelaunayTriangulation::sceneCenter() const {}
double DrawableDelaunayTriangulation::sceneRadius() const {}

void DrawableDelaunayTriangulation::setTriangles(std::vector<Triangle> t){
    this->triangles = t;
}

void DrawableDelaunayTriangulation::setBoundingTriangleActive(bool b){
    this->boundingTriangleActive = b;
}
