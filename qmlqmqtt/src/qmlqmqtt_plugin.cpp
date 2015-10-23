#include "qmlqmqtt_plugin.h"
#include "qmlqmqtt.h"

#include <qqml.h>

void QmlQmqttPlugin::registerTypes(const char *uri)
{
    // @uri QmlQmqtt
    qmlRegisterType<QmlQmqtt>(uri, 1, 0, "QmlQmqtt");
}


