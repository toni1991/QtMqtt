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
installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
qmldir.path = $$installPath
target.path = $$installPath
INSTALLS += target qmldir

INCLUDEPATH += $$PWD/../qmqtt/include
DEPENDPATH += $$PWD/../qmqtt

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qmqtt/release/ -lqmqtt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qmqtt/debug/ -lqmqtt
else:unix: LIBS += -L$$OUT_PWD/../qmqtt/ -lqmqtt

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qmqtt/release/libqmqtt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qmqtt/debug/libqmqtt.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qmqtt/release/qmqtt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qmqtt/debug/qmqtt.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../qmqtt/libqmqtt.a
