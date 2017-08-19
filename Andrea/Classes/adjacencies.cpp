#include "Andrea/Headers/adjacencies.h"

Adjacencies::Adjacencies() {}

void Adjacencies::addNodes(Triangle* t1, Triangle* t2, Triangle* t3){

}

void Adjacencies::setAdjacencies(Triangle* adj){

}


bool Adjacencies::isAdjacencies(Triangle* t1, Triangle* t2){
    if( t1->getA() == t2->getA() || t1->getC() == t2->getB() )
        return true;

    if( t1->getA() == t2->getA() || t1->getB() == t2->getC() )
        return true;

    return false;
}
