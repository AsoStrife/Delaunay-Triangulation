#include "Andrea/Headers/triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3){
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

//Getter
Point2Dd Triangle::getP1(){
    return this->p1;
}

Point2Dd Triangle::getP2(){
    return this->p2;
}

Point2Dd Triangle::getP3(){
    return this->p3;
}

//Setter
void Triangle::setP1(const Point2Dd& p){
    this->p1 = p;
}

void Triangle::setP2(const Point2Dd& p){
    this->p2 = p;
}

void Triangle::setP3(const Point2Dd& p){
    this->p3 = p;
}
