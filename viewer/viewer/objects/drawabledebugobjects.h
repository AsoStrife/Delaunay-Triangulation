#ifndef VIEWER_DRAWABLE_DEBUG_OBJECTS_H
#define VIEWER_DRAWABLE_DEBUG_OBJECTS_H

#include "../interfaces/drawable_object.h"
#include <common/bounding_box.h>


class DrawableDebugObjects : public DrawableObject{
    public:
        DrawableDebugObjects();
        virtual ~DrawableDebugObjects();

        // DrawableObject interface
        void draw() const;
        Pointd sceneCenter() const;
        double sceneRadius() const;
        bool isVisible() const;
        void setVisible(bool b);

        void addDebugSphere(const Pointd& center, double radius, const QColor &color, int precision = 4);
        void clearDebugSpheres();
        void addDebugCylinder(const Pointd& a, const Pointd& b, double radius, const QColor color);
        void clearDebugCylinders();

    protected:
        typedef struct {
                Pointd center;
                double radius;
                QColor color;
                int precision;
        } Sphere;
        typedef struct {
                Pointd a;
                Pointd b;
                double radius;
                QColor color;
        } Cylinder;
        std::vector<Sphere> debugSpheres;
        std::vector<Cylinder> debugCylinders;

        bool visible;
};

#endif // VIEWER_DRAWABLE_DEBUG_OBJECTS_H
