QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calc.c \
    credit.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    menuwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    calc.h \
    credit.h \
    graph.h \
    mainwindow.h \
    menuwindow.h \
    qcustomplot.h

FORMS += \
    credit.ui \
    graph.ui \
    mainwindow.ui \
    menuwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../Desktop/icons8-1-48.png

RESOURCES += \
    resourses.qrc
