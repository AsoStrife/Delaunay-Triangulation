#include "drawabledebugobjects.h"
#include "../objects/objects.h"

DrawableDebugObjects::DrawableDebugObjects() : visible(true) {

}

DrawableDebugObjects::~DrawableDebugObjects(){
}

void DrawableDebugObjects::draw() const {
    if (visible){
        for (unsigned int i = 0; i < debugSpheres.size(); i++){
            Viewer::drawSphere(debugSpheres[i].center, debugSpheres[i].radius, debugSpheres[i].color, debugSpheres[i].precision);
        }
        for (unsigned int i = 0; i < debugCylinders.size(); i++){
            Viewer::drawCylinder(debugCylinders[i].a, debugCylinders[i].b, debugCylinders[i].radius, debugCylinders[i].radius, debugCylinders[i].color);
        }
    }
}

    Pointd DrawableDebugObjects::sceneCenter() const {
        return 0;
    }

    double DrawableDebugObjects::sceneRadius() const {
        return -1;
    }

bool DrawableDebugObjects::isVisible() const {
    return visible;
}

void DrawableDebugObjects::setVisible(bool b) {
    visible = b;
}

void DrawableDebugObjects::addDebugSphere(const Pointd& center, double radius, const QColor& color, int precision) {
    Sphere s = {center, radius, color, precision};
    debugSpheres.push_back(s);
}

void DrawableDebugObjects::clearDebugSpheres() {
    debugSpheres.clear();
}

void DrawableDebugObjects::addDebugCylinder(const Pointd& a, const Pointd& b, double radius, const QColor color) {
    Cylinder c = {a, b, radius, color};
    debugCylinders.push_back(c);
}

void DrawableDebugObjects::clearDebugCylinders() {
    debugCylinders.clear();
}
