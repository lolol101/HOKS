QT += gui widgets network core

CONFIG += c++17 console
CONFIG -= app_bundle

SOURCES += \
    client.cpp \
    main.cpp \
    Graphics/authorizationWindow.cpp \
    Graphics/Room.cpp \
    Graphics/RoomIconWidget.cpp \
    Graphics/RoomInsideWidget.cpp \
    Graphics/MessageWidget.cpp \
    Graphics/MainWindow.cpp \
    Graphics/NewRoomWidget.cpp \
    Graphics/MessageLine.cpp \
    socket_manager.cpp \

HEADERS += \
    client.h \
    Commands.h \
    Graphics/appstyle.h \
    Graphics/authorizationWindow.h \
    Graphics/Room.h \
    Graphics/RoomIconWidget.h \
    Graphics/RoomInsideWidget.h \
    Graphics/MessageWidget.h \
    Graphics/MainWindow.h \
    Graphics/NewRoomWidget.h \
    Graphics/MessageLine.h \
    msg.h \
    socket_manager.h \

FORMS += \
    Graphics/authorizationWindow.ui \
    Graphics/MainWindow.ui \
    Graphics/MessageWidget.ui \
    Graphics/Room.ui \
    Graphics/RoomInsideWidget.ui \
    Graphics/RoomIconWidget.ui \
    Graphics/NewRoomWidget.ui \
    Graphics/MessageLine.ui \

RESOURCES += \
    Graphics/resource.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

