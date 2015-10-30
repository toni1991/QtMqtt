QT -= gui
QT += network

TARGET = qmqtt
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    src/qmqtt_client.cpp \
    src/qmqtt_client_p.cpp \
    src/qmqtt_frame.cpp \
    src/qmqtt_message.cpp \
    src/qmqtt_network.cpp \
    src/qmqtt_will.cpp

HEADERS += \
    include/qmqtt.h \
    include/qmqtt_client.h \
    include/qmqtt_client_p.h \
    include/qmqtt_frame.h \
    include/qmqtt_global.h \
    include/qmqtt_message.h \
    include/qmqtt_network.h \
    include/qmqtt_will.h

INCLUDEPATH += ./include

unix:!android {

    target.path = /usr/lib

    headers.files = $${HEADERS}
    headers.path = /usr/include/$${TARGET}

    INSTALLS += target headers
}

mac{
    target.path = /usr/local/lib

    headers.files = $${HEADERS}
    headers.path = /usr/local/include/$${TARGET}

    INSTALLS += target headers
}
