#ifndef ADJACENCIES_H
#define ADJACENCIES_H

#include <Andrea/Headers/triangle.h>

class Triangle;

class Adjacencies{

public:
    Adjacencies();

    static void setAdjacencies(Triangle* tr1, Triangle* tr2, Triangle* tr3, Triangle* trFather);

    static void setAdjacency(Triangle *triangle, Triangle *adjTriangle);

    static void setAdjacenciesAfterFlip(Triangle* tr1, Triangle* tr2, Triangle* trFather1, Triangle* trFather2);

    static bool isAdjacencies(Triangle* tr1, Triangle* tr2);

    static void overrideAdjacencyC(Triangle* triangle, Triangle *adjTriangle);

    // Potendoci essere diverse combinazioni possibili restituisco un vettore con due elementi che saranno i punti adiacenti
    //static std::vector<Point2Dd> isAdjacenciesFather(Triangle* tr1, Triangle* tr2);

};

#endif // ADJACENCIES_H
