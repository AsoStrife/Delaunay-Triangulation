#include <Andrea/Headers/DataStructures/triangle.h>

Triangle::Triangle() {}

Triangle::Triangle(Point2Dd* vA, Point2Dd* vB, Point2Dd*  vC){
    this->vA = vA;
    this->vB = vB;
    this->vC = vC;
}

Triangle::~Triangle(){ }

/**
 * Getter & Setter
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

void Triangle::setA(Point2Dd* vA){
    this->vA = vA;
}

void Triangle::setB(Point2Dd* vB){
    this->vB = vB;
}

void Triangle::setC(Point2Dd* vC){
    this->vC = vC;
}

DagNode* Triangle::getDagNode() const{
    return this->dagNode;
}

void Triangle::setDagNode(DagNode* dn){
    this->dagNode = dn;
}

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

void Triangle::setTriangleAdjacentA(Triangle* trAdjA){
    this->triangleAdjacentA = trAdjA;
}

void Triangle::setTriangleAdjacentB(Triangle* trAdjB){
    this->triangleAdjacentB = trAdjB;
}

void Triangle::setTriangleAdjacentC(Triangle* trAdjC){
    this->triangleAdjacentC = trAdjC;
}

/**
 * @brief Triangle::operator ==
 * @param tr
 * @return true if two triangles are equals, else otherwise
 */
bool Triangle::operator == (const Triangle& tr){
   if( *this->getA() == *tr.getA() && *this->getB() == *tr.getB() && *this->getC() == *tr.getC())
     return true;
   else
     return false;
}
