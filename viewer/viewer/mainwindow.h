/*
 * @author    Marco Livesu (marco.livesu@gmail.com)
 * @author    Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @copyright Alessandro Muntoni 2016.
 */

#ifndef VIEWER_MAINWINDOW_H
#define VIEWER_MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QToolBox>
#include <QFrame>
#include <QSignalMapper>
#include <QCheckBox>
#include <QProcess>
#ifdef __APPLE__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wredeclared-class-member"
#endif
#include <boost/bimap.hpp>
#ifdef __APPLE__
#pragma clang diagnostic pop
#endif
#include <QApplication>

#include "interfaces/drawable_object.h"
#include "interfaces/pickable_object.h"
#include "common/bounding_box.h"
#include "objects/drawabledebugobjects.h"
#include <common/point2d.h>

namespace Ui {
    class MainWindow;
}

/**
 * @brief La classe MainWindow è una classe che gestisce la canvas di QGLViewer e tutti i manager che vengono aggiunti ad essa.
 *
 * Gestisce in oltre una scrollArea avente le checkbox che gestiscono la visualizzazione di tutti gli oggetti presenti nella canvas.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

    public:

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void fitScene();
        void fitScene(const Pointd& center, double radius);
        Point2Di getCanvasSize();
        void updateGlCanvas();
        void pushObj(const DrawableObject * obj, std::string checkBoxName, bool b = true);
        void deleteObj(const DrawableObject * obj, bool b = true);
        bool contains(const DrawableObject* obj);
        BoundingBox getFullBoundingBox();
        int getNumberVisibleObjects();
        void saveSnapshot();
        void drawAxis(bool);

        void setFullScreen(bool);
        void setBackgroundColor(const QColor &);

        int addManager(QFrame *f, std::string name, QToolBox *parent = nullptr);
        QFrame *getManager(unsigned int i);
        void renameManager(unsigned int i, std::string s);
        void setCurrentIndexToolBox(unsigned int i);

        void disableRotation();
        void enableRotation();
        void disableTranslation();
        void enableTranslation();
        void disableZoom();
        void enableZoom();
        void setSelectLeftButton();

        void enableDebugObjects();
        void disableDebugObjects();
        void addDebugSphere(const Pointd& center, double radius, const QColor &color, int precision = 4);
        void clearDebugSpheres();
        void addDebugCylinder(const Pointd& a, const Pointd& b, double radius, const QColor color);
        void clearDebugCylinders();

        void keyPressEvent(QKeyEvent * event);

    signals:
        /**
         * @brief objectClicked
         * Segnale da "catchare", ha come parametro l'oggetto cliccato nella GLCanvas
         */
        void objectPicked(unsigned int);
        void point2DClicked(Point2Dd);

        /**
         * @brief undoEvent
         * Segnale da "catchare", viene lanciato quando viene premuto CTRL+Z
         */
        void undoEvent();

        /**
         * @brief undoEvent
         * Segnale da "catchare", viene lanciato quando viene premuto MAIUSC+CTRL+Z
         */
        void redoEvent();

    private slots:
        void checkBoxClicked(int i);
        void slotObjectPicked(unsigned int i);
        void slotPoint2DClicked(Point2Dd p);

    private:

        // GUI
        //
        Ui::MainWindow  * ui;
        std::vector<QFrame *> managers;

        // Mesh Stack
        //
        QSignalMapper* checkBoxMapper;
        std::map<int, QCheckBox * > checkBoxes;
        boost::bimap<int, const DrawableObject*> mapObjects;
        int nMeshes;
        bool first;
        DrawableDebugObjects* debugObjects;
};

#endif // VIEWER_MAINWINDOW_H
