#include <Andrea/Headers/pointtest.h>
#include <viewer/interfaces/drawable_object.h>
#include <viewer/objects/objects.h>
#include <iostream>

/*pointtest::pointtest(Point2Dd& point){
    p = point;
}*/

pointtest::pointtest(double x, double y){
    this->x = x;
    this->y = y;
}

// DrawableObject interface
void pointtest::draw() const{

    std::cout << "Clicket point: " << std::endl;
    std::cout <<  x  << std::endl;
    std::cout << " " << std::endl;
    std::cout <<  y << std::endl;
    Point2Dd p(x, y);
    Viewer::drawPoint2D(p, QColor(0, 0 ,0), 8);
}


Pointd pointtest::sceneCenter() const {

}

double pointtest::sceneRadius() const {

}



void pointtest::setx(double value){
    this->x = value;
}

void pointtest::sety(double value){
    this->y = value;
}

double pointtest::getx(){
    return this->x;
}

double pointtest::gety(){
    return this->y;
}



