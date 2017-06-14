DEFINES += COMMON_DEFINED
CONFIG += COMMON_DEFINED

CONFIG += OPENMP

unix:!macx{
    QMAKE_CXXFLAGS += -std=c++11

    exists(/usr/include/eigen3){
        DEFINES += COMMON_WITH_EIGEN
        MODULES += COMMON_WITH_EIGEN
        INCLUDEPATH += -I /usr/include/eigen3
    }
    else{
        MODULES += COMMON_WITHOUT_EIGEN
    }
}

macx{
    CONFIG += c++11
    
    exists(/libs/include/eigen3){
        DEFINES += COMMON_WITH_EIGEN
        MODULES += COMMON_WITH_EIGEN
        INCLUDEPATH += -I /libs/include/eigen3/
    }
    else{
        MODULES += COMMON_WITHOUT_EIGEN
    }
}

OPENMP {
    unix:!macx{
        QMAKE_CXXFLAGS += -fopenmp
        QMAKE_LFLAGS += -fopenmp
    }
}

win32 {
    CONFIG += c++11

    exists(C:/dev/eigen3){
        DEFINES += COMMON_WITH_EIGEN
        MODULES += COMMON_WITH_EIGEN
        INCLUDEPATH += -I C:/dev/eigen3
    }
    else{
        MODULES += COMMON_WITHOUT_EIGEN
    }
}

HEADERS += \
    $$PWD/common/bounding_box.h \
    $$PWD/common/comparators.h \
    $$PWD/common/point.h \
    $$PWD/common/point2d.h \
    $$PWD/common/serialize.h \
    $$PWD/common/arrays.h \
    $$PWD/common/timer.h \
    $$PWD/common/utils.h \
    $$PWD/common/hashlib.h \
    $$PWD/common/file_conversions.h \
    $$PWD/common/serializable_object.h \
    $$PWD/common/load_save_file.h \
    $$PWD/common/color.h \
    $$PWD/common/geometry/line.h \
    $$PWD/common/geometry/plane.h \
    $$PWD/common/bounding_box2d.h

SOURCES += \
    $$PWD/common/load_save_file.cpp \
    $$PWD/common/point.cpp \
    $$PWD/common/arrays.cpp \
    $$PWD/common/color.cpp \
    $$PWD/common/point2d.cpp \
    $$PWD/common/geometry/line.cpp \
    $$PWD/common/geometry/plane.cpp

DISTFILES += \
    $$PWD/common/bounding_box.cpp \
    $$PWD/common/timer.cpp \
    $$PWD/common/utils.cpp \
    $$PWD/common/serialize.cpp \
    $$PWD/common/bounding_box2d.cpp

INCLUDEPATH += $$PWD


