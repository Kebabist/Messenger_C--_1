QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    exceptionhandler.cpp \
    httphandler.cpp \
    loggedinpage.cpp \
    loginui.cpp \
    main.cpp \
    mainwindow.cpp \
    signupui.cpp \
    urlmaker.cpp

HEADERS += \
    client.h \
    exceptionhandler.h \
    httphandler.h \
    loggedinpage.h \
    loginui.h \
    mainwindow.h \
    signupui.h \
    urlmaker.h

FORMS += \
    exceptionhandler.ui \
    loggedinpage.ui \
    loginui.ui \
    mainwindow.ui \
    signupui.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
