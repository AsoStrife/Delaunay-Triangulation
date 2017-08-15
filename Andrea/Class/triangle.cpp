#include "Andrea/Headers/triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(Point2Dd* p1, Point2Dd* p2, Point2Dd*  p3){
    this->vA = p1;
    this->vB = p2;
    this->vC = p3;
}

/*
 * Getter & setter per i 3 punti del triangolo
 */
Point2Dd* Triangle::getA() const{
    if(this->vA != nullptr)
        return this->vA;
    else
        return nullptr;
}

Point2Dd* Triangle::getB() const{
    if(this->vB != nullptr)
        return this->vB;
    else
        return nullptr;
}

Point2Dd* Triangle::getC() const{
    if(this->vC != nullptr)
        return this->vC;
    else
        return nullptr;
}

void Triangle::setA(Point2Dd* p){
    this->vA = p;
}

void Triangle::setB(Point2Dd* p){
    this->vB = p;
}

void Triangle::setC(Point2Dd* p){
    this->vC = p;
}
