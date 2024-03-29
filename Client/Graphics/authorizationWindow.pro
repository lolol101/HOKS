QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MessageLine.cpp \
    MainWindow.cpp \
    MessageWidget.cpp \
    NewRoomWidget.cpp \
    Room.cpp \
    RoomIconWidget.cpp \
    RoomInsideWidget.cpp \
    authorizationWindow.cpp \
    main.cpp

HEADERS += \
    MessageLine.h \
    MainWindow.h \
    MessageWidget.h \
    NewRoomWidget.h \
    Room.h \
    RoomIconWidget.h \
    RoomInsideWidget.h \
    authorizationWindow.h \
    appstyle.h

FORMS += \
    MessageLine.ui \
    MainWindow.ui \
    MessageWidget.ui \
    NewRoomWidget.ui \
    Room.ui \
    RoomIconWidget.ui \
    RoomInsideWidget.ui \
    authorizationWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
