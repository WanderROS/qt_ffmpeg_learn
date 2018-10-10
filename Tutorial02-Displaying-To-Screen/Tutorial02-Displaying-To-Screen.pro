#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T10:44:58
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tutorial02-Displaying-To-Screen
TEMPLATE = app
INCLUDEPATH+=/usr/local/Cellar/ffmpeg/4.0.2/include
LIBS += -L/usr/local/Cellar/ffmpeg/4.0.2/lib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswscale

SOURCES += main.cpp\
        widget.cpp \
    ffmpegworker.cpp

HEADERS  += widget.h \
    ffmpegworker.h
