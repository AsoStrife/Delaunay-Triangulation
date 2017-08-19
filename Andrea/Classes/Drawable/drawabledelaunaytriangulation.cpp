#include <Andrea/Headers/Drawable/drawabledelaunaytriangulation.h>

DrawableDelaunayTriangulation::DrawableDelaunayTriangulation(){}

// DrawableObject interface
void DrawableDelaunayTriangulation::draw() const{

    //std::cout << "Dimensione vettore triangoli: " << triangles.size() << std::endl;
    if(this->triangles.size() > 0){
        for(int i = 0; i < this->triangles.size(); i++){
            if(this->boundingTriangleActive == true){

                Viewer::drawPoint2D( Point2Dd(*triangles[i].getA()), this->pointColor, this->pointSize);
                Viewer::drawPoint2D( Point2Dd(*triangles[i].getB()), this->pointColor, this->pointSize);
                Viewer::drawPoint2D( Point2Dd(*triangles[i].getC()), this->pointColor, this->pointSize);

                Viewer::drawLine2D( Point2Dd(*triangles[i].getA()), Point2Dd(*triangles[i].getB()), this->lineColor, this->lineSize);
                Viewer::drawLine2D( Point2Dd(*triangles[i].getB()), Point2Dd(*triangles[i].getC()), this->lineColor, this->lineSize);
                Viewer::drawLine2D( Point2Dd(*triangles[i].getC()), Point2Dd(*triangles[i].getA()), this->lineColor, this->lineSize);
            }
            else{
                // Stampo i punti validi
                if(needToPrintPoint( Point2Dd(*triangles[i].getA()) ) == true)
                    Viewer::drawPoint2D( Point2Dd(*triangles[i].getA()), this->pointColor, this->pointSize);
                if( needToPrintPoint( Point2Dd(*triangles[i].getB()) ) == true)
                    Viewer::drawPoint2D( Point2Dd(*triangles[i].getB()), this->pointColor, this->pointSize);
                if( needToPrintPoint( Point2Dd(*triangles[i].getC()) ) == true)
                    Viewer::drawPoint2D( Point2Dd(*triangles[i].getC()), this->pointColor, this->pointSize);

                // Stampo le linee valide
                if( needToPrintLine( Point2Dd(*triangles[i].getA()), Point2Dd(*triangles[i].getB()) ) == true )
                    Viewer::drawLine2D( Point2Dd(*triangles[i].getA()), Point2Dd(*triangles[i].getB()), this->lineColor, this->lineSize);

                if( needToPrintLine( Point2Dd(*triangles[i].getB()), Point2Dd(*triangles[i].getC()) ) == true )
                    Viewer::drawLine2D( Point2Dd(*triangles[i].getB()), Point2Dd(*triangles[i].getC()), this->lineColor, this->lineSize);

                if( needToPrintLine( Point2Dd(*triangles[i].getC()), Point2Dd(*triangles[i].getA()) ) == true )
                    Viewer::drawLine2D( Point2Dd(*triangles[i].getC()), Point2Dd(*triangles[i].getA()), this->lineColor, this->lineSize);
            }
        }
    }
}

Pointd DrawableDelaunayTriangulation::sceneCenter() const {}
double DrawableDelaunayTriangulation::sceneRadius() const {}

void DrawableDelaunayTriangulation::setTriangles(std::vector<Triangle*> t){

    for(int i = 0; i < t.size(); i++)
        this->triangles.push_back(*t[i]);

    this->BT_P1 = Point2Dd(*triangles.at(0).getA());
    this->BT_P2 = Point2Dd(*triangles.at(0).getB());
    this->BT_P3 = Point2Dd(*triangles.at(0).getC());
}

void DrawableDelaunayTriangulation::setBoundingTriangleActive(bool b){
    this->boundingTriangleActive = b;
}

bool DrawableDelaunayTriangulation::needToPrintPoint(const Point2Dd& p) const{
    if( p != BT_P1 && p != BT_P2 && p != BT_P3)
        return true;
    else
        return false;
}

bool DrawableDelaunayTriangulation::needToPrintLine(const Point2Dd& p1, const Point2Dd& p2) const{
    if( p1 != BT_P1 && p1 != BT_P2 && p1 != BT_P3 && p2 != BT_P1 && p2 != BT_P2 && p2 != BT_P3)
        return true;
    else
        return false;
}

void DrawableDelaunayTriangulation::clearTriangles(){
    this->triangles.clear();
}
