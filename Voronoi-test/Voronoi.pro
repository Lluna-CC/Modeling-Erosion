QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++11

INCLUDEPATH += code
INCLUDEPATH += code/scenes
INCLUDEPATH += code/widgets
INCLUDEPATH += extlibs

VPATH += code

SOURCES += \
    code/camera.cpp \
    code/glutils.cpp \
    code/glwidget.cpp \
    code/main.cpp \
    code/mainwindow.cpp \
    code/model.cpp \
    code/scenes/scenebase.cpp \
    code/widgets/widgetbase.cpp \

HEADERS += \
    code/camera.h \
    code/defines.h \
    code/glutils.h \
    code/glwidget.h \
    code/mainwindow.h \
    code/model.h \
    code/scene.h \
    code/scenes/scenebase.h \
    code/widgets/widgetbase.h \

FORMS += \
    forms/mainwindow.ui \
    forms/widgetbase.ui \

RESOURCES += shaders.qrc
