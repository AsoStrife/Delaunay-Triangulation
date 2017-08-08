DEFINES += VIEWER_DEFINED
CONFIG += VIEWER_DEFINED
MODULES += VIEWER

!contains(DEFINES, COMMON_DEFINED){
    error(Viewer module requires common module!)
}

QT += core gui opengl xml widgets

unix:!macx{
    QMAKE_CXXFLAGS += -std=c++11
    LIBS += /usr/lib/x86_64-linux-gnu/libGLU.so
    LIBS += -lQGLViewer-qt5
}

macx{
    CONFIG += c++11
    INCLUDEPATH += -I /libs/include/boost
    INCLUDEPATH += /libs/frameworks/QGLViewer/QGLViewer.framework/Headers
    LIBS += -F/libs/frameworks/QGLViewer -framework QGLViewer
}

win32 {
    INCLUDEPATH += -I "C:/dev/libQGLViewer"

    LIBS += -lglu32 -lopengl32

    CONFIG(debug, debug|release){
        LIBS += -L"C:/dev/libQGLViewer/QGLViewer" -lQGLViewerd2
    }
    CONFIG(release, debug|release){
        LIBS += -L"C:/dev/libQGLViewer/QGLViewer" -lQGLViewer2
    }
}

HEADERS += \
    $$PWD/viewer/glcanvas.h \
    $$PWD/viewer/mainwindow.h \
    $$PWD/viewer/objects/drawabledebugobjects.h \
    $$PWD/viewer/managers/windowmanager.h \
    $$PWD/viewer/objects/objects.h \
    $$PWD/viewer/interfaces/drawable_object.h \
    $$PWD/viewer/interfaces/pickable_object.h \
    $$PWD/viewer/interfaces/drawable_mesh.h \
    $$PWD/viewer/drawable_objects/drawableboundingbox2d.h

SOURCES += \
    $$PWD/viewer/glcanvas.cpp \
    $$PWD/viewer/mainwindow.cpp \
    $$PWD/viewer/objects/drawabledebugobjects.cpp \
    $$PWD/viewer/managers/windowmanager.cpp \
    $$PWD/viewer/interfaces/drawable_mesh.cpp \
    $$PWD/viewer/drawable_objects/drawableboundingbox2d.cpp

DISTFILES += \
    $$PWD/viewer/objects/objects.cpp

FORMS += \
    $$PWD/viewer/mainwindow.ui \
    $$PWD/viewer/managers/windowmanager.ui

INCLUDEPATH += $$PWD
