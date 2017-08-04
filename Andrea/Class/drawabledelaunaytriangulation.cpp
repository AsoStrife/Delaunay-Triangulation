#include <Andrea/Headers/drawabledelaunaytriangulation.h>
#include <viewer/objects/objects.h>
#include <Andrea/Headers/drawablepoint.h>

DrawableDelaunayTriangulation::DrawableDelaunayTriangulation(){}

// DrawableObject interface
void DrawableDelaunayTriangulation::draw() const{

    //std::vector<DrawablePoint> points;
    //std::vector<DrawableLine> lines;
    int size = points.size();

    if(size > 0){
        for (int i = 0; i < size; i++){

            points[i].draw();
        }

        if(size == 3){
            lines[0].draw();
            lines[1].draw();
            lines[2].draw();
        }
    }
}


Pointd DrawableDelaunayTriangulation::sceneCenter() const {}

double DrawableDelaunayTriangulation::sceneRadius() const {}

void DrawableDelaunayTriangulation::addDrawablePoint(const Point2Dd& p){
    int size = points.size();
    if(size < 2)
        points.push_back( DrawablePoint(p) );
    else{
        points.push_back( DrawablePoint(p) );
        addDrawableLine(points[0].getPoint2Dd(), points[1].getPoint2Dd());
        addDrawableLine(points[0].getPoint2Dd(), points[2].getPoint2Dd());
        addDrawableLine(points[1].getPoint2Dd(), points[2].getPoint2Dd());
    }
}

void DrawableDelaunayTriangulation::addDrawableLine(Point2Dd p1, Point2Dd p2){
    lines.push_back( DrawableLine(p1, p2));
}

bool DrawableDelaunayTriangulation::checkIfPointAlreadyExist(const Point2Dd& p){
    if (std::find(points.begin(), points.end(), DrawablePoint(p)) != points.end())
        return true;
    else return false;
}

void DrawableDelaunayTriangulation::cleanDelaunayTriangulation(){
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
