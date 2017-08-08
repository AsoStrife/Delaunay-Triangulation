#include "Andrea/Headers/branch.h"

Branch::Branch(){}

Branch::Branch( int f, int c1, int c2, int c3){
    this->father = f;
    this->child1 = c1;
    this->child2 = c2;
    this->child3 = c3;
}

bool Branch::hasChild(){
    if(child1 != 0 || child2 != 0 || child2 != 0)
        return true;
    else
        return false;
}

int Branch::getChild (int child){
    switch(child){
        case(1): return this->child1; break;
        case(2): return this->child2; break;
        case(3): return this->child3; break;

        default: return 0;
    }
}

int Branch::getFather(){
    return this->father;
}

void Branch::setChild(int child, int v){
    switch(child){
        case(1): this->child1 = v; break;
        case(2): this->child2 = v; break;
        case(3): this->child3 = v; break;

        default: 0;
    }
}

void Branch::setFather(int f){
    this->father = f;
}
