#-------------------------------------------------
#
# Project created by QtCreator 2019-08-18T20:54:29
#
#-------------------------------------------------

QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSOLogger
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        src/databasehandler.cpp \
        src/datetimeformatdelegate.cpp \
        src/main.cpp \
        src/newrecord.cpp \
        src/qsologger.cpp \
        src/qsomodel.cpp

HEADERS += \
        src/databasehandler.h \
        src/datetimeformatdelegate.h \
        src/newrecord.h \
        src/qsologger.h \
        src/qsomodel.h

RESOURCES = qsologger.qrc

FORMS += \
        src/ui/qsologger.ui \
        src/ui/record.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
