#include "Andrea/Headers/adjacencies.h"

Adjacencies::Adjacencies() {}

void Adjacencies::addNodes(Node* n1, Node* n2, Node* n3){
    Node* current;

    //if(Adjacencies::isAdjacencies(n1, n2) == true){ }
}

void Adjacencies::setAdjacenciesA(Node* father, Node* adj){
    father->setChildA(adj);
}

void Adjacencies::setAdjacenciesB(Node* father, Node* adj){
    father->setChildA(adj);

}

void Adjacencies::setAdjacenciesC(Node* father, Node* adj){
    father->setChildA(adj);

}

bool Adjacencies::isAdjacencies(Node* n1, Node* n2){
    if( n1->getA() == n2->getA() || n1->getC() == n2->getB() )
        return true;

    if( n1->getA() == n2->getA() || n1->getB() == n2->getC() )
        return true;
}

