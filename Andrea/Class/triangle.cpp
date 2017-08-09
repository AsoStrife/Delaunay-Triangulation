#include "Andrea/Headers/triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3){
    this->A = p1;
    this->B = p2;
    this->C = p3;
}

/*
 * Getter & setter per i 3 punti del triangolo
 */
Point2Dd Triangle::getA() const{
    return this->A;
}

Point2Dd Triangle::getB() const{
    return this->B;
}

Point2Dd Triangle::getC() const{
    return this->C;
}

void Triangle::setA(const Point2Dd& p){
    this->A = p;
}

void Triangle::setB(const Point2Dd& p){
    this->B = p;
}

void Triangle::setC(const Point2Dd& p){
    this->C = p;
}

/*
 * Getter & setter per i 3 figli
 */
void Triangle::setChildA(Triangle* t){
    this->childA = t;
}

void Triangle::setChildB(Triangle* t){
    this->childB = t;
}

void Triangle::setChildC(Triangle* t){
    this->childC = t;
}

void Triangle::setChildren(Triangle* A, Triangle* B, Triangle* C){
    this->childA = A;
    this->childB = B;
    this->childC = C;
}

Triangle* Triangle::getChildA(){
    if(this->childA != nullptr)
        return this->childA;
    else
        return nullptr;
}

Triangle* Triangle::getChildB(){
    if(this->childB != nullptr)
        return this->childB;
    else
        return nullptr;
}

Triangle* Triangle::getChildC(){
    if(this->childC != nullptr)
        return this->childC;
    else
        return nullptr;
}
