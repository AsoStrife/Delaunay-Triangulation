#include "Andrea/Headers/adjacencies.h"

Adjacencies::Adjacencies() {}

void Adjacencies::setAdjacencies(Triangle* tr1, Triangle* tr2, Triangle* tr3, Triangle* trFather){


    // Setto al triangolo adj1 adj2 e adj3 come triangoli adiacenti
    if(isAdjacencies(tr1, tr2) == true){
        Adjacencies::setAdjacency(tr1, tr2);
    }

    if(isAdjacencies(tr1, tr3) == true){
        Adjacencies::setAdjacency(tr1, tr3);
    }


    // Per la terza adiacenza controllo il triangolo padre, ovvero quello in cui sono nati i 3 sotto triangoli
    if(trFather == nullptr)
        return;

    if(trFather->getTriangleAdjacentA() != nullptr && trFather->getTriangleAdjacentB() != nullptr){

        if(isAdjacencies(tr1, trFather->getTriangleAdjacentA()) == true){
            // devo vedere se trFather->getTriangleA ha dei figli
            Triangle* trAdj = Dag::navigateAdj(trFather->getTriangleAdjacentA()->getDagNode(), tr1);
            Adjacencies::setAdjacency(tr1, trAdj );
            Adjacencies::overrideAdjacencyC(trAdj,  tr1);
        }
        else if(isAdjacencies(tr1, trFather->getTriangleAdjacentB()) == true){
            // devo vedere se trFather->getTriangleB ha dei figli
            Triangle* trAdj = Dag::navigateAdj(trFather->getTriangleAdjacentB()->getDagNode(), tr1);
            Adjacencies::setAdjacency(tr1, trAdj );
            //Adjacencies::overrideAdjacencyC(trAdj, tr1 );
        }

        else if(trFather->getTriangleAdjacentC() != nullptr){
            if(isAdjacencies(tr1, trFather->getTriangleAdjacentC()) == true){
                // devo vedere se trFather->getTriangleAdjacentC ha dei figli
                Triangle* trAdj = Dag::navigateAdj(trFather->getTriangleAdjacentC()->getDagNode(), tr1);
                Adjacencies::setAdjacency(tr1, trAdj );
                Adjacencies::overrideAdjacencyC(trAdj, tr1 );
            }
        }
    }

}


bool Adjacencies::isAdjacencies(Triangle* tr1, Triangle* tr2){

    if(
        // AB
        ( (tr1->getA() == tr2->getA() || tr1->getB() == tr2->getA() || tr1->getC() == tr2->getA()) &&
          (tr1->getA() == tr2->getB() || tr1->getB() == tr2->getB() || tr1->getC() == tr2->getB()) ) ||
        // BC
        ( (tr1->getA() == tr2->getB() || tr1->getB() == tr2->getB() || tr1->getC() == tr2->getB()) &&
          (tr1->getA() == tr2->getC() || tr1->getB() == tr2->getC() || tr1->getC() == tr2->getC()) ) ||
        // CA
        ( (tr1->getA() == tr2->getC() || tr1->getB() == tr2->getC() || tr1->getC() == tr2->getC()) &&
          (tr1->getA() == tr2->getA() || tr1->getB() == tr2->getA() || tr1->getC() == tr2->getA()) )
       ){
            return true;
    }


    return false;
}

// Potendoci essere diverse combinazioni possibili restituisco un vettore con due elementi che saranno i punti adiacenti

/*std::vector<Point2Dd>  Adjacencies::isAdjacenciesFather(Triangle* tr1, Triangle* tr2){
    // IL triangolo 1 sarà sempre B - C
    // Il triangolo 2 può essere: A - B oppure A - C oppure B - C

    std::vector<Point2Dd> p;

    if( tr1->getB() == tr2->getA() && tr1->getC() == tr2->getB() ){ // triangolo 2 AB
        p.push_back(*tr2->getA());
        p.push_back(*tr2->getB());
    }
    else if( tr1->getB() == tr2->getA() && tr1->getC() == tr2->getC() ){ // triangolo 2 AC
        p.push_back(*tr2->getA());
        p.push_back(*tr2->getC());
    }

    else if( tr1->getB() == tr2->getB() && tr1->getC() == tr2->getC() ){ // triangolo 2 BC
        p.push_back(*tr2->getB());
        p.push_back(*tr2->getC());
    }

    return p;
}*/

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

void Adjacencies::overrideAdjacencyC(Triangle* triangle, Triangle *adjTriangle){
    triangle->setTriangleAdjacentC(adjTriangle);
}
