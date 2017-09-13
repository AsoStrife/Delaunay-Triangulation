#include <Andrea/Headers/Static/adjacencies.h>

Adjacencies::Adjacencies() {}

/**
 * @brief Adjacencies::setAdjacencies
 * @param A pointer to the triangle to which we will set the adjacences
 * @param A Pointer to the first adjacent triangle of tr1
 * @param A Pointer to the second adjacent triangle of tr1
 * @param A pointer to the triangle father of tr1, the triangle that contain tr1
 * Calculate the adjacencies for triangle tr1. tr2 and tr3 will be adiacients a priori,
 * while for the third adjacent check the triangle parent.
 */
void Adjacencies::setAdjacencies(Triangle* tr1, Triangle* tr2, Triangle* tr3, Triangle* trFather){

    Adjacencies::setAdjacency(tr1, tr2); // AC
    Adjacencies::setAdjacency(tr1, tr3); // AB


    // Check the father of tr1 and check his adjacencies
    if(trFather == nullptr)
        return;

    Triangle* adjTriangle = nullptr;

    // First
    adjTriangle = trFather->getTriangleAdjacentA();
    if(adjTriangle != nullptr){
        if((isAdjacencies(*tr1, *adjTriangle ) == true) && (adjTriangle->getIsDeleted() == false)){
            Adjacencies::setAdjacency(tr1, adjTriangle );
            Adjacencies::overrideAdjacency(adjTriangle,  tr1);
        }
    }

    // Second
    adjTriangle = trFather->getTriangleAdjacentB();
    if(adjTriangle != nullptr){
        if((isAdjacencies(*tr1, *adjTriangle ) == true) && (adjTriangle->getIsDeleted() == false)){
            Adjacencies::setAdjacency(tr1, adjTriangle );
            Adjacencies::overrideAdjacency(adjTriangle, tr1);
        }
    }

    // Third
    adjTriangle = trFather->getTriangleAdjacentC();
    if(adjTriangle != nullptr){
        if((isAdjacencies(*tr1, *adjTriangle ) == true) && (adjTriangle->getIsDeleted() == false)){
            Adjacencies::setAdjacency(tr1, adjTriangle );
            Adjacencies::overrideAdjacency(adjTriangle, tr1);
        }
    }

}

/**
 * @brief Adjacencies::setAdjacenciesAfterFlip
 * @param A pointer to the triangle to which we will set the adjacences
 * @param A Pointer to the first adjacent triangle of tr1
 * @param A pointer to the first triangle father of tr1, the triangle that contain tr1
 * @param A pointer to the second triangle father of tr1, the triangle that contain tr1
 * Calculate the adjacencies for triangle tr1, after it was done a Edge Flip.
 * So the function check two parents: tr1Father and tr2Father and set the second and third adjacencies
 */
void Adjacencies::setAdjacenciesAfterFlip(Triangle* tr1, Triangle* tr2, Triangle* tr1Father, Triangle* tr2Father){

    Adjacencies::setAdjacency(tr1, tr2);
    Triangle* adjTriangle = nullptr;

    // First father
    adjTriangle = tr1Father->getTriangleAdjacentA();
    if( (isAdjacencies(*tr1, *adjTriangle ) ) && (adjTriangle->getIsDeleted() == false)){
        Adjacencies::setAdjacency(tr1, adjTriangle );
        Adjacencies::overrideAdjacency(adjTriangle,  tr1);
    }

    adjTriangle = tr1Father->getTriangleAdjacentB();
    if( (isAdjacencies(*tr1, *adjTriangle ) ) && (adjTriangle->getIsDeleted() == false)){
        Adjacencies::setAdjacency(tr1, adjTriangle );
        Adjacencies::overrideAdjacency(adjTriangle,  tr1);
    }

    adjTriangle = tr1Father->getTriangleAdjacentC();
    if( (isAdjacencies(*tr1, *adjTriangle ) ) && (adjTriangle->getIsDeleted() == false)){
        Adjacencies::setAdjacency(tr1, adjTriangle );
        Adjacencies::overrideAdjacency(adjTriangle,  tr1);
    }

    // Second father
    adjTriangle = tr2Father->getTriangleAdjacentA();
    if( (isAdjacencies(*tr1, *adjTriangle ) ) && (adjTriangle->getIsDeleted() == false)){
        Adjacencies::setAdjacency(tr1, adjTriangle );
        Adjacencies::overrideAdjacency(adjTriangle,  tr1);
    }

    adjTriangle = tr2Father->getTriangleAdjacentB();
    if( (isAdjacencies(*tr1, *adjTriangle ) ) && (adjTriangle->getIsDeleted() == false)){
        Adjacencies::setAdjacency(tr1, adjTriangle );
        Adjacencies::overrideAdjacency(adjTriangle,  tr1);
    }

    adjTriangle = tr2Father->getTriangleAdjacentC();
    if( adjTriangle != nullptr ){
        if( (isAdjacencies(*tr1, *adjTriangle ) ) && (adjTriangle->getIsDeleted() == false)){
            Adjacencies::setAdjacency(tr1, adjTriangle );
            Adjacencies::overrideAdjacency(adjTriangle,  tr1);
        }
    }

}

/**
 * @brief Adjacencies::isAdjacencies
 * @param tr1 the first triangle to check
 * @param tr2 the second triangle to check
 * @return true is tr1 and tr1 are adjacent, false otherwise
 * Check if two triangles are adjacent trying all possible combinations, and return true if
 * the triangles are adjacent.
 */
bool Adjacencies::isAdjacencies(const Triangle& tr1, const Triangle& tr2){

    if(
        // AB
        ( (tr1.getA() == tr2.getA() || tr1.getB() == tr2.getA() || tr1.getC() == tr2.getA()) &&
          (tr1.getA() == tr2.getB() || tr1.getB() == tr2.getB() || tr1.getC() == tr2.getB()) ) )
            return true;

        // BC
       if ( (tr1.getA() == tr2.getB() || tr1.getB() == tr2.getB() || tr1.getC() == tr2.getB()) &&
          (tr1.getA() == tr2.getC() || tr1.getB() == tr2.getC() || tr1.getC() == tr2.getC()) )
           return true;

        // CA
        if( (tr1.getA() == tr2.getC() || tr1.getB() == tr2.getC() || tr1.getC() == tr2.getC()) &&
          (tr1.getA() == tr2.getA() || tr1.getB() == tr2.getA() || tr1.getC() == tr2.getA()) )
            return true;

    return false;
}

/**
 * @brief Adjacencies::isAdjacenciesForTwoPoints
 * @param The triangle to which we will check the adjacences
 * @param First vertex to check
 * @param Second vertex to check
 * @return True if tr have p1 and p2 as verticies, else otherwise
 * Similar to isAdjacencies, but this function check if a triangle have two specific verticies
 */
bool Adjacencies::isAdjacenciesForTwoPoints(const Triangle& tr, const Point2Dd& p1, const Point2Dd& p2){
    if( (*tr.getA() == p1 && *tr.getB() == p2) || (*tr.getB() == p1 && *tr.getA() == p2) ) // AB
        return true;

    else if( (*tr.getA() == p1 && *tr.getC() == p2) || (*tr.getC() == p1 && *tr.getA() == p2) ) // AC
        return true;

    else if( (*tr.getB() == p1 && *tr.getC() == p2) || (*tr.getC() == p1 && *tr.getB() == p2) ) // BC
        return true;
    else
        return false;

}

/**
 * @brief Adjacencies::getThirdPoint
 * @param Triangle* tr
 * @param Point2Dd* p1
 * @param Point2Dd* p2
 * @return Point2Dd*
 * Given a triangle and two points, this method return the third point of that triangle.
 */
Point2Dd* Adjacencies::getThirdPoint(const Triangle& tr, const Point2Dd& p1, const Point2Dd& p2){
    if( (*tr.getA() == p1 && *tr.getB() == p2) || (*tr.getB() == p1 && *tr.getA() == p2) ) // AB
        return tr.getC();

    if( (*tr.getA() == p1 && *tr.getC() == p2) || (*tr.getC() == p1 && *tr.getA() == p2) ) // AC
        return tr.getB();

    if( (*tr.getB() == p1 && *tr.getC() == p2) || (*tr.getC() == p1 && *tr.getB() == p2) ) // BC
        return tr.getA();

    return nullptr;
}

/**
 * @brief Adjacencies::setAdjacency
 * @param A pointer to the triangle to which we will set the adjacent
 * @param A pointer to the adjacent triangle
 * Set adjTriangle as a adjacent of triangle (settings his attribute) in the
 * first free slot.
 */
void Adjacencies::setAdjacency(Triangle* triangle, Triangle* adjTriangle){

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

/**
 * @brief Adjacencies::overrideAdjacency
 * @param A pointer to the triangle to which we will set the adjacent
 * @param A pointer to the adjacent triangle
 * Overrride the adjacency when a new triangle is added. It will be called inside
 * setAdjacencies & setAdjacenciesAfterFlip;
 * If adjTriangle has the same vertex of one of the three adjacencies of *triangle, that attribute
 * will be override with the new adjacentTriangle pointer.
 */
void Adjacencies::overrideAdjacency(Triangle* triangle, Triangle* adjTriangle){

    if( (triangle->getTriangleAdjacentA()->getIsDeleted() == true) && (Adjacencies::isAdjacencies(*adjTriangle, *triangle->getTriangleAdjacentA() ) == true) )
        triangle->setTriangleAdjacentA(adjTriangle);

    if(triangle->getTriangleAdjacentB() != nullptr){
        if( (triangle->getTriangleAdjacentB()->getIsDeleted() == true) && (Adjacencies::isAdjacencies(*adjTriangle, *triangle->getTriangleAdjacentB() ) == true) )
            triangle->setTriangleAdjacentB(adjTriangle);
    }

    if(triangle->getTriangleAdjacentC() != nullptr){
        if( (triangle->getTriangleAdjacentC()->getIsDeleted() == true) && (Adjacencies::isAdjacencies(*adjTriangle, *triangle->getTriangleAdjacentC() ) == true) )
            triangle->setTriangleAdjacentC(adjTriangle);
    }

}

Triangle* Adjacencies::getTriangleAdjacentByTwoPoints(Triangle* tr, const Point2Dd& a, const Point2Dd& b){

    if(Adjacencies::isAdjacenciesForTwoPoints(*tr->getTriangleAdjacentA(), a, b))
        return tr->getTriangleAdjacentA();
    else if(Adjacencies::isAdjacenciesForTwoPoints(*tr->getTriangleAdjacentB(), a, b))
        return tr->getTriangleAdjacentB();

    else if(tr->getTriangleAdjacentC() != nullptr){
    if(Adjacencies::isAdjacenciesForTwoPoints(*tr->getTriangleAdjacentC(), a, b))
        return tr->getTriangleAdjacentC();
    }

    return nullptr;
}
