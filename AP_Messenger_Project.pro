QT       += core gui
QT       += network
QT       += core
QT       += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
RC_ICONS += icon3.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DTO\Channel\channel.cpp \
    Repository\ChannelRepository\channelrepository.cpp \
    Client\client.cpp \
    DTO\DTOParent\dto.cpp \
    ExceotionHandler\exceptionhandler.cpp \
    DTO\Group\group.cpp \
    Repository\GroupRepository\grouprepository.cpp \
    HTTPHandler\httphandler.cpp \
    UI\LoggedinForm\loggedinpage.cpp \
    UI\LoginForm\loginui.cpp \
    Main\main.cpp \
    UI\MainWindow\mainwindow.cpp \
    DTO\PV\pv.cpp \
    Repository\PVRepository\pvrepository.cpp \
    UI\SignupForm\signupui.cpp \
    Repository\Repository\repository.cpp \
    URLMaker\urlmaker.cpp

HEADERS += \
    DTO\Channel\channel.h \
    Repository\ChannelRepository\channelrepository.h \
    Client\client.h \
    DTO\DTOParent\dto.h \
    ExceotionHandler\exceptionhandler.h \
    DTO\Group\group.h \
    Repository\GroupRepository\grouprepository.h \
    HTTPHandler\httphandler.h \
    UI\LoggedinForm\loggedinpage.h \
    UI\LoginForm\loginui.h \
    UI\MainWindow\mainwindow.h \
    DTO\PV\pv.h \
    Repository\PVRepository\pvrepository.h \
    UI\SignupForm\signupui.h \
    Repository\Repository\repository.h \
    URLMaker\urlmaker.h

FORMS += \
    UI\MainWindow\mainwindow.ui \
    UI\LoggedinForm\loggedinpage.ui \
    UI\LoginForm\loginui.ui \
    UI\MainWindow\mainwindow.ui \
    UI\SignupForm\signupui.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
