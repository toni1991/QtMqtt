#ifndef QMLQMQTT_PLUGIN_H
#define QMLQMQTT_PLUGIN_H

#include <QQmlExtensionPlugin>

class QmlQmqttPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "QmlQmqtt")

public:
    void registerTypes(const char *uri);
};

#endif // QMLQMQTT_PLUGIN_H

