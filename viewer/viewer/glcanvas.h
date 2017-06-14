/*
 * @author    Marco Livesu (marco.livesu@gmail.com)
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#ifndef VIEWER_GL_CANVAS_H
#define VIEWER_GL_CANVAS_H

#ifdef WIN32
#include "windows.h"
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <QGLViewer/qglviewer.h>
#include <QGLViewer/manipulatedCameraFrame.h>
#include <QGLWidget>
#include <QKeyEvent>
#include <vector>

#include "common/bounding_box.h"
#include "interfaces/drawable_object.h"
#include "interfaces/pickable_object.h"
#include <qmessagebox.h>
#include <common/point2d.h>

//using namespace std;

class GLcanvas : public QGLViewer {

        Q_OBJECT

    public:

        GLcanvas(QWidget * parent = nullptr);
        ~GLcanvas();

        void init();
        void draw();
        void drawWithNames();
        void clear();
        void fitScene();
        void fitScene(const Pointd &center, double radius);
        void setClearColor(const QColor & color);
        BoundingBox getFullBoundingBox();
        int getNumberVisibleObjects();
        void postSelection(const QPoint& point);

        int  pushObj(const DrawableObject * obj, bool visible = true);
        void deleteObj(const DrawableObject* obj);
        void setVisibility(const DrawableObject * obj, bool visible = true);
        bool isVisible(const DrawableObject* obj);

    signals:
        void objectPicked(unsigned int);
        void point2DClicked(Point2Dd);
    private:

        QColor clearColor;
        std::vector<const DrawableObject *> drawlist;
        std::vector<bool> objVisibility;

        qglviewer::Vec orig, dir, selectedPoint;
};

#endif // VIEWER_GL_CANVAS_H
