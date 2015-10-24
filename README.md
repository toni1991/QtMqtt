# About
This project provides the abilty to establish MQTT connections and to perform MQTT communication using Qt.
This library consists of two parts:

 - Qt/C++ Library
 - QML Plugin

## Credits
For the most part it's a "merge" of the work of the people mentioned below, marely refactored for the sake of readability and to fit particular needs.

Special thanks to the owners of the used repositories and contributors:

 - [@MacroBull] (https://github.com/MacroBull)
 - [@ndesai] (https://github.com/ndesai)
 - [@erylee] (https://github.com/erylee)
 - [@tipih] (https://github.com/tipih)
 - [@Kampfgnom] (https://github.com/Kampfgnom)
 - [@wuming123057](https://github.com/wuming123057)

There are much more contributors which aren't less important! Please refer to the licence headers in each file and the repositories below for detailed information about authors.

Sourcecode taken from:
 - [qmqtt] (https://github.com/emqtt/qmqtt)
 - [qml-qmqtt] (https://github.com/MacroBull/qml-qmqtt)
 - [qtModeratorDemo] (https://github.com/tipih/qtModeratorDemo)

## Compatibility
This library has been compiled and tested on:

 - Fedora 22 x64 - Qt 5.5.1
 - Android NDK r10e-rc4 (64-bit) - Qt 5.5.1
 - Windows 7 x64 - Qt 5.5.1

# Build
    git clone https://github.com/toni1991/QtMqtt.git && cd QtMqtt
    mkdir build && cd build
    qmake ..
    make
    make install

Caution: The installation with 'make install' is only tested under GNU/Linux and may not work on other OS/target!

Under windows it's neccessary to copy the compiled files listed below to the directory ".../Qt/...qml/QmlQmqtt".
 - libQmlQmqtt.a
 - libQmlQmqttd.a
 - qmldir
 - QmlQmqtt.dll
 - QmlQmqttd.dll

# Qt/C++

## Example usage

```C++
#include "qmqtt.h"

[...]

QMQTT::Client client("localhost", 1883);
m_client->setClientId(m_clientId);
QObject::connect(client, &QMQTT::Client::received, this, messageReceived);
m_client->connect();

[...]

void QmlQmqtt::messageReceivedSlot(const QMQTT::Message &message)
{
    qDebug() << "Topic: " << arg.topic();
    qDebug() << "Payload: " << arg.payload();
}
```


## Signals
     - connected()
     - error(QAbstractSocket::SocketError)
     - connacked(quint8 ack)
     - published(QMQTT::Message &message)
     - pubacked(quint8 type, quint16 msgid)
     - received(const QMQTT::Message &message)
     - subscribed(const QString &topic)
     - subacked(quint16 mid, quint8 qos)
     - unsubscribed(const QString &topic)
     - unsubacked(quint16 mid)
     - pong()
     - disconnected()

## Slots
    - void onConnected()
    - void onDisconnected()
    - void onReceived(Frame & frame)
    - void handlePublish(Message &message)
    - void handleConnack(quint8 ack)
    - void handlePuback(quint8 type, quint16 msgid)

# QML Plugin
## Example usage

```QML
import QmlQmqtt 1.0
QmlQmqtt{
    id: qmlqmqtt
    host: "localhost"
    port: 1883
    onConnected: qmlqmqtt.subscribe("#")
    onMessageReceived: {
        console.log("topic:",topic)
        console.log("payload:",payload)
    }
    Component.onCompleted: qmlqmqtt.connect()
}
```

## Properties
    - bool autoReconnect
    - bool cleanSession
    - int keepalive
    - int port
    - QString clientId
    - QString host
    - QString password
    - QString username

## Signals
    - autoReconnectChanged(bool cleanSession)
    - cleanSessionChanged(bool cleanSession)
    - clientIdChanged(QString clientId)
    - connacked(quint8 ack)
    - connected()
    - disconnected()
    - error(QAbstractSocket::SocketError error)
    - hostChanged(QString host)
    - keepaliveChanged(int keepalive)
    - messageReceived(QString topic, QString payload)
    - passwordChanged(QString password)
    - pong()
    - portChanged(int port)
    - pubacked(quint8 type, quint16 msgid)
    - published(QMQTT::Message &message)
    - received(const QMQTT::Message &message)
    - subacked(quint16 mid, quint8 qos)
    - subscribed(const QString &topic)
    - unsubacked(quint16 mid)
    - unsubscribed(const QString &topic)
    - usernameChanged(QString username)

## Methods (Q_INVOCABLE)
    - bool isConnected()
    - quint16 publish(const QString& topic, const QString& payload, quint8 qos = 0)
    - quint16 publishMessageObject(QMQTT::Message &message)
    - quint16 subscribe(const QString& topic, quint8 qos = 0)
    - void connect()
    - void disconnect()
    - void ping()
    - void puback(quint8 type, quint16 msgid)
    - void unsubscribe(const QString& topic)
