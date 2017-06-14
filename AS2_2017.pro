CONFIG(debug, debug|release){
    DEFINES += DEBUG
}
CONFIG(release, debug|release){
    DEFINES -= DEBUG
    #just uncomment next lines if you want to ignore asserts and got a more optimized binary
    #CONFIG += FINAL_RELEASE
}
FINAL_RELEASE {
    unix:!macx{
        QMAKE_CXXFLAGS_RELEASE -= -g -O2
        QMAKE_CXXFLAGS += -O3 -DNDEBUG
    }
}

#Add or remove all the modules you need
#Before pushing the project with your new module, please double check that everything works keeping uncommentend
#only the modules that are required by your module. Also please write here required and optional modules for your module

#Common module: contains classes and common functions used on all the other modules
#Optional: Eigen
include (common/common.pri)

#Viewer module: contains classes for a simple viewer
#Requires: Common module, libQGLViewer, boost
include (viewer/viewer.pri)

#comment next line if you don't want to see the message that shows included modules
message(Included modules: $$MODULES)

HEADERS += \
    gui/delaunaymanager.h \
    utils/fileutils.h \
    utils/delaunay_checker.h

SOURCES += \
    main.cpp \
    gui/delaunaymanager.cpp \
    utils/fileutils.cpp \
    utils/delaunay_checker.cpp

FORMS += \
    gui/delaunaymanager.ui




