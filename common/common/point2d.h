#ifndef COMMON_MODULE_POINT2D_H
#define COMMON_MODULE_POINT2D_H

#include <sstream>
#include <assert.h>
#include <QDebug>
#include <string>
#include <iostream>

#include "serialize.h"

/**
 * \~Engish
 * @class Point2D
 * @brief The Point2D class models a point or a vector in a 2D plane.
 *
 * It representes a 2D point or vector, with the precision given by the template type T.
 * Specified types with T = int, float or double are already defined as Point2Di,
 * Point2Df and Point2Dd (Vec2).
 *
 * @author Alessandro Muntoni
 */
template <class T> class Point2D : SerializableObject {
    public:
        Point2D(T x = 0.0, T y = 0.0);
        #ifdef COMMON_WITH_EIGEN
        Point2D(const Eigen::VectorXd &v);
        #endif

        /***
         * Const Member Functions
         **/
        const T& x() const;
        const T& y() const;
        double dist(const Point2D<T> &otherPoint) const;
        double dot(const Point2D<T> &otherVector) const;
        double perpendicularDot(const Point2D<T> &otherVector) const;
        double getLength() const;
        double getLengthSquared() const;
        Point2D<T> min(const Point2D<T> &otherPoint) const;
        Point2D<T> max(const Point2D<T> &otherPoint) const;

        const T& operator[](unsigned int i)                 const;
        const T& operator()(unsigned int i)                 const;
        bool operator == (const Point2D<T> &otherPoint)   const;
        bool operator != (const Point2D<T> &otherPoint)   const;
        bool operator < (const Point2D<T>& otherPoint)    const;
        bool operator > (const Point2D<T>& otherPoint)    const;
        bool operator <= (const Point2D<T>& otherPoint)   const;
        bool operator >= (const Point2D<T>& otherPoint)   const;
        Point2D<T> operator - ()                          const;
        Point2D<T> operator + (const T& scalar) const;
        Point2D<T> operator + (const Point2D<T>& otherPoint) const;
        Point2D<T> operator - (const Point2D<T>& otherPoint) const;
        Point2D<T> operator * (const T& scalar)      const;
        Point2D<T> operator * (const Point2D<T>& otherPoint) const;
        Point2D<T> operator / (const T& scalar )     const;
        Point2D<T> operator / (const Point2D<T>& otherPoint) const;

        T& x();
        T& y();
        void setXCoord(const T& x);
        void setYCoord(const T& y);
        void set(const T& x, const T& y);
        double normalize();
        void rotate(T matrix[][2], const Point2D<T>& centroid = Point2D<T>());
        Point2D<T> operator += (const Point2D<T>& otherPoint);
        Point2D<T> operator -= (const Point2D<T>& otherPoint);
        Point2D<T> operator *= (const T& scalar);
        Point2D<T> operator *= (const Point2D<T>& otherPoint);
        Point2D<T> operator /= (const T& scalar );
        Point2D<T> operator /= (const Point2D<T>& otherPoint);

    private:
        T xCoord, yCoord;
        void rot(T matrix[][2]);

        // SerializableObject interface
    public:
        void serialize(std::ofstream& binaryFile) const;
        bool deserialize(std::ifstream& binaryFile);
};

/****************
* Other Methods *
*****************/

template <class T>
Point2D<T> operator * (const T& scalar, const Point2D<T>& point);

template <class T>
Point2D<T> normalOfSegment(const Point2D<T>& p1, const Point2D<T>& p2);

/******************
* Type definition *
******************/

typedef Point2D<double> Point2Dd;
typedef Point2D<float> Point2Df;
typedef Point2D<int> Point2Di;
typedef Point2D<double> Vec2;

#include "point2d.cpp"

#endif // COMMON_MODULE_POINT2D_H
