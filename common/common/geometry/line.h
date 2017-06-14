#ifndef LINE_H
#define LINE_H

#include <common/point.h>

class Line {
    public:
        Line();
        Line(const Pointd& p0, const Vec3& dir);
        const Vec3& getDir() const;
        const Pointd& getStartingPoint() const;

        bool pointBelonging(const Pointd &p) const;

    protected:
        Pointd p0;
        Vec3 dir;

};

#endif // LINE_H
