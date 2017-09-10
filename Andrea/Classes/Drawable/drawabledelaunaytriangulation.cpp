#include <Andrea/Headers/Drawable/drawabledelaunaytriangulation.h>

DrawableDelaunayTriangulation::DrawableDelaunayTriangulation(){}

// DrawableObject interface
void DrawableDelaunayTriangulation::draw() const{

    if(this->triangles.size() > 0){
        for(unsigned int i = 0; i < this->triangles.size(); i++){

            if(this->triangles.at(i)->getIsDeleted() == false){
                if(this->boundingTriangleActive == true){

                    Viewer::drawPoint2D( *triangles[i]->getA(), this->delaunayPointColor, this->pointSize);
                    Viewer::drawPoint2D( *triangles[i]->getB(), this->delaunayPointColor, this->pointSize);
                    Viewer::drawPoint2D( *triangles[i]->getC(), this->delaunayPointColor, this->pointSize);

                    Viewer::drawLine2D( *triangles[i]->getA(), *triangles[i]->getB(), this->delaunayLineColor, this->lineSize);
                    Viewer::drawLine2D( *triangles[i]->getB(), *triangles[i]->getC(), this->delaunayLineColor, this->lineSize);
                    Viewer::drawLine2D( *triangles[i]->getC(), *triangles[i]->getA(), this->delaunayLineColor, this->lineSize);


                }
                else{
                    // Stampo i punti validi
                    if(needToPrintPoint( *triangles[i]->getA() ) == true)
                        Viewer::drawPoint2D( *triangles[i]->getA(), this->delaunayPointColor, this->pointSize);
                    if( needToPrintPoint( *triangles[i]->getB() ) == true)
                        Viewer::drawPoint2D( *triangles[i]->getB(), this->delaunayPointColor, this->pointSize);
                    if( needToPrintPoint( *triangles[i]->getC() ) == true)
                        Viewer::drawPoint2D( *triangles[i]->getC(), this->delaunayPointColor, this->pointSize);

                    // Stampo le linee valide
                    if( needToPrintLine( *triangles[i]->getA(), *triangles[i]->getB() ) == true )
                        Viewer::drawLine2D( *triangles[i]->getA(), *triangles[i]->getB(), this->delaunayLineColor, this->lineSize);

                    if( needToPrintLine( *triangles[i]->getB(), *triangles[i]->getC())  == true )
                        Viewer::drawLine2D( *triangles[i]->getB(), *triangles[i]->getC(), this->delaunayLineColor, this->lineSize);

                    if( needToPrintLine( *triangles[i]->getC(), *triangles[i]->getA())  == true )
                        Viewer::drawLine2D( *triangles[i]->getC(), *triangles[i]->getA(), this->delaunayLineColor, this->lineSize);
                } //  if(this->boundingTriangleActive == true)


            } // if(*triangles[i]->getIsDeleted == false)

        } //for
    } // size() > 0
}

Pointd DrawableDelaunayTriangulation::sceneCenter() const {

}

double DrawableDelaunayTriangulation::sceneRadius() const {

}

void DrawableDelaunayTriangulation::setBoundingTriangleActive(bool b){
    this->boundingTriangleActive = b;
}

bool DrawableDelaunayTriangulation::needToPrintPoint(const Point2Dd& p) const{
    if( p != *BT_P1 && p != *BT_P2 && p != *BT_P3)
        return true;
    else
        return false;
}

bool DrawableDelaunayTriangulation::needToPrintLine(const Point2Dd& p1, const Point2Dd& p2) const{
    if( p1 != *BT_P1 && p1 != *BT_P2 && p1 != *BT_P3 && p2 != *BT_P1 && p2 != *BT_P2 && p2 != *BT_P3)
        return true;
    else
        return false;
}

void DrawableDelaunayTriangulation::clearTriangles(){
    //this->triangles.clear();
}

void DrawableDelaunayTriangulation::setVoronoiActive(bool b){
    this->voronoiActive = b;
}

bool DrawableDelaunayTriangulation::getVoronoiActive() const{
    return this->voronoiActive;
}

void DrawableDelaunayTriangulation::setTriangles(std::vector<Triangle*> t){
    triangles.clear();

    this->triangles = t;

    this->BT_P1 = triangles.at(0)->getA();
    this->BT_P2 = triangles.at(0)->getB();
    this->BT_P3 = triangles.at(0)->getC();
}


