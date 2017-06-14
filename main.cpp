///Test common.pri
#ifdef COMMON_DEFINED
#include <common/arrays.h>
#include <common/bounding_box.h>
#include <common/comparators.h>
#include <common/timer.h>
#endif

///Test viewer.pri
#ifdef VIEWER_DEFINED
#include <viewer/interfaces/drawable_object.h>
#include <viewer/interfaces/pickable_object.h>
#include <viewer/mainwindow.h>
#include <viewer/managers/windowmanager.h>
#endif

#include "gui/delaunaymanager.h"

int main(int argc, char *argv[]) {

    ///Test viewer.pri:
    #ifdef VIEWER_DEFINED
    QApplication app(argc, argv);

    MainWindow gui;  // finestra principale, contiene la canvas di QGLViewer


    WindowManager wm(&gui); // Creo un window manager e lo aggiungo alla mainwindow
    gui.addManager(&wm, "Window");

    DelaunayManager delaunayManager(&gui);
    int id = gui.addManager(&delaunayManager, "Delaunay Manager");

    gui.setCurrentIndexToolBox(id); // il delaunay manager sarà quello visualizzato di default
    gui.updateGlCanvas();

    gui.show();


    return app.exec();
    #else
    std::cout << "Hello World!" << std::endl;
    return 0;
    #endif
}
