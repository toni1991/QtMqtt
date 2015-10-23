#include "qmlqmqtt.h"
#include "qmqtt.h"
#include <QUuid>

// Constructor
QmlQmqtt::QmlQmqtt(QObject *parent) :
    QObject(parent),
    m_client(NULL),
    m_autoReconnect(true),
    m_cleanSession(true),
    m_keepalive(3000),
    m_port(1883),
    m_clientId(QString(QUuid::createUuid().toString())),
    m_host("localhost"),
    m_password(""),
    m_username("")
{
    // re-initialize client whenever the host or the port changes
    QObject::connect(this, &QmlQmqtt::hostChanged, this, &QmlQmqtt::initializeClient);
    QObject::connect(this, &QmlQmqtt::portChanged, this, &QmlQmqtt::initializeClient);

    // initialize client object
    initializeClient();
}

// Destructor
QmlQmqtt::~QmlQmqtt()
{
    if(clientAvailableAndConnected())
        m_client->disconnect();
    delete m_client;
}

// Q_PROPERTY READ Methods
bool QmlQmqtt::getAutoReconnect() const {
    return m_autoReconnect;
}

bool QmlQmqtt::getCleanSession() const {
    return m_cleanSession;
}

int QmlQmqtt::getKeepalive() const {
    return m_keepalive;
}

int QmlQmqtt::getPort() const {
    return m_port;
}

QString QmlQmqtt::getClientId() const {
    return m_clientId;
}

QString QmlQmqtt::getHost() const {
    return m_host;
}

QString QmlQmqtt::getPassword() const {
    return m_password;
}

QString QmlQmqtt::getUsername() const {
    return m_username;
}


// Q_PROPERTY WRITE Methods
void QmlQmqtt::setAutoReconnect(bool autoReconnect) {
    if(m_autoReconnect != autoReconnect){
        m_autoReconnect = autoReconnect;
        emit autoReconnectChanged(m_autoReconnect);
    }
}

void QmlQmqtt::setCleanSession(bool cleanSession) {
    if(m_cleanSession != cleanSession){
        m_cleanSession = cleanSession;
        emit cleanSessionChanged(m_cleanSession);
    }
}

void QmlQmqtt::setKeepalive(int keepalive) {
    if(m_keepalive != keepalive){
        m_keepalive = keepalive;
        emit keepaliveChanged(m_keepalive);
    }
}

void QmlQmqtt::setPort(int port) {
    if(m_port != port){
        m_port = port;
        emit portChanged(m_port);
    }
}

void QmlQmqtt::setClientId(QString clientId) {
    if(m_clientId != clientId){
        m_clientId = clientId;
        emit clientIdChanged(m_clientId);
    }
}

void QmlQmqtt::setHost(QString host)  {
    if(m_host != host){
        m_host = host;
        emit hostChanged(m_host);
    }
}

void QmlQmqtt::setPassword(QString password) {
    if(m_password != password){
        m_password = password;
        emit passwordChanged(m_password);
    }
}

void QmlQmqtt::setUsername(QString username) {
    if(m_username != username){
        m_username = username;
        emit usernameChanged(m_username);
    }
}

// Connection methods
void QmlQmqtt::connect() const {
    if(m_client != NULL)
    {
        m_client->connect();
    }
}

void QmlQmqtt::disconnect() const {
    if(m_client != NULL)
    {
        m_client->disconnect();
    }
}

bool QmlQmqtt::isConnected() const {
    if(m_client != NULL)
    {
        return m_client->isConnected();
    }

    return false;
}

void QmlQmqtt::ping() const {
    if(m_client != NULL)
    {
        m_client->ping();
    }
}

void QmlQmqtt::puback(quint8 type, quint16 msgid) const
{
    if(m_client != NULL)
    {
        m_client->puback(type, msgid);
    }
}

// Publish methods
quint16 QmlQmqtt::publishMessageObject(QMQTT::Message &message) const {
    if(clientAvailableAndConnected() &&
            !message.topic().isEmpty() &&
            !message.payload().isEmpty())
    {
        return m_client->publish(message);
    }
    return 0;
}

quint16 QmlQmqtt::publish(const QString& topic, const QString& payload, quint8 qos) const {
    QMQTT::Message message;
    message.setTopic(topic);
    message.setPayload(payload.toUtf8());
    message.setQos(qos);
    return this->publishMessageObject(message);
}

// Subscription methods
quint16 QmlQmqtt::subscribe(const QString& topic, quint8 qos)  const{
    if(clientAvailableAndConnected())
    {
        return m_client->subscribe(topic, qos);
    }
    return 0;
}

void QmlQmqtt::unsubscribe(const QString& topic)  const{
    if(clientAvailableAndConnected())
    {
        m_client->unsubscribe(topic);
    }
}

// Slots
void QmlQmqtt::messageReceivedSlot(const QMQTT::Message &arg)
{
    emit messageReceived(arg.topic(), arg.payload());
}

void QmlQmqtt::initializeClient() {

    if(m_client != NULL)
    {
        delete m_client;
        m_client = NULL;
    }

    if(m_host.isEmpty() || !m_port)
    {
        qDebug() << "Hostname (" << m_host << ") or port (" << m_port << ") invalid!";
        return;
    }

    m_client = new QMQTT::Client(m_host, m_port);
    m_client->setClientId(m_clientId);
    m_client->setAutoReconnect(m_autoReconnect);
    m_client->setCleansess(m_cleanSession);
    m_client->setKeepAlive(m_keepalive);
    m_client->setPassword(m_password);
    m_client->setUsername(m_username);

    if(!m_username.isEmpty())
        m_client->setUsername(m_username);
    if(!m_password.isEmpty())
        m_client->setPassword(m_password);

    connectClientSignals();
}

void QmlQmqtt::connectClientSignals() const
{
    if(m_client == NULL)
        return;

    // Connect Pass-through signals
    QObject::connect(m_client, &QMQTT::Client::connacked, this, &QmlQmqtt::connacked);
    QObject::connect(m_client, &QMQTT::Client::connected, this, &QmlQmqtt::connected);
    QObject::connect(m_client, &QMQTT::Client::disconnected, this, &QmlQmqtt::disconnected);
    QObject::connect(m_client, &QMQTT::Client::error, this, &QmlQmqtt::error);
    QObject::connect(m_client, &QMQTT::Client::pong, this, &QmlQmqtt::pong);
    QObject::connect(m_client, &QMQTT::Client::pubacked, this, &QmlQmqtt::pubacked);
    QObject::connect(m_client, &QMQTT::Client::published, this, &QmlQmqtt::published);
    QObject::connect(m_client, &QMQTT::Client::received, this, &QmlQmqtt::received);
    QObject::connect(m_client, &QMQTT::Client::subacked, this, &QmlQmqtt::subacked);
    QObject::connect(m_client, &QMQTT::Client::subscribed, this, &QmlQmqtt::subscribed);
    QObject::connect(m_client, &QMQTT::Client::unsubacked, this, &QmlQmqtt::unsubacked);
    QObject::connect(m_client, &QMQTT::Client::unsubscribed, this, &QmlQmqtt::unsubscribed);

    // Connect set signals
    QObject::connect(this, &QmlQmqtt::autoReconnectChanged, m_client, &QMQTT::Client::setAutoReconnect);
    QObject::connect(this, &QmlQmqtt::cleanSessionChanged, m_client, &QMQTT::Client::setCleansess);
    QObject::connect(this, &QmlQmqtt::keepaliveChanged, m_client, &QMQTT::Client::setKeepAlive);
    QObject::connect(this, &QmlQmqtt::portChanged, m_client, &QMQTT::Client::setPort);
    QObject::connect(this, &QmlQmqtt::clientIdChanged, m_client, &QMQTT::Client::setClientId);
    QObject::connect(this, &QmlQmqtt::hostChanged, m_client, &QMQTT::Client::setHost);
    QObject::connect(this, &QmlQmqtt::passwordChanged, m_client, &QMQTT::Client::setPassword);
    QObject::connect(this, &QmlQmqtt::usernameChanged, m_client, &QMQTT::Client::setUsername);

    // Connect custom signals
    QObject::connect(m_client, &QMQTT::Client::received, this, &QmlQmqtt::messageReceivedSlot);
}

// Private Methods
bool QmlQmqtt::clientAvailableAndConnected() const
{
    if(m_client != NULL)
    {
        return m_client->isConnected();
    }
    return false;
}
