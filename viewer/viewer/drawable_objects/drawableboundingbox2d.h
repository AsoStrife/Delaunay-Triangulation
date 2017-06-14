#ifndef DRAWABLEBOUNDINGBOX2D_H
#define DRAWABLEBOUNDINGBOX2D_H

#include <common/bounding_box2d.h>
#include <common/color.h>
#include "../interfaces/drawable_object.h"

class DrawableBoundingBox2D : public BoundingBox2D, public DrawableObject
{
    public:
        DrawableBoundingBox2D(double thirdCoord = 0);
        DrawableBoundingBox2D(const BoundingBox2D& b, double thirdCoord = 0);
        DrawableBoundingBox2D(const Point2Dd& min, const Point2Dd& max, double thirdCoord = 0);


        // DrawableObject interface
        void draw() const;
        Pointd sceneCenter() const;
        double sceneRadius() const;

    private:

        void drawEdges() const;
        void drawPoints() const;

        int pointSize;
        Color colorPoint;
        int edgeWidth;
        Color colorEdge;

        double thirdCoord;
};

#endif // DRAWABLEBOUNDINGBOX2D_H
