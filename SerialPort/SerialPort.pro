#-------------------------------------------------
#
# Project created by QtCreator 2014-03-31T23:05:21
#
#-------------------------------------------------


QT       += gui widgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialPort
TEMPLATE = app


SOURCES += main.cpp\
    SearchForSerialPort.cpp \
    SerialThread.cpp \
    WriteThread.cpp \
    ReadThread.cpp \
    MainApplicationUI.cpp \
    Queue/MyQueue.cpp \
    LedChoose.cpp

HEADERS  += \
    SearchForSerialPort.h \
    SerialThread.h \
    WriteThread.h \
    ReadThread.h \
    MainApplicationUI.h \
    Queue/QueueNode.h \
    Queue/MyQueue.h \
    LedChoose.h
FORMS    += \
    SearchForSerialPort.ui \
    MainApplicationUI.ui \
    LedChoose.ui
QMAKE_CXXFLAGS += -std=c++11

DISTFILES +=

RESOURCES += \
    resource.qrc
CONFIG += thread
include(qextserialport/src/qextserialport.pri)
