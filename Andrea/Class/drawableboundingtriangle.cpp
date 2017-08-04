#include <Andrea/Headers/drawableboundingtriangle.h>
#include <Andrea/Headers/drawableline.h>
#include <viewer/interfaces/drawable_object.h>
#include <viewer/objects/objects.h>
#include <iostream>

// Costruttore vuoto
DrawableBoundingTriangle::DrawableBoundingTriangle(){}

void DrawableBoundingTriangle::definePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;

    l1.setPoints(p1, p2);
    l2.setPoints(p1, p3);
    l3.setPoints(p2, p3);
}

// DrawableObject interface
void DrawableBoundingTriangle::draw() const{
    //Viewer::drawLine2D(this->p1, this->p2, QColor(0, 0 ,0), 1);
    //Viewer::drawLine2D(this->p1, this->p3, QColor(0, 0 ,0), 1);
    //Viewer::drawLine2D(this->p2, this->p3, QColor(0, 0 ,0), 1);

    l1.draw();
    l2.draw();
    l3.draw();
}


Pointd DrawableBoundingTriangle::sceneCenter() const { }

double DrawableBoundingTriangle::sceneRadius() const { }
