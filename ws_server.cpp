#include "ws_server.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <QTimer>

QT_USE_NAMESPACE

WS_Server::WS_Server(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug){
            qDebug() << "Server listening on port" << port;
        }
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &WS_Server::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WS_Server::closed);


    }
}
//! [constructor]

WS_Server::~WS_Server()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

//! [onNewConnection]
void WS_Server::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WS_Server::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WS_Server::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WS_Server::socketDisconnected);

    m_clients << pSocket;

    // Some debugging output for fun
    int iClients = m_clients.size();

    if(iClients < 2){

        qDebug() << "Timer starts";
        QTimer *timer = new QTimer(this);
        timer->setInterval(2000);
        connect(timer, &QTimer::timeout, this, &WS_Server::processTimeout);
        // Start timer, timeout is 5 sec
        timer->start(2000);
    }
}
//! [onNewConnection]

//! [processTextMessage]
void WS_Server::processTextMessage(QString message)
{

    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (!m_debug)
        qDebug() << "Message received:" << message;

    if(message.contains("gate")){
        pClient->sendTextMessage(obj.readJsonFile(obj.getFn_dir() + obj.getFn_connEstablished()));
        connGateEstablished = true;
        QTime t = QTime::currentTime();
        qDebug() << "Connection to Dummy Gate App established at " + t.toString();
    } else if(message.contains("iocontrol")){
        pClient->sendTextMessage(obj.readJsonFile(obj.getFn_dir() + obj.getFn_connEstablished()));
        connGateEstablished = true;
        QTime t = QTime::currentTime();
        qDebug() << "Connection to Dummy IO-Control established at " + t.toString();
    }
}
//! [processTextMessage]

//! [processBinaryMessage]
void WS_Server::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}
//! [processBinaryMessage]

//! [socketDisconnected]
void WS_Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
//! [socketDisconnected]


//! [processTimeout]
void WS_Server::processTimeout() {
    if(m_clients.isEmpty()){
        m_pWebSocketServer->disconnect();
    }
    if(!m_clients.isEmpty()) {
      QWebSocket *pID_Check = m_clients.first();
      if (pID_Check) {
          nCounter++;
          qDebug() << "Sent";
          pID_Check->sendTextMessage(obj.createJsonGateEvent((rand() % 3000 + 1)));
        }
    }
}
//! [processTimeout]
