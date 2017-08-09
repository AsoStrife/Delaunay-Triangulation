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

//Array2D<unsigned int> Dag::getTriangles(){}

void Dag::addTrianglesIntoDag(const Point2Dd& p){

    bool hasChild = true;
    int posT = 0;

    while(hasChild){
        Triangle &triangle = nodes[posT];

        if(PointInTriangle(p, triangle)){
            std::cout << "Il punto è dentro il triangolo " << std::endl;

            //if(DelaunayTriangulation::Checker::isPointLyingInCircle(triangle.getA(), triangle.getB(), triangle.getC(), p, true) == true)
                //std::cout << "Il punto è cade dentro il cerchio " << std::endl;

            // Aggiungo i tre triangoli appena creati congiungendoli alla root
            Triangle A = Triangle(p, triangle.getA(), triangle.getB());
            Triangle B = Triangle(p, triangle.getA(), triangle.getC());
            Triangle C = Triangle(p, triangle.getC(), triangle.getB());

            triangle.setChildA(&A);
            triangle.setChildB(&B);
            triangle.setChildC(&C);

            nodes.push_back(A);
            nodes.push_back(B);
            nodes.push_back(C);

            hasChild = false;
        }

    }
}
