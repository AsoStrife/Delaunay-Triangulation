#include <Andrea/Headers/Drawable/drawabledelaunaytriangulation.h>

DrawableDelaunayTriangulation::DrawableDelaunayTriangulation(){}

/**
 * @brief DrawableDelaunayTriangulation::draw
 * This method draw the triangle inside the canvas.
 * If getIsDeleted == true print all points and edges, otherwise
 * only the point inside the bounding triangle an the edges that
 * not lie in one of three verticies of the bounding triangle
 */
void DrawableDelaunayTriangulation::draw() const{

    if(this->triangles.size() > 0){
        for(unsigned int i = 0; i < this->triangles.size(); i++){
            // Take only the triangle that have getIsDeleted == false, that is still valid inside the triangulation
            if(this->triangles.at(i)->getIsDeleted() == false){
                // if the boundingTriangleActive is true, print the bounding triangle and the edge that lie in those verticies
                if(this->boundingTriangleActive == true){

                    // Verticies
                    Viewer::drawPoint2D( *triangles[i]->getA(), this->delaunayPointColor, this->pointSize);
                    Viewer::drawPoint2D( *triangles[i]->getB(), this->delaunayPointColor, this->pointSize);
                    Viewer::drawPoint2D( *triangles[i]->getC(), this->delaunayPointColor, this->pointSize);

                    // Edges
                    Viewer::drawLine2D( *triangles[i]->getA(), *triangles[i]->getB(), this->delaunayLineColor, this->lineSize);
                    Viewer::drawLine2D( *triangles[i]->getB(), *triangles[i]->getC(), this->delaunayLineColor, this->lineSize);
                    Viewer::drawLine2D( *triangles[i]->getC(), *triangles[i]->getA(), this->delaunayLineColor, this->lineSize);


                }
                else{ // Print only the point and edge inside the bounding triangle
                    // Verticies
                    if(needToPrintPoint( *triangles[i]->getA() ) == true)
                        Viewer::drawPoint2D( *triangles[i]->getA(), this->delaunayPointColor, this->pointSize);
                    if( needToPrintPoint( *triangles[i]->getB() ) == true)
                        Viewer::drawPoint2D( *triangles[i]->getB(), this->delaunayPointColor, this->pointSize);
                    if( needToPrintPoint( *triangles[i]->getC() ) == true)
                        Viewer::drawPoint2D( *triangles[i]->getC(), this->delaunayPointColor, this->pointSize);

                    // Edges
                    if( needToPrintLine( *triangles[i]->getA(), *triangles[i]->getB() ) == true )
                        Viewer::drawLine2D( *triangles[i]->getA(), *triangles[i]->getB(), this->delaunayLineColor, this->lineSize);

                    if( needToPrintLine( *triangles[i]->getB(), *triangles[i]->getC())  == true )
                        Viewer::drawLine2D( *triangles[i]->getB(), *triangles[i]->getC(), this->delaunayLineColor, this->lineSize);

                    if( needToPrintLine( *triangles[i]->getC(), *triangles[i]->getA())  == true )
                        Viewer::drawLine2D( *triangles[i]->getC(), *triangles[i]->getA(), this->delaunayLineColor, this->lineSize);
                } //  if(this->boundingTriangleActive == true)


            } // if(*triangles[i]->getIsDeleted == false)

        } //for
    } // size() > 0
}

/**
 * @brief DrawableDelaunayTriangulation::sceneCenter
 * @return the center of the scene
 */
Pointd DrawableDelaunayTriangulation::sceneCenter() const {
   return Pointd(0, 0);
}

/**
 * @brief DrawableDelaunayTriangulation::sceneRadius
 * @return -1
 */
double DrawableDelaunayTriangulation::sceneRadius() const {
    return -1;
}

/**
 * @brief DrawableDelaunayTriangulation::setBoundingTriangleActive
 * @param b, simple boolean value
 */
void DrawableDelaunayTriangulation::setBoundingTriangleActive(bool b){
    this->boundingTriangleActive = b;
}

/**
 * @brief DrawableDelaunayTriangulation::needToPrintPoint
 * @param p is a simple point that will be print
 * @return true if p is different from BT_P1, BT_P2, BT_P3
 */
bool DrawableDelaunayTriangulation::needToPrintPoint(const Point2Dd& p) const{
    if( p != BT_P1 && p != BT_P2 && p != BT_P3)
        return true;
    else
        return false;
}

/**
 * @brief DrawableDelaunayTriangulation::needToPrintLine
 * @param p1 first point of the segment
 * @param p2 second point of the segment
 * @returntrue if p1 and p2 are different from BT_P1, BT_P2, BT_P3
 */
bool DrawableDelaunayTriangulation::needToPrintLine(const Point2Dd& p1, const Point2Dd& p2) const{
    if( p1 != BT_P1 && p1 != BT_P2 && p1 != BT_P3 && p2 != BT_P1 && p2 != BT_P2 && p2 != BT_P3)
        return true;
    else
        return false;
}

/**
 * @brief DrawableDelaunayTriangulation::clearTriangles
 * Clear the vector of triangles
 */
void DrawableDelaunayTriangulation::clearTriangles(){
    this->triangles.clear();
}

/**
 * @brief DrawableDelaunayTriangulation::setTriangles
 * @param t the vector of pointer of triangles, obtained from delaunaytriangulationcore.cpp
 * Copy the vector of pointer of triangles, and set the constant value of BT_P1, BT_P2, BT_P3
 * for the bounding triangle
 */
void DrawableDelaunayTriangulation::setTriangles(const std::vector<Triangle*>& t){
    this->clearTriangles();

    this->triangles = t;

    this->BT_P1 = *triangles.at(0)->getA();
    this->BT_P2 = *triangles.at(0)->getB();
    this->BT_P3 = *triangles.at(0)->getC();
}


