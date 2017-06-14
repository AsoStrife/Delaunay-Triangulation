#ifndef PLANE_H
#define PLANE_H

#include <common/point.h>
#include "line.h"
class Plane {
    public:
        Plane(const Vec3& normal, double d);
        Plane(double a, double b, double c, double d);
        Plane(const Pointd &p1, const Pointd &p2, const Pointd &p3);
        ~Plane();


        double getA() const;
        double getB() const;
        double getC() const;
        double getD() const;


        bool pointBelonging(const Pointd& p) const;
        #ifdef COMMON_WITH_EIGEN
        bool getIntersection(Pointd&intersection, const Line &l) const;
        #endif

    protected:
        Vec3 normal;
        double d;

};

#endif // PLANE_H
