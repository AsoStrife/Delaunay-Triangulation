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

Dag* Triangle::getDagNode() const{
    return this->dagNode;
}

/*Adjacencies* Triangle::getAdjNode(){
    return this->adjNode;
}
*/
void Triangle::setDagNode(Dag* n){
    this->dagNode = n;
}

/*
void Triangle::setAdjNode(Adjacencies* a){
    this->adjNode = a;
}
*/
void Triangle::setIsDeleted(bool b){
    this->isDeleted = b;
}

bool Triangle::getIsDeleted() const{
    return this->isDeleted;
}


Triangle* Triangle::getTriangleAdjacentA() const{
    return triangleAdjacentA;
}

Triangle* Triangle::getTriangleAdjacentB() const{
    return triangleAdjacentB;
}

Triangle* Triangle::getTriangleAdjacentC() const{
    return triangleAdjacentC;
}

void Triangle::setTriangleAdjacentA(Triangle* tA){
    this->triangleAdjacentA = tA;
}

void Triangle::setTriangleAdjacentB(Triangle* tB){
    this->triangleAdjacentB = tB;
}

void Triangle::setTriangleAdjacentC(Triangle* tC){
    this->triangleAdjacentC = tC;
}


bool Triangle::operator == (const Triangle* t1){
   if( *this->getA() == *t1->getA() && *this->getB() == *t1->getB() && *this->getC() == *t1->getC())
     return true;
   else
     return false;
}
