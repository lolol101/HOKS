QT += gui widgets network core

CONFIG += c++17 console
CONFIG -= app_bundle

SOURCES += \
    client.cpp \
    main.cpp \
    Graphics/authorizationWindow.cpp

HEADERS += \
    client.h \
    Commands.h \
    Graphics/appstyle.h \
    Graphics/authorizationWindow.h \

FORMS += \
    Graphics/authorizationWindow.ui

RESOURCES += \
    Graphics/resource.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

