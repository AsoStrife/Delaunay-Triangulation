#include "Andrea/Headers/dag.h"
#include <viewer/objects/objects.h>
#include <stdio.h>

#include <utils/delaunay_checker.h>
Dag::Dag() {}

/**
  *@link https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
 * @brief sign
 * @param p1
 * @param p2
 * @param p3
 * @return float
 * I due seguenti metodi sono stati implementati per poter controllare che un punto si trovi all'interno di un triangolo
 */
float Dag::sign (const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3){
    return (p1.x() - p3.x()) * (p2.y() - p3.y()) - (p2.x() - p3.x()) * (p1.y() - p3.y());
}

bool Dag::PointInTriangle (const Point2Dd& pt, const Triangle& t){
    if(&t == nullptr)
        return false;

    bool b1, b2, b3;

    b1 = sign(pt, t.getA(), t.getB()) < 0.0f;
    b2 = sign(pt, t.getB(), t.getC()) < 0.0f;
    b3 = sign(pt, t.getC(), t.getA()) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

// Aggiungo un punto alla lista
void Dag::addPoint2Dd(const Point2Dd& p){
    this->points.push_back(p);
}

/**
 * @brief Dag::addRoot
 * @param p1
 * @param p2
 * @param p3
 * Aggiungo la radice della mia dag con i 3 punti del Bounding Triangle
 */
void Dag::addRoot(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3){
    this->points.push_back(p1);
    this->points.push_back(p2);
    this->points.push_back(p3);

    this->nodes.push_back( Triangle(p1, p2, p3) ) ;
}

std::vector<Point2Dd> Dag::getPoints(){
    return this->points;
}


/**
 * @brief Dag::navigate
 * @param Point2Dd p
 * @return Triangle*
 *
 * Passo come parametro un punto, e restituisco il più piccolo triangolo che lo contiene. Nel caso in cui
 * sia il primo punto inserito nella triangolazione, restituirà la radice della Dag, ovvero il Bounding Triangle
 */
Triangle* Dag::navigate(const Point2Dd& p){

    bool hasChild = true;

    Triangle* triangle = &nodes.at(0); // Inizializzo prendendo la radice della dag
    while(hasChild){

        if(triangle == nullptr){
            return nullptr; // Check di controllo, non dovrebbe mai verificarsi di entrare nella navigate con un puntatore nullo
        }

        // Se il punto è contenuto in questo triangolo, controllo i suoi figli. Se è contenuto nei suoi figli aggiorno il puntatore e iterativamente continuo il ciclo
        if(PointInTriangle(p, *triangle)){

            if(PointInTriangle(p, *triangle->getChildA()))
                triangle = triangle->getChildA();
            else if(PointInTriangle(p, *triangle->getChildB()))
                triangle = triangle->getChildB();

            else if(PointInTriangle(p, *triangle->getChildC()))
                triangle = triangle->getChildC();
            else
            hasChild = false;
        }

    }
    // Quando non ho più figli restituisco l'ultimo triangolo (il più piccolo) che contiene il mio punto
    return triangle; // restituisco l'ultimo l'indirizzo del triangolo più piccolo che contiene il punto appena inserito
}

void Dag::addNode(Triangle* node, Triangle* Father, int nChild){
    switch(nChild){
        case(1): Father->setChildA(node); break;
        case(2): Father->setChildB(node); break;
        case(3): Father->setChildC(node); break;
    }
}
