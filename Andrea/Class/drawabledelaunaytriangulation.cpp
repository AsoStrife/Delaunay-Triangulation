#include "Andrea/Headers/drawabledelaunaytriangulation.h"
#include <Andrea/Headers/drawablepoint.h>

DrawableDelaunayTriangulation::DrawableDelaunayTriangulation(){
    std::cout << "Inizializzo oggetto drawabledelaunay triangulation" << std::endl;
}

void DrawableDelaunayTriangulation::addDrawablePoint(Point2Dd p){
    points.push_back( DrawablePoint(p) );
}

// DrawableObject interface
void DrawableDelaunayTriangulation::draw() const{

    //<DrawablePoint> points
   int size = points.size();
   std::cout << size << std::endl;

   if(size > 0){
        for (int i = 0; i < size; i++){
            //std::cout << points.size() << '\n';
            points[i].draw();
        }
    }
}


Pointd DrawableDelaunayTriangulation::sceneCenter() const {}

double DrawableDelaunayTriangulation::sceneRadius() const {}
