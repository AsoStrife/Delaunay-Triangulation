#include "Andrea/Headers/Drawable/drawableline.h"
#include <viewer/interfaces/drawable_object.h>
#include <viewer/objects/objects.h>

#include <stdio.h>

DrawableLine::DrawableLine(){}

DrawableLine::DrawableLine(double x1, double y1, double x2, double y2){
    this->p1 = Point2Dd(x1, y1);
    this->p2 = Point2Dd(x2, y2);
}

DrawableLine::DrawableLine(const Point2Dd& p1, const Point2Dd& p2){
    this->p1 = p1;
    this->p2 = p2;
}

// DrawableObject interface
void DrawableLine::draw() const{
    Viewer::drawLine2D(this->p1, this->p2, QColor(0, 0 ,0), 1);
}

Pointd DrawableLine::sceneCenter() const{}

double DrawableLine::sceneRadius() const{}

void DrawableLine::setPoints(const Point2Dd& p1, const Point2Dd& p2){
    this->p1 = p1;
    this->p2 = p2;
}