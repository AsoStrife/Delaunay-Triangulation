#include <Andrea/Headers/drawablepoint.h>
#include <viewer/interfaces/drawable_object.h>
#include <viewer/objects/objects.h>

#include <stdio.h>
DrawablePoint::DrawablePoint(){}

DrawablePoint::DrawablePoint(double x, double y){
    this->x = x;
    this->y = y;

    this->point = Point2Dd(x, y);
}

DrawablePoint::DrawablePoint(const Point2Dd& p){
    this->point = p;

    this->x = p.x();
    this->y = p.y();
}

// DrawableObject interface
void DrawablePoint::draw() const{
    Viewer::drawPoint2D(this->point, QColor(0, 0 ,0), 3);
}


Pointd DrawablePoint::sceneCenter() const {

}

double DrawablePoint::sceneRadius() const {

}

void DrawablePoint::setx(double x){
    this->x = x;
    updatePoint();
}

void DrawablePoint::sety(double y){
    this->y = y;
    updatePoint();
}

void DrawablePoint::setPoints(double x, double y){
    this->x = x;
    this->y = y;

    updatePoint();
}

void DrawablePoint::updatePoint(){
    this->point = Point2Dd(this->x, this->y);
}

double DrawablePoint::getx() const{
    return this->x;
}

double DrawablePoint::gety() const{
    return this->y;
}

/**
 * @brief operator ==
 * @param p1 DrawablePoint
 * @param p2 DrawablePoint
 * @return bool
 * Definisco quando due DrawablePoint sono uguali
 */
bool DrawablePoint::operator == (const DrawablePoint &p1)
{
   if( this->getx() == p1.getx() && this->getx() == p1.getx())
     return true;
   else
     return false;
}
