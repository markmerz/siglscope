#-------------------------------------------------
#
# Project created by QtCreator 2015-09-20T18:54:51
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

LIBS += -lfftw3

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = siglscope
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    addcommanddialog.cpp \
    selectdevicedialog.cpp \
    Device.cpp \
    Wave.cpp \
    commandreplydialog.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    addcommanddialog.h \
    constants.h \
    selectdevicedialog.h \
    Device.h \
    template_siglent_dso_sds1000.h \
    Wave.h \
    commandreplydialog.h

FORMS    += mainwindow.ui \
    addcommanddialog.ui \
    selectdevicedialog.ui \
    commandreplydialog.ui
