#include "Andrea/Headers/node.h"

Node::Node(){}
//Richiamo il costruttore con quello della superclasse
Node::Node(const Point2Dd p1, const Point2Dd p2, const Point2Dd p3) : Triangle(p1, p2, p3){}

void Node::setChildA(Node* t){
    this->childA = t;
}

void Node::setChildB(Node* t){
    this->childB = t;
}

void Node::setChildC(Node* t){
    this->childC = t;
}

void Node::setChildren(Node* A, Node* B, Node* C){
    this->childA = A;
    this->childB = B;
    this->childC = C;
}

Node* Node::getChildA(){
    if(this->childA != nullptr)
        return this->childA;
    else
        return nullptr;
}

Node* Node::getChildB(){
    if(this->childB != nullptr)
        return this->childB;
    else
        return nullptr;
}

Node* Node::getChildC(){
    if(this->childC != nullptr)
        return this->childC;
    else
        return nullptr;
}
