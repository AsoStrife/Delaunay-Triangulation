#include <Andrea/Headers/DataStructures/dagnode.h>

DagNode::DagNode(){}

DagNode::DagNode(Triangle* tr){
    this->tr = tr;
}


/*
 * Getter & Setter
 */

DagNode* DagNode::getChildA(){
    return this->childA;
}

DagNode* DagNode::getChildB(){
    return this->childB;
}

DagNode* DagNode::getChildC(){
    return this->childC;
}

Triangle* DagNode::getTriangle(){
    return this->tr;
}

void DagNode::setChildA(DagNode* dn){
    this->childA = dn;
}

void DagNode::setChildB(DagNode* dn){
    this->childB = dn;
}

void DagNode::setChildC(DagNode* dn){
    this->childC = dn;
}

void DagNode::setTriangle(Triangle* tr){
    this->tr = tr;
}
