#include "Andrea/Headers/triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3){
    this->vA = p1;
    this->vB = p2;
    this->vC = p3;
}

/*
 * Getter & setter per i 3 punti del triangolo
 */
Point2Dd Triangle::getA() const{
    return this->vA;
}

Point2Dd Triangle::getB() const{
    return this->vB;
}

Point2Dd Triangle::getC() const{
    return this->vC;
}

void Triangle::setA(const Point2Dd& p){
    this->vA = p;
}

void Triangle::setB(const Point2Dd& p){
    this->vB = p;
}

void Triangle::setC(const Point2Dd& p){
    this->vC = p;
}
