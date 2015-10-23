#ifndef QMLQMQTT__H
#define QMLQMQTT__H

#include <QObject>
#include "qmqtt.h"

class QmlQmqtt : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool autoReconnect READ getAutoReconnect WRITE setAutoReconnect NOTIFY autoReconnectChanged)
    Q_PROPERTY(bool cleanSession READ getCleanSession WRITE setCleanSession NOTIFY cleanSessionChanged)
    Q_PROPERTY(int keepalive READ getKeepalive WRITE setKeepalive NOTIFY keepaliveChanged)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString clientId READ getClientId WRITE setClientId NOTIFY clientIdChanged)
    Q_PROPERTY(QString host READ getHost WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)

public:
    explicit QmlQmqtt(QObject *parent = 0);
    ~QmlQmqtt();

    // Q_PROPERTY READ Methods
    bool getAutoReconnect() const;
    bool getCleanSession() const;
    int getKeepalive() const;
    int getPort() const;
    QString getClientId() const;
    QString getHost() const;
    QString getPassword() const;
    QString getUsername() const;

    // Q_PROPERTY WRITE Methods
    void setAutoReconnect(bool autoReconnect);
    void setCleanSession(bool cleanSession);
    void setKeepalive(int keepalive);
    void setPort(int port);
    void setClientId(QString clientId);
    void setHost(QString host);
    void setPassword(QString password);
    void setUsername(QString username);

    // Connection methods
    Q_INVOKABLE void connect() const;
    Q_INVOKABLE void disconnect() const;
    Q_INVOKABLE bool isConnected() const;
    Q_INVOKABLE void ping() const;
    Q_INVOKABLE void puback(quint8 type, quint16 msgid) const;

    // Publish methods
    Q_INVOKABLE quint16 publishMessageObject(QMQTT::Message &message) const;
    Q_INVOKABLE quint16 publish(const QString& topic, const QString& payload, quint8 qos = 0) const;

    // Subscription methods
    Q_INVOKABLE quint16 subscribe(const QString& topic, quint8 qos = 0) const;
    Q_INVOKABLE void unsubscribe(const QString& topic) const;

signals:
    // Q_PROPERTY NOTIFY Signals
    void autoReconnectChanged(bool cleanSession);
    void cleanSessionChanged(bool cleanSession);
    void keepaliveChanged(int keepalive);
    void portChanged(int port);
    void clientIdChanged(QString clientId);
    void hostChanged(QString host);
    void passwordChanged(QString password);
    void usernameChanged(QString username);

    // Pass-through signals
    void connacked(quint8 ack);
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError error);
    void pong();
    void pubacked(quint8 type, quint16 msgid);
    void published(QMQTT::Message &message);
    void received(const QMQTT::Message &message);
    void subacked(quint16 mid, quint8 qos);
    void subscribed(const QString &topic);
    void unsubacked(quint16 mid);
    void unsubscribed(const QString &topic);

    // Custom signals
    void messageReceived(QString topic, QString payload);

private slots:
    void messageReceivedSlot(const QMQTT::Message &arg);
    void initializeClient();

private:
    void connectClientSignals() const;
    bool clientAvailableAndConnected() const;

    QMQTT::Client *m_client;

    bool m_autoReconnect;
    bool m_cleanSession;
    int m_keepalive;
    int m_port;
    QString m_clientId;
    QString m_host;
    QString m_password;
    QString m_username;
};

#endif // QMLQMQTT__H
