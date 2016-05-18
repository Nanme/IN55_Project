#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T08:59:58
#
#-------------------------------------------------

QT       += core gui opengl

DEPENDPATH += src
INCLUDEPATH = src "./glew-mingw\include"
win32:LIBS += -L"./glew-mingw\lib" -lglew32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IN55_Project
TEMPLATE = app


SOURCES += framework/Shapes/Basis.cpp \
    framework/GlFramework.cpp \
    framework/GlWindow.cpp \
    framework/LF_String.cpp \
    framework/Object3D.cpp \
    framework/RandomNumberGenerator.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/particulsystem.cpp \
    src/particulemitter.cpp \
    src/renderer.cpp \
    src/objectpool.cpp \
    src/transform.cpp

HEADERS  += framework/Shapes/Basis.h \
    framework/AbstractFramework.h \
    framework/GlFramework.h \
    framework/GlWindow.h \
    framework/LF_String.h \
    framework/MemDefns.h \
    framework/Object3D.h \
    framework/RandomNumberGenerator.h \
    framework/Types.h \
    framework/Vectors.h \
#    glew-mingw/include/GL/glew.h \
#    glew-mingw/include/GL/glxew.h \
#    glew-mingw/include/GL/wglew.h \
    src/mainwindow.h \
    src/particulsystem.h \
    src/particulemitter.h \
    src/renderer.h \
    src/objectpool.h \
    src/transform.h
