#include <Andrea/Headers/Drawable/drawabledelaunaytriangulation.h>
#include <Andrea/Headers/Drawable/drawablepoint.h>
#include <viewer/objects/objects.h>

DrawableDelaunayTriangulation::DrawableDelaunayTriangulation(){}

// DrawableObject interface
void DrawableDelaunayTriangulation::draw() const{

    //std::vector<DrawablePoint> points;
    //std::vector<DrawableLine> lines;

    for (int i = 0; i < points.size(); i++){

        points[i].draw();
    }


}

Pointd DrawableDelaunayTriangulation::sceneCenter() const {}
double DrawableDelaunayTriangulation::sceneRadius() const {}

void DrawableDelaunayTriangulation::addDrawablePoint(const Point2Dd& p){
    this->dag.addPoint2Dd(p);

    this->points.push_back( DrawablePoint(p) );
    dag.addTrianglesIntoDag(p);
}

void DrawableDelaunayTriangulation::addDrawableLine(Point2Dd p1, Point2Dd p2){
    lines.push_back( DrawableLine(p1, p2));
}

bool DrawableDelaunayTriangulation::checkIfPointAlreadyExist(const Point2Dd& p){
    if (std::find(points.begin(), points.end(), DrawablePoint(p)) != points.end())
        return true;
    else
        return false;
}

void DrawableDelaunayTriangulation::cleanDelaunayTriangulation(){
    //p.clear();
    //t.clear();
    points.clear();
    lines.clear();
}

void DrawableDelaunayTriangulation::loadPointFromVector(const std::vector<Point2Dd>& p){
    int size = p.size();

    if(size > 0){
        for (int i = 0; i < size; i++){

            if(!checkIfPointAlreadyExist(p[i])){
                addDrawablePoint(p[i]);
            }
        }
    }
}

void DrawableDelaunayTriangulation::setBoundingTrianglePoints(const Point2Dd& p1, const Point2Dd& p2, const Point2Dd& p3){
    this->BT_P1 = p1;
    this->BT_P2 = p2;
    this->BT_P3 = p3;

    this->dag.addRoot(p1, p2, p3);
}
