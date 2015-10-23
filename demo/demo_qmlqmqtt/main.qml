import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QmlQmqtt 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("QmlQmqtt Demo")

    QmlQmqtt {
        id: qmlQmqtt
        cleanSession: false
        onDisconnected: {
            textArea.text = textArea.text +
                    "\n" +
                    "Disconnected..."
        }
        onConnected: {
            textArea.text = textArea.text +
                    "\n" +
                    "Connected..."
        }
        onMessageReceived: {
            textArea.text = textArea.text +
                    "\n" +
                    "Message received. Topic: " +
                    topic +
                    " | Payload: " +
                    payload
        }
        onSubscribed: {
            textArea.text = textArea.text +
                    "\n" +
                    "Subscribed. Topic: " +
                    topic
        }
        onUnsubscribed: {
            textArea.text = textArea.text +
                    "\n" +
                    "Unsubscribed. Topic: " +
                    topic
        }
    }

    TabView{
        id: tabView
        width: parent.width
        height: parent.height / 3
        Tab{
            title: "Connection"
            Grid{
                columns: 2
                spacing: height * 0.1
                Text{
                    text: "Host"
                }
                TextField{
                    id: connectionHost
                    text: "192.168.1.119"
                }
                Text{
                    text: "Port"
                }
                TextField{
                    id: connectionPort
                    text: "1883"
                }
                Button{
                    id: connectButton
                    text: "Connect"
                    onClicked: {
                        if(qmlQmqtt.isConnected())
                        {
                            qmlQmqtt.disconnect()
                            connectButton.text =  "Connect"
                        }
                        else
                        {
                            Qt.inputMethod.hide();
                            if(connectionHost.text && connectionPort.text)
                            {
                                qmlQmqtt.host = connectionHost.text
                                qmlQmqtt.port = connectionPort.text
                                qmlQmqtt.connect()
                                connectButton.text =  "Disonnect"
                            }
                        }
                    }
                }
            }
        }
        Tab{
            title: "Subscription"
            Grid{
                columns: 2
                spacing: height * 0.1
                Text{
                    text: "Topic"
                }
                TextField{
                    id: subscriptionTopic
                    text: "#"
                }
                Button{
                    text: "Subscribe"
                    onClicked: qmlQmqtt.subscribe(subscriptionTopic.text)
                }
                Button{
                    text: "Unsubscribe"
                    onClicked: qmlQmqtt.unsubscribe(subscriptionTopic.text)
                }
            }
        }
        Tab{
            title: "Publish"
            Grid{
                columns: 2
                spacing: height * 0.1
                Text{
                    text: "Topic"
                }
                TextField{
                    id: publishTopic
                    text: "topic"
                }
                Text{
                    text: "Payload"
                }
                TextField{
                    id: publishPayload
                    text: "payload"
                }
                Button{
                    text: "Publish"
                    onClicked: qmlQmqtt.publish(publishTopic.text, publishPayload.text)
                    Layout.fillWidth: true
                    Layout.columnSpan: 2
                }
            }
        }
    }
    TextArea{
        id: textArea
        width: parent.width
        height: parent.height -tabView.height
        anchors.top: tabView.bottom
        text: "Started..."
    }
}
