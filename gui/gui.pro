######################################################################
# Automatically generated by qmake (2.01a) jeu. oct. 11 23:31:54 2007
######################################################################

TEMPLATE = app
TARGET = qpackagekit
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += qdbus

INCLUDEPATH += ../lib
LIBS += ../lib/libqpackagekit.so.0.0.1

# Input
RESOURCES += resources.qrc
HEADERS += MainWindow.h PackageModel.h 
FORMS += mainwindow.ui
SOURCES += main.cpp MainWindow.cpp PackageModel.cpp 