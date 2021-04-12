#-------------------------------------------------
#
# Project created by QtCreator 2013-10-01T09:40:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseGraphiX
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp \
    camera.cpp \
    scene.cpp \
    visualizator.cpp \
    particle_system.cpp \
    scene_object.cpp \
    calculations.cpp \
    particle.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    camera.h \
    scene.h \
    visualizator.h \
    particle_system.h \
    scene_object.h \
    user_definitions.h \
    calculations.h \
    particle.h

FORMS    += mainwindow.ui
