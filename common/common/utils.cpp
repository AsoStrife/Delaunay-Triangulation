#include "utils.h"

/**
 * \~English
 * @brief This function computes a binary search of an element on a sorted std::vector
 * @param[in] n: the object that we are searching on the vector
 * @param[in] v: a sorted std::vector
 * @return the position index of the object if it is found, -1 otherwise
 *
 * \~Italian
 * @brief Questa funzione esegue una ricerca binaria di un elemento su un std::vector ordinato
 * @param[in] n: l'oggetto che si deve cercare all'interno del vector
 * @param[in] v: un std::vector ordinato
 * @return l'indice di posizione dell'oggetto se è stato trovato, -1 altrimenti
 */
template <typename T>
int Common::binarySearch(const T &n, const std::vector<T> &v) {
    int first = 0, last =v.size()-1, mid;
    while (first <= last){
        mid = (first + last) / 2;
        if (v[mid] < n) first = mid + 1;
        else if (v[mid] == n) return mid;
        else last = mid - 1;
    }
    return -1;
}

/**
     * \~English
     * @brief This function computes an equality between two parameters considering an epsilon offset
     * @param[in] x: first parameter
     * @param[in] v: second parameter
     * @param[in] epsilon: offset for equality, default value 0.0000001
     * @return true if the two parameters are equals on the epsilon interval, false otherwise
     *
     * \~Italian
     * @brief Questa funzione calcola l'uguaglianza tra due parametri tenendo conto di un possibile offset pari a epsilon
     * @param[in] x: primo parametro
     * @param[in] v: secondo parametro
     * @param[in] epsilon: offset di uguaglianza, valore di default 0.0000001
     * @return true se i due parametri sono uguali a meno del valore di epsilon, falso altrimenti
     */
template <typename T>
inline bool Common::epsilonEqual(T x, T v, double epsilon) {
    if (std::abs(x-v) < epsilon) return true;
    return false;
}

/**
 * \~English
 * @brief This function computes an equality between two Points considering an epsilon offset
 * @param[in] x: first Point parameter
 * @param[in] v: second Point parameter
 * @param[in] epsilon: offset for equality, default value 0.0000001
 * @return true if the two Points are equals on the epsilon interval, false otherwise
 *
 * \~Italian
 * @brief Questa funzione calcola l'uguaglianza tra due Point tenendo conto di un possibile offset pari a epsilon
 * @param[in] x: primo parametro Point
 * @param[in] v: secondo parametro Point
 * @param[in] epsilon: offset di uguaglianza, valore di default 0.0000001
 * @return true se i due Point sono uguali a meno del valore di epsilon, falso altrimenti
 */
template <typename T>
inline bool Common::epsilonEqual(const Point<T> &x, const Point<T> &v, double epsilon) {
    if ((epsilonEqual(x.x(), v.x(), epsilon)) && (epsilonEqual(x.y(), v.y(), epsilon)) && (epsilonEqual(x.z(), v.z(), epsilon))) return true;
    else return false;
}

/**
 * \~English
 * @brief this function computes a rotation matrix given the axis of the rotation and the angle
 * @param[in] axis
 * @param[in] angle
 * @param[out] m
 */
inline void Common::getRotationMatrix(Vec3 axis, double angle, Eigen::Matrix3d &m) {
    axis.normalize();
    double cosa = cos(angle);
    double sina = sin(angle);
    m(0,0) = cosa + (axis.x() * axis.x())*(1-cosa);
    m(0,1) = axis.x() * axis.y() * (1-cosa) - axis.z() * sina;
    m(0,2) = axis.x() * axis.z() * (1-cosa) + axis.y() * sina;
    m(1,0) = axis.y() * axis.x() * (1-cosa) + axis.z() * sina;
    m(1,1) = cosa + (axis.y() * axis.y())*(1-cosa);
    m(1,2) = axis.y() * axis.z() * (1-cosa) - axis.x() * sina;
    m(2,0) = axis.z() * axis.x() * (1-cosa) - axis.y() * sina;
    m(2,1) = axis.z() * axis.y() * (1-cosa) + axis.x() * sina;
    m(2,2) = cosa + (axis.z() * axis.z())*(1-cosa);
}

/**
 * \~English
 * @brief this function computes a rotation matrix given the axis of the rotation and the angle
 * @param[in] axis
 * @param[out] angle
 * @return the rotation matrix
 */
inline Eigen::Matrix3d Common::getRotationMatrix(Vec3 axis, double angle) {
    Eigen::Matrix3d m;
    axis.normalize();
    double cosa = cos(angle);
    double sina = sin(angle);
    m(0,0) = cosa + (axis.x() * axis.x())*(1-cosa);
    m(0,1) = axis.x() * axis.y() * (1-cosa) - axis.z() * sina;
    m(0,2) = axis.x() * axis.z() * (1-cosa) + axis.y() * sina;
    m(1,0) = axis.y() * axis.x() * (1-cosa) + axis.z() * sina;
    m(1,1) = cosa + (axis.y() * axis.y())*(1-cosa);
    m(1,2) = axis.y() * axis.z() * (1-cosa) - axis.x() * sina;
    m(2,0) = axis.z() * axis.x() * (1-cosa) - axis.y() * sina;
    m(2,1) = axis.z() * axis.y() * (1-cosa) + axis.x() * sina;
    m(2,2) = cosa + (axis.z() * axis.z())*(1-cosa);
    return m;
}

/**
 * \~English
 * @brief this function computes a rotation matrix given the axis of the rotation and the angle
 * @param[in] axis
 * @param[in] angle
 * @param[out] m
 */
inline void Common::getRotationMatrix(Vec3 axis, double angle, double m[][3]) {
    axis.normalize();
    double cosa = cos(angle);
    double sina = sin(angle);
    m[0][0] = cosa + (axis.x() * axis.x())*(1-cosa);
    m[0][1] = axis.x() * axis.y() * (1-cosa) - axis.z() * sina;
    m[0][2] = axis.x() * axis.z() * (1-cosa) + axis.y() * sina;
    m[1][0] = axis.y() * axis.x() * (1-cosa) + axis.z() * sina;
    m[1][1] = cosa + (axis.y() * axis.y())*(1-cosa);
    m[1][2] = axis.y() * axis.z() * (1-cosa) - axis.x() * sina;
    m[2][0] = axis.z() * axis.x() * (1-cosa) - axis.y() * sina;
    m[2][1] = axis.z() * axis.y() * (1-cosa) + axis.x() * sina;
    m[2][2] = cosa + (axis.z() * axis.z())*(1-cosa);
}

template<typename T>
inline std::set<T> Common::setIntersection(const std::set<T> &a, const std::set<T> &b){
    std::set<T> intersect;
    std::set_intersection(a.begin(),a.end(),b.begin(),b.end(),
                      std::inserter(intersect,intersect.begin()));
    return intersect;
}

template<typename T>
inline std::set<T> Common::setUnion(const std::set<T> &a, const std::set<T> &b){
    std::set<T> u;
    std::set_union(a.begin(),a.end(),b.begin(),b.end(),
                      std::inserter(u,u.begin()));
    return u;
}

template<typename T>
inline std::set<T> Common::setDifference(const std::set<T> &a, const std::set<T> &b){
    std::set<T> diff;
    std::set_difference(a.begin(),a.end(),b.begin(),b.end(),
                      std::inserter(diff,diff.begin()));
    return diff;
}

template<typename T>
inline bool Common::isSubset(const std::set<T> &a, const std::set<T> &b){
    return std::includes(b.begin(), b.end(), a.begin(), a.end());
}

/**
 * \~English
 * @brief this function executes a command on the shell
 * @param[in] cmd: string containing the command
 * @return the output of the executed command
 */
inline std::string Common::executeCommand(const char* cmd) {
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}

/**
 * \~English
 * @brief this function flips a pair
 * @param[in] p: input pair
 * @return the flipped pair
 */
template<typename A, typename B>
inline std::pair<B,A> Common::flipPair(const std::pair<A,B> &p) {
    return std::pair<B,A>(p.second, p.first);
}

/**
 * \~English
 * @brief this function flips a std::map on a std::multimap. All the elements of the multimap will be sorted by the value of the map.
 * @param[in] src: input map
 * @return the flipped multimap
 */
template<typename A, typename B, template<class,class,class...> class M, class... Args>
inline std::multimap<B,A> Common::flipMap(const M<A,B,Args...> &src) {
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(),
                   std::inserter(dst, dst.begin()),
                   flipPair<A,B>);
    return dst;
}

template <typename T>
bool Common::isInBounds(const T& value, const T& low, const T& high) {
    return !(value < low) && !(high < value);
}

template <typename T, typename R, typename Comparator>
bool Common::isInBounds(const T& value, const R& low, const R& high, Comparator comp) {
    return !comp(value, low) && !comp(high, value);
}


template <typename T, typename AdjComparator>
inline std::map<T, Color> Common::smartColoring(const std::vector<T> &elements, AdjComparator comp, const std::vector<Color> &colors) {
    std::set<T> colored;
    std::map<T, Color> colorMap;
    for (const T i : elements){
        if (colored.find(i) == colored.end()){
            std::set<Color> adjColors;
            std::set<T> adjacences = comp.getAdjacences(i);
            for (T adj : adjacences){
                if (colored.find(adj) != colored.end())
                    adjColors.insert(colorMap[adj]);
            }

            Color color;
            bool finded = false;
            for (unsigned int k = 0; k < colors.size() && !finded; k++){
                if (adjColors.find(colors[k]) == adjColors.end()){
                    finded = true;
                    color = colors[k];
                }
            }
            assert(finded);
            colorMap[i] = color;
            colored.insert(i);
        }
    }
    return colorMap;
}

/**
 * @brief Common::sortIndexes
 *
 * returns the indices corrispondence of the v vector sorted.
 *
 * https://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
 *
 * @param v
 * @return
 */

template <typename T>
inline std::vector<size_t> Common::sortIndexes(const std::vector<T> &v) {

    // initialize original index locations
    std::vector<size_t> idx(v.size());
    std::iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    std::sort(idx.begin(), idx.end(),
              [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

    return idx;
}
