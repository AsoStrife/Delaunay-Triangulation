#include "Andrea/Headers/adjacencies.h"

Adjacencies::Adjacencies() {}

void Adjacencies::setAdjacencies(Triangle* tr1, Triangle* tr2, Triangle* tr3, Triangle* trFather){

    Adjacencies::setAdjacency(tr1, tr2); // AC
    Adjacencies::setAdjacency(tr1, tr3); // AB


    // Per la terza adiacenza controllo il triangolo padre, ovvero quello in cui sono nati i 3 sotto triangoli
    if(trFather == nullptr)
        return;

    Triangle* adjTriangle = nullptr;

    if(trFather->getTriangleAdjacentA() != nullptr && trFather->getTriangleAdjacentB() != nullptr){

        if(isAdjacencies(tr1, trFather->getTriangleAdjacentA()) == true){
            // devo vedere se trFather->getTriangleA ha dei figli
            Triangle* trAdj = Dag::navigateAdj(trFather->getTriangleAdjacentA()->getDagNode(), tr1);
            Adjacencies::setAdjacency(tr1, trAdj );
            Adjacencies::overrideAdjacency(trAdj,  tr1);
        }
        else if(isAdjacencies(tr1, trFather->getTriangleAdjacentB()) == true){
            // devo vedere se trFather->getTriangleB ha dei figli
            Triangle* trAdj = Dag::navigateAdj(trFather->getTriangleAdjacentB()->getDagNode(), tr1);
            Adjacencies::setAdjacency(tr1, trAdj );
            Adjacencies::overrideAdjacency(trAdj, tr1);
        }

        else if(trFather->getTriangleAdjacentC() != nullptr){
            if(isAdjacencies(tr1, trFather->getTriangleAdjacentC()) == true){
                // devo vedere se trFather->getTriangleAdjacentC ha dei figli
                Triangle* trAdj = Dag::navigateAdj(trFather->getTriangleAdjacentC()->getDagNode(), tr1);
                Adjacencies::setAdjacency(tr1, trAdj );
                Adjacencies::overrideAdjacency(trAdj, tr1);
            }
        }
    }

}

void Adjacencies::setAdjacenciesAfterFlip(Triangle* tr1, Triangle* tr2, Triangle* trFather1, Triangle* trFather2){

    Adjacencies::setAdjacency(tr1, tr2);

    int contatore = 0;

    if( (isAdjacencies(tr1, trFather1->getTriangleAdjacentA()) == true) && (trFather1->getTriangleAdjacentA()->getIsDeleted() == false)){
            Adjacencies::setAdjacency(tr1, trFather1->getTriangleAdjacentA() );
            Adjacencies::overrideAdjacency(trFather1->getTriangleAdjacentA(),  tr1);
            contatore++;
        }

    if( (isAdjacencies(tr1, trFather1->getTriangleAdjacentB()) == true) && (trFather1->getTriangleAdjacentB()->getIsDeleted() == false)){
        Adjacencies::setAdjacency(tr1, trFather1->getTriangleAdjacentB() );
        Adjacencies::overrideAdjacency(trFather1->getTriangleAdjacentB(),  tr1);
        contatore++;
    }

    if( trFather1->getTriangleAdjacentC() != nullptr ){
        if((isAdjacencies(tr1, trFather1->getTriangleAdjacentC()) == true) && (trFather1->getTriangleAdjacentC()->getIsDeleted() == false)){
            Adjacencies::setAdjacency(tr1, trFather1->getTriangleAdjacentC() );
            Adjacencies::overrideAdjacency(trFather1->getTriangleAdjacentC(),  tr1);
            contatore++;
        }
    }

    // TRFATHER2
    if( (isAdjacencies(tr1, trFather2->getTriangleAdjacentA()) == true) && (trFather2->getTriangleAdjacentA()->getIsDeleted() == false)){
        Adjacencies::setAdjacency(tr1, trFather2->getTriangleAdjacentA() );
        Adjacencies::overrideAdjacency(trFather2->getTriangleAdjacentA(),  tr1);
        contatore++;
    }

    if( (isAdjacencies(tr1, trFather2->getTriangleAdjacentB()) == true) && (trFather2->getTriangleAdjacentB()->getIsDeleted() == false)){
        Adjacencies::setAdjacency(tr1, trFather2->getTriangleAdjacentB() );
        Adjacencies::overrideAdjacency(trFather2->getTriangleAdjacentB(),  tr1);
        contatore++;
    }

    if( trFather2->getTriangleAdjacentC() != nullptr ){
        if((isAdjacencies(tr1, trFather2->getTriangleAdjacentC()) == true) && (trFather2->getTriangleAdjacentC()->getIsDeleted() == false)){
            Adjacencies::setAdjacency(tr1, trFather2->getTriangleAdjacentC() );
            Adjacencies::overrideAdjacency(trFather2->getTriangleAdjacentC(),  tr1);
            contatore++;
        }
    }

    std::cout << "Triangoli adiacenti trovati dopo il flip : " << contatore << std::endl;
}

// Funzione generale per sapere se due triangoli sono adiacenti
bool Adjacencies::isAdjacencies(Triangle* tr1, Triangle* tr2){

    if(
        // AB
        ( (tr1->getA() == tr2->getA() || tr1->getB() == tr2->getA() || tr1->getC() == tr2->getA()) &&
          (tr1->getA() == tr2->getB() || tr1->getB() == tr2->getB() || tr1->getC() == tr2->getB()) ) )
        return true;

        // BC
       if ( (tr1->getA() == tr2->getB() || tr1->getB() == tr2->getB() || tr1->getC() == tr2->getB()) &&
          (tr1->getA() == tr2->getC() || tr1->getB() == tr2->getC() || tr1->getC() == tr2->getC()) )
           return true;

        // CA
        if( (tr1->getA() == tr2->getC() || tr1->getB() == tr2->getC() || tr1->getC() == tr2->getC()) &&
          (tr1->getA() == tr2->getA() || tr1->getB() == tr2->getA() || tr1->getC() == tr2->getA()) )

            return true;

    return false;
}

bool Adjacencies::isAdjacenciesForTwoPoints(Triangle* tr, const Point2Dd& p1, const Point2Dd& p2){
    if( (*tr->getA() == p1 && *tr->getB() == p2) || (*tr->getB() == p1 && *tr->getA() == p2) ) // AB
        return true;

    else if( (*tr->getA() == p1 && *tr->getC() == p2) || (*tr->getC() == p1 && *tr->getA() == p2) ) // AC
        return true;

    else if( (*tr->getB() == p1 && *tr->getC() == p2) || (*tr->getC() == p1 && *tr->getB() == p2) ) // BC
        return true;
    else
        return false;
}


Point2Dd* Adjacencies::getThirdPoint(Triangle* tr, Point2Dd *p1, Point2Dd *p2){
    if( (*tr->getA() == *p1 && *tr->getB() == *p2) || (*tr->getB() == *p1 && *tr->getA() == *p2) ) // AB
        return tr->getC();

    if( (*tr->getA() == *p1 && *tr->getC() == *p2) || (*tr->getC() == *p1 && *tr->getA() == *p2) ) // AC
        return tr->getB();

    if( (*tr->getB() == *p1 && *tr->getC() == *p2) || (*tr->getC() == *p1 && *tr->getB() == *p2) ) // BC
        return tr->getA();

    return nullptr;
}

void Adjacencies::setAdjacency(Triangle *triangle, Triangle *adjTriangle){

    // Set Adjacencies A
    if(triangle->getTriangleAdjacentA() == nullptr){
        triangle->setTriangleAdjacentA(adjTriangle);
        return;
    }

    // Set Adjacencies B
    if(triangle->getTriangleAdjacentB() == nullptr){
        triangle->setTriangleAdjacentB(adjTriangle);
        return;
    }

    // Set Adjacencies C
    if(triangle->getTriangleAdjacentC() == nullptr){
        triangle->setTriangleAdjacentC(adjTriangle);
        return;
    }

}

// Adjtriangle ha BC = a triangle
void Adjacencies::overrideAdjacency(Triangle* triangle, Triangle *adjTriangle){

    if( (triangle->getTriangleAdjacentA()->getIsDeleted() == true) && (Adjacencies::isAdjacencies(adjTriangle, triangle->getTriangleAdjacentA() ) == true) )
        triangle->setTriangleAdjacentA(adjTriangle);

    if(triangle->getTriangleAdjacentB() != nullptr){
        if( (triangle->getTriangleAdjacentB()->getIsDeleted() == true) && (Adjacencies::isAdjacencies(adjTriangle, triangle->getTriangleAdjacentB() ) == true) )
            triangle->setTriangleAdjacentB(adjTriangle);
    }

    if(triangle->getTriangleAdjacentC() != nullptr){
        if( (triangle->getTriangleAdjacentC()->getIsDeleted() == true) && (Adjacencies::isAdjacencies(adjTriangle, triangle->getTriangleAdjacentC() ) == true) )
            triangle->setTriangleAdjacentC(adjTriangle);
    }

}
