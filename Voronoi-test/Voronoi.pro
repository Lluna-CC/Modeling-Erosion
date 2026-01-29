QT += core gui opengl widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++11
CONFIG(release, release|debug):QMAKE_CXXFLAGS += -Wall -O2 -I/usr/local/include/voro++ -L/usr/local/lib
LIBS += -lvoro++


SOURCES += \
    core.cpp \
    heightfield-breach.cpp \
    heightfield-fill.cpp \
    heightfield-metrics-hydrology.cpp \
    heightfield-metrics-landforms.cpp \
    heightfield-metrics-local.cpp \
    heightfield-metrics-orometry.cpp \
    heightfield-metrics-visibility.cpp \
    heightfield.cpp \
    integerfield.cpp \
    isolation.cpp \
    main.cpp \
    mainwindow-draw-metrics.cpp \
    mainwindow.cpp \
    ppa.cpp \
    riversnet.cpp \
    scalarfield.cpp \
    terrainwidget.cpp \
    voronoi.cpp \
    heightfieldWall.cpp

HEADERS += \
    core.h \
    heightfield.h \
    integerfield.h \
    isolation.h \
    mainwindow.h \
    ppa.h \
    riversnet.h \
    scalarfield.h \
    terrainwidget.h \
    voronoi.h \
    heightfieldWall.h 

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
