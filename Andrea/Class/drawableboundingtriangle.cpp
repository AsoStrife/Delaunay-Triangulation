#include <Andrea/Headers/drawableboundingtriangle.h>
#include <viewer/interfaces/drawable_object.h>
#include <viewer/objects/objects.h>
#include <iostream>

// Costruttore vuoto
DrawableBoundingTriangle::DrawableBoundingTriangle(){}

void DrawableBoundingTriangle::definePoints(Point2Dd p1, Point2Dd p2, Point2Dd p3)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

// DrawableObject interface
void DrawableBoundingTriangle::draw() const{
    Viewer::drawLine2D(this->p1, this->p2, QColor(0, 0 ,0), 3);
    Viewer::drawLine2D(this->p1, this->p3, QColor(0, 0 ,0), 3);
    Viewer::drawLine2D(this->p2, this->p3, QColor(0, 0 ,0), 3);
}


Pointd DrawableBoundingTriangle::sceneCenter() const {

}

double DrawableBoundingTriangle::sceneRadius() const {

}
