#include "delaunaymanager.h"
#include "ui_delaunaymanager.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

#include <ctime>

#include "utils/fileutils.h"
#include "utils/delaunay_checker.h"

#include <common/arrays.h>
#include <common/timer.h>

#include <viewer/objects/objects.h>
#include <viewer/interfaces/drawable_object.h>

//limits for the bounding box
const double BOUNDINGBOX = 1e+6;
const double SCENERADIUS = BOUNDINGBOX;
const Pointd SCENECENTER(0,0,0);


//coordinates of the bounding triangle.
//use these coordinates to initialize the bounding triangle of your triangulation
const Point2Dd BT_P1(1e+10, 0);
const Point2Dd BT_P2(0, 1e+10);
const Point2Dd BT_P3(-1e+10, -1e+10);


/***************************
* Constructors/Destructors *
***************************/

/**
 * @brief Constructor
 */
DelaunayManager::DelaunayManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DelaunayManager),
    mainWindow((MainWindow&)*parent),
    boundingBox(Point2Dd(-BOUNDINGBOX, -BOUNDINGBOX),
                Point2Dd(BOUNDINGBOX, BOUNDINGBOX))

{


    //UI setup
    ui->setupUi(this);
    connect(&mainWindow, SIGNAL(point2DClicked(Point2Dd)), this, SLOT(point2DClicked(Point2Dd)));

    //Setting options to use the canvas
    mainWindow.disableRotation();

    mainWindow.setSelectLeftButton();

    // putting the drawable object to the mainWindow.
    // the mainWindow will take care of the rendering of the bounding box
    mainWindow.pushObj(&boundingBox, "Bounding box");

    // Credo l'oggetto Delaunay Triangulation
    dtc.setBoundingTrianglePoints(BT_P1, BT_P2, BT_P3);
    mainWindow.pushObj(&ddt, "Delaunay Triangulation");
    mainWindow.pushObj(&dvd, "Voronoi Diagram");
    mainWindow.updateGlCanvas();

    fitScene();
}


/**
 * @brief Destructor
 */
DelaunayManager::~DelaunayManager() {
    //when destroyed the manager, the mainWindow mustn't have the
    //reference to the bounding box.
    mainWindow.deleteObj(&boundingBox);
    delete ui;
}


/*****************
* Private fields *
*****************/

/**
 * @brief Fit scene on the bounding box
 */
void DelaunayManager::fitScene() {
    //do not write code here
    mainWindow.fitScene(SCENECENTER, SCENERADIUS);
}


/********
* Slots *
********/


/**
 * @brief Enable picking checkbox
 */
void DelaunayManager::on_enablePickingCheckBox_stateChanged(int arg1) {
    //do not write code here
    if (arg1 == Qt::Checked){
        mainWindow.setSelectLeftButton();
    }
    else {
        mainWindow.disableRotation();
    }
}

void DelaunayManager::on_resetScenePushButton_clicked() {
    //do not write code here
    fitScene();
}





/**
 * @brief Clean button event handler
 */
void DelaunayManager::on_clearPointsPushButton_clicked() {

    //clear here your triangulation
    dtc.cleanDelaunayTriangulation(); // Elimino tutti i punti
    ddt.clearTriangles();

    dtc.setBoundingTrianglePoints(BT_P1, BT_P2, BT_P3); // Setto nuovamente il Bounding Triangle come triangolo iniziale
    ddt.setTriangles( dtc.getTriangles() );


    mainWindow.updateGlCanvas();
}


/**
 * @brief Show bounding triangle checkbox event handler
 * Disegno il bounding triangle
 */
void DelaunayManager::on_showBoundingTriangleCheckBox_stateChanged(int arg1) {

    //if arg1 is true, you must draw the bounding triangle of your triangulation
    if(arg1){
        ddt.setBoundingTriangleActive(true);
    }
    else{
        ddt.setBoundingTriangleActive(false);
    }

    mainWindow.updateGlCanvas();
}

/**
 * @brief Load point event handler
 */
void DelaunayManager::on_loadPointsPushButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(nullptr,
                       "Open points",
                       ".",
                       "*.txt");

    if (!filename.isEmpty()) {

        std::vector<Point2Dd> points = FileUtils::getPointsFromFile(filename.toStdString());

        Timer t("Delaunay Triangulation");

        //launch your triangulation algorithm here

        for(unsigned i = 0; i < points.size(); i++)
            dtc.addPoint(points.at(i));

        t.stopAndPrint();

        ddt.setTriangles( dtc.getTriangles() ); // Aggiorno la drawable

        mainWindow.updateGlCanvas();
    }
}

/**
 * @brief DelaunayManager::point2DClicked
 *
 * this method is called when a there is a click in the canvas.
 * The coordinates of the point are given in the point p.
 *
 * @param p
 */
void DelaunayManager::point2DClicked(const Point2Dd& p) {
    if (!boundingBox.isInside(p)) {
        QMessageBox::warning(this, "Cannot insert point", "Point [" + QString::number(p.x()) + "," + QString::number(p.y()) + "] is not contained in the bounding box.");
        return;
    }
    else {
        //comment the next line
        //QMessageBox::information(this, "Point Clicked", "Point [" + QString::number(p.x()) + "," + QString::number(p.y()) + "].");
        //manage here the insertion of the point inside the triangulation

        /******/
        if(dtc.addPoint(p) == false)
            QMessageBox::warning(this, "Point already exist", "The point in the coordinates [" + QString::number(p.x()) + "," + QString::number(p.y()) + "] already exist.");
        else{
            std::vector<Triangle*> triangles = dtc.getTriangles();
            ddt.setTriangles( triangles );

        }/******/

    }

    mainWindow.updateGlCanvas();
}



void DelaunayManager::on_checkTriangulationPushButton_clicked() {
    // Ottengo i punti della triangolazione
    std::vector<Point2Dd> points = dtc.getPointsForValidation();
    Array2D<unsigned int> triangles;

    //get your triangulation here and save it in the vector points and in the matrix triangles
    //"points" will be a vector where every position i is associated to a point of the triangulation
    //"triangle" will be a Matrix with n rows (n = number of triangles) and 3 columns.
    //the i-th row represents the i-th triangle, composed of three unsigned integers which are
    //the indices of the points in the vector "points" that belong to the i-th triangle.

    //you can initially resize the matrix "triangles" by calling triangles.resize(n, 3),
    //and then fill the matrix using the assignment operator: triangles(i,j) = a;
    dtc.generateTrianglesForValidation();

    triangles.resize( dtc.getCountValidTriangle(), 3);
    triangles = dtc.getValidTriangles();

    if (DelaunayTriangulation::Checker::isDeulaunayTriangulation(points, triangles)) {
        QMessageBox::information(this, "Triangulation checking", "Success: it is a Delaunay triangulation!");
    }
    else {
        QMessageBox::warning(this, "Triangulation checking", "Error: it is NOT a Delaunay triangulation!");
    }
}

void DelaunayManager::on_generatePointsFilePushButton_clicked() {
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(nullptr,
                       "File containing points",
                       ".",
                       "TXT(*.txt)", &selectedFilter);

    if (!filename.isEmpty()){
        int number = QInputDialog::getInt(this, tr("Generate file"),
                                                 tr("Number of random points:"), 1000, 0, 1000000000, 1);

        FileUtils::generateRandomPointFile(filename.toStdString(), BOUNDINGBOX, number);
    }
}

void DelaunayManager::on_voronoiDiagramPushButton_clicked(){
    dvd.setTriangles( dtc.getTriangles() );
    mainWindow.updateGlCanvas();
}

void DelaunayManager::on_clearVoronoiDiagramPushButton_clicked(){
    dvd.clearVoronoi();
    mainWindow.updateGlCanvas();
}
