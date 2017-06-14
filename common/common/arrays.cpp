#include "arrays.h"

///
/// Array2D
///

/**
 * @brief Array2D<T>::Array2D
 * Initializes a 2D array with 0 rows and 0 columns
 */
template <class T>
inline Array2D<T>::Array2D() : sizeX(0), sizeY(0) {
    v.resize(0);
}

/**
 * @brief Array2D<T>::Array2D
 * Initializes a 2D array with sizeX rows and sizeY columns
 * All the velues of the array will be initialized to 0
 *
 * @param sizeX
 * @param sizeY
 */
template <class T>
inline Array2D<T>::Array2D(unsigned long int sizeX, unsigned long int sizeY) : sizeX(sizeX), sizeY(sizeY) {
    v.resize(sizeX*sizeY);
}

/**
 * @brief Array2D<T>::Array2D
 * Initializzes a 2D array with sizeX rows and sizeY columns.
 * All the values of the array will be initialized to the value passed as a parameter
 *
 * @param sizeX
 * @param sizeY
 * @param value
 */
template <class T>
inline Array2D<T>::Array2D(unsigned long int sizeX, unsigned long int sizeY, const T& value) : sizeX(sizeX), sizeY(sizeY) {
    v.resize(sizeX*sizeY, value);
}

/**
 * @brief Array2D<T>::operator ()
 * Access to the i,j element of the array
 *
 * @param i: row of the desired element
 * @param j: column of the desired element
 * @return a reference of the element in position i,j
 */
template <class T>
inline T& Array2D<T>::operator ()(unsigned long int i, unsigned long int j) {
    return v[getIndex(i,j)];
}

template <class T>
inline T Array2D<T>::operator ()(unsigned long int i, unsigned long int j) const {
    return v[getIndex(i,j)];
}

template <class T>
inline const T* Array2D<T>::operator ()(unsigned long int i) const{
    assert (i < sizeX);
    return &(v[sizeY*i]);
}

template <class T>
inline unsigned long int Array2D<T>::getSizeX() const {
    return sizeX;
}

template <class T>
inline unsigned long int Array2D<T>::getSizeY() const{
    return sizeY;
}

template <class T>
inline T&Array2D<T>::getMin() {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
const T&Array2D<T>::getMin() const {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
inline T&Array2D<T>::getMax() {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
const T&Array2D<T>::getMax() const {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
inline void Array2D<T>::setConstant(const T& c) {
    std::fill(v.begin(), v.end(), c);
}

template <class T>
inline void Array2D<T>::resize(unsigned long int x, unsigned long int y) {
    v.resize(x*y);
    sizeX = x;
    sizeY = y;
}

template <class T>
inline void Array2D<T>::resize(unsigned long int x, unsigned long int y, const T& value) {
    v.resize(x*y, value);
    sizeX = x;
    sizeY = y;
}

template <class T>
inline void Array2D<T>::serialize(std::ofstream& binaryFile) const {
    Serializer::serialize(sizeX, binaryFile);
    Serializer::serialize(sizeY, binaryFile);
    for (unsigned int i = 0; i < v.size(); ++i)
        Serializer::serialize(v[i], binaryFile);
}

template <class T>
inline bool Array2D<T>::deserialize(std::ifstream& binaryFile) {
    Array2D<T> tmp;
    if (Serializer::deserialize(tmp.sizeX, binaryFile) &&
            Serializer::deserialize(tmp.sizeY, binaryFile)) {
        tmp.v.resize(tmp.sizeX*tmp.sizeY);
        for (unsigned int i = 0; i < tmp.v.size(); ++i){
            if (! Serializer::deserialize(tmp.v[i], binaryFile))
                return false;
        }
        *this = std::move(tmp);
        return true;
    }
    else
        return false;
}

template <class T>
inline unsigned long int Array2D<T>::getIndex(unsigned long int i, unsigned long int j) const {
    assert (i < sizeX);
    assert (j < sizeY);
    return j + sizeY*i;
}

template <class T>
std::ostream& operator<< (std::ostream& inputStream, const Array2D<T>& a) {
    for (unsigned int i = 0; i < a.getSizeX(); i++){
        for (unsigned int j = 0; j < a.getSizeY(); j++){
            inputStream << std::setw(4) <<a(i,j) << " ";
        }
        inputStream << "\n";
    }
    return inputStream;
}

///
/// Array3D
///

template <class T>
inline Array3D<T>::Array3D() : sizeX(0), sizeY(0), sizeZ(0) {
    v.resize(0);
}

template <class T>
inline Array3D<T>::Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ) : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {
    v.resize(sizeX*sizeY*sizeZ);
}

template <class T>
inline Array3D<T>::Array3D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, const T& value) : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {
    v.resize(sizeX*sizeY*sizeZ, value);
}

template <class T>
inline T& Array3D<T>::operator ()(unsigned long int i, unsigned long int j, unsigned long int k) {
    return v[getIndex(i,j,k)];
}

template <class T>
inline T Array3D<T>::operator ()(unsigned long int i, unsigned long int j, unsigned long int k) const {
    return v[getIndex(i,j,k)];
}

template <class T>
inline const T* Array3D<T>::operator ()(unsigned long int i, unsigned long int j) const{
    assert (i < sizeX);
    assert (j < sizeY);
    return &(v[sizeZ*(j + sizeY*i)]);
}

template <class T>
inline unsigned long int Array3D<T>::getSizeX() const {
    return sizeX;
}

template <class T>
inline unsigned long int Array3D<T>::getSizeY() const{
    return sizeY;
}

template <class T>
inline unsigned long int Array3D<T>::getSizeZ() const {
    return sizeZ;
}

template <class T>
inline T&Array3D<T>::getMin() {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
const T&Array3D<T>::getMin() const {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
inline T&Array3D<T>::getMax() {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
const T&Array3D<T>::getMax() const {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
inline void Array3D<T>::setConstant(const T& c) {
    std::fill(v.begin(), v.end(), c);
}

template <class T>
inline void Array3D<T>::resize(unsigned long int x, unsigned long int y, unsigned long int z) {
    v.resize(x*y*z);
    sizeX = x;
    sizeY = y;
    sizeZ = z;
}

template <class T>
inline void Array3D<T>::resize(unsigned long int x, unsigned long int y, unsigned long int z, const T& value) {
    v.resize(x*y*z, value);
    sizeX = x;
    sizeY = y;
    sizeZ = z;
}

template <class T>
inline void Array3D<T>::serialize(std::ofstream& binaryFile) const {
    Serializer::serialize(sizeX, binaryFile);
    Serializer::serialize(sizeY, binaryFile);
    Serializer::serialize(sizeZ, binaryFile);
    for (unsigned int i = 0; i < v.size(); ++i)
        Serializer::serialize(v[i], binaryFile);
}

template <class T>
inline bool Array3D<T>::deserialize(std::ifstream& binaryFile) {
    Array3D<T> tmp;
    if (Serializer::deserialize(tmp.sizeX, binaryFile) &&
            Serializer::deserialize(tmp.sizeY, binaryFile) &&
            Serializer::deserialize(tmp.sizeZ, binaryFile)) {
        tmp.v.resize(tmp.sizeX*tmp.sizeY*tmp.sizeZ);
        for (unsigned int i = 0; i < tmp.v.size(); ++i){
            if (! Serializer::deserialize(tmp.v[i], binaryFile))
                return false;
        }
        *this = std::move(tmp);
        return true;
    }
    else
        return false;
}

template <class T>
inline unsigned long int Array3D<T>::getIndex(unsigned long int i, unsigned long int j, unsigned long int k) const {
    assert (i < sizeX);
    assert (j < sizeY);
    assert (k < sizeZ);
    return k+sizeZ*(j + sizeY*i);
}

///
/// Array4D
///

template <class T>
inline Array4D<T>::Array4D() : sizeX(0), sizeY(0), sizeZ(0), sizeW(0) {
    v.resize(0);
}

template <class T>
inline Array4D<T>::Array4D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, unsigned long int sizeW) : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ), sizeW(sizeW) {
    v.resize(sizeX*sizeY*sizeZ*sizeW);
}

template <class T>
inline Array4D<T>::Array4D(unsigned long int sizeX, unsigned long int sizeY, unsigned long int sizeZ, unsigned long int sizeW, const T& value) : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ), sizeW(sizeW) {
    v.resize(sizeX*sizeY*sizeZ*sizeW, value);
}

template <class T>
inline T& Array4D<T>::operator ()(unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l) {
    return v[getIndex(i,j,k,l)];
}

template <class T>
inline T Array4D<T>::operator ()(unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l) const {
    return v[getIndex(i,j,k,l)];
}

template <class T>
inline const T* Array4D<T>::operator ()(unsigned long int i, unsigned long int j, unsigned long int k) const {
    assert (i < sizeX);
    assert (j < sizeY);
    assert (k < sizeZ);
    return &(v[sizeW*(k + sizeZ*(j + sizeY*i))]);
}

template <class T>
inline unsigned long int Array4D<T>::getSizeX() const {
    return sizeX;
}

template <class T>
inline unsigned long int Array4D<T>::getSizeY() const{
    return sizeY;
}

template <class T>
inline unsigned long int Array4D<T>::getSizeZ() const {
    return sizeZ;
}

template <class T>
inline unsigned long int Array4D<T>::getSizeW() const {
    return sizeW;
}

template <class T>
inline T&Array4D<T>::getMin() {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
const T&Array4D<T>::getMin() const {
    return *(std::min_element(v.begin(), v.end()));
}

template <class T>
inline T&Array4D<T>::getMax() {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
const T&Array4D<T>::getMax() const {
    return *(std::max_element(v.begin(), v.end()));
}

template <class T>
inline void Array4D<T>::setConstant(const T& c) {
    std::fill(v.begin(), v.end(), c);
}

template <class T>
inline void Array4D<T>::resize(unsigned long int x, unsigned long int y, unsigned long int z, unsigned long int w) {
    v.resize(x*y*z*w);
    sizeX = x;
    sizeY = y;
    sizeZ = z;
    sizeW = w;
}

template <class T>
inline void Array4D<T>::resize(unsigned long int x, unsigned long int y, unsigned long int z, unsigned long int w, const T& value) {
    v.resize(x*y*z*w, value);
    sizeX = x;
    sizeY = y;
    sizeZ = z;
    sizeW = w;
}

template <class T>
inline void Array4D<T>::serialize(std::ofstream& binaryFile) const {
    Serializer::serialize(sizeX, binaryFile);
    Serializer::serialize(sizeY, binaryFile);
    Serializer::serialize(sizeZ, binaryFile);
    Serializer::serialize(sizeW, binaryFile);
    for (unsigned int i = 0; i < v.size(); ++i)
        Serializer::serialize(v[i], binaryFile);
}

template <class T>
inline bool Array4D<T>::deserialize(std::ifstream& binaryFile) {
    Array4D<T> tmp;
    if (Serializer::deserialize(tmp.sizeX, binaryFile) &&
            Serializer::deserialize(tmp.sizeY, binaryFile) &&
            Serializer::deserialize(tmp.sizeZ, binaryFile) &&
            Serializer::deserialize(tmp.sizeW, binaryFile)) {
        tmp.v.resize(tmp.sizeX*tmp.sizeY*tmp.sizeZ*tmp.sizeW);
        for (unsigned int i = 0; i < tmp.v.size(); ++i){
            if (! Serializer::deserialize(tmp.v[i], binaryFile))
                return false;
        }
        *this = std::move(tmp);
        return true;
    }
    else
        return false;
}

template <class T>
inline unsigned long int Array4D<T>::getIndex(unsigned long int i, unsigned long int j, unsigned long int k, unsigned long int l) {
    assert (i < sizeX);
    assert (j < sizeY);
    assert (k < sizeZ);
    assert (l < sizeW);
    return l + sizeW*(k + sizeZ*(j + sizeY*i));
}
