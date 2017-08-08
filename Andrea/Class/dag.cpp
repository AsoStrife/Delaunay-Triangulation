#include "Andrea/Headers/dag.h"
#include <viewer/objects/objects.h>

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
float Dag::sign (Point2Dd p1, Point2Dd p2, Point2Dd p3){
    return (p1.x() - p3.x()) * (p2.y() - p3.y()) - (p2.x() - p3.x()) * (p1.y() - p3.y());
}

bool Dag::PointInTriangle (Point2Dd pt, Point2Dd v1, Point2Dd v2, Point2Dd v3){
    bool b1, b2, b3;

    b1 = sign(pt, v1, v2) < 0.0f;
    b2 = sign(pt, v2, v3) < 0.0f;
    b3 = sign(pt, v3, v1) < 0.0f;

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

//Array2D<unsigned int> Dag::getTriangles(){}

void Dag::updateDag(const Point2Dd& p){
   /*
          branches.push_back( Branch(0,));
    }
    */
}
