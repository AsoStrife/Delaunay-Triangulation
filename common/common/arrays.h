#ifndef COMMON_MODULE_ARRAYS_H
#define COMMON_MODULE_ARRAYS_H

#include <vector>
#include <assert.h>
#include <iomanip>
#include "serialize.h"

template <class T> class Array2D : public SerializableObject{

    public:
        Array2D();
        Array2D(unsigned long int sizeX, unsigned long int sizeY);
        Array2D(unsigned long int sizeX, unsigned long int sizeY, const T& value);
        T& operator () (unsigned long int i, unsigned long int j);
        T operator () (unsigned long int i, unsigned long int j) const;
        const T* operator () (unsigned long int i) const;

        unsigned long int getSizeX() const;
        unsigned long int getSizeY() const;

        T& getMin();
        const T& getMin() const;
        T& getMax();
        const T& getMax() const;

        void setConstant(const T& c);

        void resize (unsigned long int x, unsigned long int y);
        void resize (unsigned long int x, unsigned long int y, const T& value);

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        bool deserialize(std::ifstream& binaryFile);

    private:
        unsigned long int getIndex(unsigned long int i, unsigned long int j) const;

        unsigned long int sizeX, sizeY;
        std::vector<T> v;
};

template <class T>
std::ostream& operator<< (std::ostream& inputStream, const Array2D<T>& a);

template <class T> class Array3D : public SerializableObject{

    public:
        Array3D();
        Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ);
        Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, const T& value);
        T& operator () (unsigned long int i, unsigned long int j, unsigned long int k);
        T operator () (unsigned long int i, unsigned long int j, unsigned long int k) const;
        const T* operator () (unsigned long int i, unsigned long int j) const;

        unsigned long int getSizeX() const;
        unsigned long int getSizeY() const;
        unsigned long int getSizeZ() const;

        T& getMin();
        const T& getMin() const;
        T& getMax();
        const T& getMax() const;

        void setConstant(const T& c);

        void resize (unsigned long int x, unsigned long int y, unsigned long int z);
        void resize (unsigned long int x, unsigned long int y, unsigned long int z, const T& value);

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        bool deserialize(std::ifstream& binaryFile);

    private:
        unsigned long int getIndex(unsigned long int i, unsigned long int j, unsigned long int k) const;

        unsigned long int sizeX, sizeY, sizeZ;
        std::vector<T> v;
};

template <class T> class Array4D : public SerializableObject{

    public:
        Array4D();
        Array4D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, unsigned long int sizeW);
        Array4D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, unsigned long int sizeW, const T& value);
        T& operator () (unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l);
        T operator () (unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l) const;
        const T* operator () (unsigned long int i, unsigned long int j, unsigned long int k) const;

        unsigned long int getSizeX() const;
        unsigned long int getSizeY() const;
        unsigned long int getSizeZ() const;
        unsigned long int getSizeW() const;

        T& getMin();
        const T& getMin() const;
        T& getMax();
        const T& getMax() const;

        void setConstant(const T& c);

        void resize (unsigned long int x, unsigned long int y, unsigned long int z, unsigned long int w);
        void resize (unsigned long int x, unsigned long int y, unsigned long int z, unsigned long int w, const T& value);

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        bool deserialize(std::ifstream& binaryFile);

    private:
        unsigned long int getIndex(unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l);

        unsigned long int sizeX, sizeY, sizeZ, sizeW;
        std::vector<T> v;
};

#include "arrays.cpp"

#endif // COMMON_MODULE_ARRAYS_H
