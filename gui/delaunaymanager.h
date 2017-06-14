#ifndef DELAUNAYMANAGER_H
#define DELAUNAYMANAGER_H

#include <QFrame>

#include <viewer/mainwindow.h>

#include <viewer/drawable_objects/drawableboundingbox2d.h>


namespace Ui {
    class DelaunayManager;
}

class DelaunayManager : public QFrame {
    Q_OBJECT

public:
    /***************************
    * Constructors/Destructors *
    ***************************/

    explicit DelaunayManager(QWidget *parent = 0);
    ~DelaunayManager();

protected:

private:
    /************
    * UI fields *
    *************/

    Ui::DelaunayManager *ui;
    MainWindow& mainWindow;

    /*****************
    * Private fields *
    *****************/

    const DrawableBoundingBox2D boundingBox; //it is const because, once defined and initialized, it will never change!

    /*****************
    * Private methods *
    *****************/

    void fitScene();

private slots:

    /********
    * Slots *
    ********/

    /** UI slots **/
    void on_enablePickingCheckBox_stateChanged(int arg1);
    void on_resetScenePushButton_clicked();
    void on_loadPointsPushButton_clicked();

    void on_clearPointsPushButton_clicked();
    void on_showBoundingTriangleCheckBox_stateChanged(int arg1);

    /** Point clicked receiver **/
    void point2DClicked(const Point2Dd& p);

    void on_checkTriangulationPushButton_clicked();
    void on_generatePointsFilePushButton_clicked();
};

#endif // DELAUNAYMANAGER_H
