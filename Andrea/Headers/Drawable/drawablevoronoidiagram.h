#ifndef DRAWABLEVORONOIDIAGRAM_H
#define DRAWABLEVORONOIDIAGRAM_H
#include <viewer/objects/objects.h>
#include <Andrea/Headers/triangle.h>
#include <math.h>

class DrawableVoronoiDiagram{
public:
    DrawableVoronoiDiagram();

    static Point2Dd getCircumcircle(const Triangle& t);
};

#endif // DRAWABLEVORONOIDIAGRAM_H
