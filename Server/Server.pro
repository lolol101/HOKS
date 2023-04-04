QT += core network sql

CONFIG += c++17 console
CONFIG -= app_bundle

SOURCES += \
    database/database.cpp \
    main.cpp \
    server.cpp


HEADERS += \
    database/database.h \
    Commands.h \
    server.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
