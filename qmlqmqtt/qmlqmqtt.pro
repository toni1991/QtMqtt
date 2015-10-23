TEMPLATE = lib
TARGET = QmlQmqtt
QT += qml quick
CONFIG += qt plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = QmlQmqtt

# Input
SOURCES += \
    src/qmlqmqtt_plugin.cpp \
    src/qmlqmqtt.cpp

HEADERS += \
    include/qmlqmqtt_plugin.h \
    include/qmlqmqtt.h \

INCLUDEPATH += ./include

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}


unix|win32: LIBS += -L$$OUT_PWD/../qmqtt/ -lqmqtt

INCLUDEPATH += $$PWD/../qmqtt/include
DEPENDPATH += $$PWD/../qmqtt

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../qmqtt/qmqtt.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../qmqtt/libqmqtt.a
