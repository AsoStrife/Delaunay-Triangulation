#include "Andrea/Headers/Drawable/drawablevoronoidiagram.h"

DrawableVoronoiDiagram::DrawableVoronoiDiagram(){}

/**
 * @brief getCircumcircle
 * @param t
 * @link http://www.delphitricks.com/source-code/math/determine_the_circumcenter_of_a_2d_triangle.html
 */
Point2Dd DrawableVoronoiDiagram::getCircumcircle(const Triangle& t){
    Point2Dd a = *t.getA();
    Point2Dd b = *t.getB();
    Point2Dd c = *t.getC();

    double A = b.x() - a.x();
    double B = b.y() - a.y();
    double C = c.x() - a.x();
    double D = c.y() - a.y();
    double E = A * (a.x() + b.x()) + B * (a.y() + c.y());
    double F = C * (a.x() + b.x()) + D * (a.y() + c.y());
    double G = 2.0 * (A * (c.y() - b.y()) - B * (c.x() - b.x()));

    if(G == 0)
        return Point2Dd();

    double Px = (D * E - B * F) / G;
    double Py = (A * F - C * E) / G;

    return Point2Dd(Px, Py);
}


/*
if(getVoronoiActive() == true){
    Point2Dd p = DrawableVoronoiDiagram::getCircumcircle(*triangles.at(i));
    std::cout << "Punto inserito voronoi: " << p.x() << " - " << p.y() << std::endl;
    Viewer::drawPoint2D( p, this->voronoiPointColor, this->pointSize);
}*/
