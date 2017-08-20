#include "Andrea/Headers/adjacencies.h"

Adjacencies::Adjacencies() {}

Adjacencies::Adjacencies(Triangle* t) {
    this->t = t;
}


void Adjacencies::setAdjacencies(Triangle* adj1, Triangle* adj2, Adjacencies* father){

    if(isAdjacencies(adj1, adj2) == true){
        //std::cout << " Triangolo adiacente a b trovato" << std::endl;
        Adjacencies::setAdjacency(adj2, adj1->getAdjNode());
        Adjacencies::setAdjacency(adj1, adj2->getAdjNode());
    }


    if(father == nullptr)
        exit(0);

    if(father->getAdjA() != nullptr){
        if(isAdjacencies(adj1, father->getAdjA() ) == true){
            Adjacencies::setAdjacency(father->getAdjA(), adj1->getAdjNode() );
            //std::cout << " Triangolo adiacente 3-1 trovato" << std::endl;
        }
    }

    if(father->getAdjB() != nullptr){
        if(isAdjacencies(adj1, father->getAdjB() ) == true){
            Adjacencies::setAdjacency(father->getAdjB(), adj1->getAdjNode() );
            std::cout << " Triangolo adiacente 3-2 trovato" << std::endl;
        }
    }
    if(father->getAdjC() != nullptr){
        if(isAdjacencies(adj1, father->getAdjC() ) == true){
            Adjacencies::setAdjacency(father->getAdjC(), adj1->getAdjNode() );
            //std::cout << " Triangolo adiacente 3-3 trovato" << std::endl;
        }
    }

}


bool Adjacencies::isAdjacencies(Triangle* t1, Triangle* t2){

    if( t1->getA() == t2->getA() && t1->getC() == t2->getB() )
        return true;
    if( t1->getA() == t2->getA() && t1->getB() == t2->getC() )
        return true;
    if( t1->getC() == t2->getA() && t1->getB() == t2->getB() )
        return true;

    return false;
}

void Adjacencies::setAdjacency(Triangle *adj, Adjacencies *father){
    if(father->getAdjA() == nullptr)
        father->setAdjA(adj);

    else if(father->getAdjB() == nullptr)
        father->setAdjB(adj);

    else if(father->getAdjB() == nullptr)
        father->setAdjC(adj);
}

// Getter & setter
// Getter & Setter
Triangle* Adjacencies::getTriangle(){
    return this->t;
}

Triangle* Adjacencies::getAdjA(){
    return this->adjA;
}

Triangle* Adjacencies::getAdjB(){
    return this->adjB;
}

Triangle* Adjacencies::getAdjC(){
    return this->adjC;
}

void Adjacencies::setTriangle(Triangle* t){
    this->t = t;
}

void Adjacencies::setAdjA(Triangle* t){
    this->adjA = t;
}

void Adjacencies::setAdjB(Triangle* t){
    this->adjB = t;
}

void Adjacencies::setAdjC(Triangle* t){
    this->adjC = t;
}
