#include <Andrea/Headers/drawabledelaunaytriangulation.h>
#include <viewer/objects/objects.h>
#include <Andrea/Headers/drawablepoint.h>

DrawableDelaunayTriangulation::DrawableDelaunayTriangulation(){}

void DrawableDelaunayTriangulation::addDrawablePoint(Point2Dd p){
    points.push_back( DrawablePoint(p) );
}

// DrawableObject interface
void DrawableDelaunayTriangulation::draw() const{

   //<DrawablePoint> points
   int size = points.size();

   if(size > 0){
        for (int i = 0; i < size; i++){

            points[i].draw();
        }
    }
}


Pointd DrawableDelaunayTriangulation::sceneCenter() const {}

double DrawableDelaunayTriangulation::sceneRadius() const {}

bool DrawableDelaunayTriangulation::checkIfPointAlreadyExist(Point2Dd p){
    if (std::find(points.begin(), points.end(), DrawablePoint(p)) != points.end())
        return true;
    else return false;
}
