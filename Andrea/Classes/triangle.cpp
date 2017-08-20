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
    return this->vA;
}

Point2Dd* Triangle::getB() const{
    return this->vB;
}

Point2Dd* Triangle::getC() const{
    return this->vC;
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

Dag* Triangle::getDagNode(){
    return this->dagNode;
}

Adjacencies* Triangle::getAdjNode(){
    return this->adjNode;
}

void Triangle::setDagNode(Dag* n){
    this->dagNode = n;
}

void Triangle::setAdjNode(Adjacencies* a){
    this->adjNode = a;
}

void Triangle::setIsDeleted(bool b){
    this->isDeleted = b;
}

bool Triangle::getIsDeleted() const{
    return this->isDeleted;
}
