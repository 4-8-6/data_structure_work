QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    XmlStreamReader.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow1.cpp \
    mainwindow2.cpp \
    mainwindow3.cpp \
    mainwindow4.cpp \
    mainwindow5.cpp \
    mainwindow6.cpp \
    solution.cpp

HEADERS += \
    XmlStreamReader.h \
    mainwindow.h \
    mainwindow1.h \
    mainwindow2.h \
    mainwindow3.h \
    mainwindow4.h \
    mainwindow5.h \
    mainwindow6.h \
    solution.h

FORMS += \
    mainwindow.ui \
    mainwindow1.ui \
    mainwindow2.ui \
    mainwindow3.ui \
    mainwindow4.ui \
    mainwindow5.ui \
    mainwindow6.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc
