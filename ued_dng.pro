#-------------------------------------------------
#
# Project created by QtCreator 2019-01-03T09:18:26
#
#-------------------------------------------------
QT       += core gui sql websockets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ued_dng
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
        main.cpp \
    dashboardwindow.cpp \
    server.cpp \
    judge.cpp \
    submissionviewdialog.cpp


HEADERS += \
    dashboardwindow.h \
    contest.h \
    http.h \
    crow.h \
    server.h \
    json.h \
    judge.h \
    submissionviewdialog.h \
    export.h

FORMS += \
    dashboardwindow.ui \
    submissionviewdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/boost/1.67.0_1/lib/release/ -lboost_thread-mt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/boost/1.67.0_1/lib/debug/ -lboost_thread-mt
else:unix: LIBS += -L$$PWD/../../../../usr/local/Cellar/boost/1.67.0_1/lib/ -lboost_thread-mt

# boost lib
INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/boost/1.67.0_1/include
DEPENDPATH += $$PWD/../../../../usr/local/Cellar/boost/1.67.0_1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/boost/1.67.0_1/lib/release/ -lboost_system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/boost/1.67.0_1/lib/debug/ -lboost_system
else:unix: LIBS += -L$$PWD/../../../../usr/local/Cellar/boost/1.67.0_1/lib/ -lboost_system

INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/boost/1.67.0_1/include
DEPENDPATH += $$PWD/../../../../usr/local/Cellar/boost/1.67.0_1/include

DISTFILES +=

RESOURCES += files.qrc
ICON = app.icns


## XLS lib
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/libxlsxwriter/0.8.4/lib/release/ -lxlsxwriter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/libxlsxwriter/0.8.4/lib/debug/ -lxlsxwriter
else:unix: LIBS += -L$$PWD/../../../../usr/local/Cellar/libxlsxwriter/0.8.4/lib/ -lxlsxwriter

INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/libxlsxwriter/0.8.4/include
DEPENDPATH += $$PWD/../../../../usr/local/Cellar/libxlsxwriter/0.8.4/include
