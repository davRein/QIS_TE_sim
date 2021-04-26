#include "ws_server.h"


QT_USE_NAMESPACE

//! [Constructor]
//! Creates an object to open websocket connections
//! @param port: Port on which the server can be addressed
//! @param debug: toggle true/false for debug output
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

//! [destructor]
//! Don't call it manually, everytime you do a unicorn will die. It may be the last !
WS_Server::~WS_Server()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}
//! [destructor]

//! [onNewConnection]
//! Puts connected clients to thee client list and enables communicatione between server and client
void WS_Server::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WS_Server::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WS_Server::socketDisconnected);

    m_clients << pSocket;

    // Some debugging output for fun
    int iClients = m_clients.size();

    if(iClients < 2){
        QTimer *timer = new QTimer(this);
        timer->setInterval(3000);
        connect(timer, &QTimer::timeout, this, &WS_Server::processTimeout);
        // Start timer, timeout is 3 sec
        timer->start(3000);
    }
}
//! [onNewConnection]

//! [processTextMessage]
//! Receives incoming messages and check their content to decide which method to be call as next
//! @param message: Sent message(s) from the client
void WS_Server::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    obj.checkJsonMessage(message, *pClient);
}
//! [processTextMessage]


//! [socketDisconnected]
//! Disconnects the websocket
void WS_Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug){
        qDebug() << "socketDisconnected:" << pClient;
    }
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
//! [socketDisconnected]


//! [processTimeout]
//! Generates every 3 sec a gateEvent with a random UII between 1 und 3000
void WS_Server::processTimeout() {
    if(m_clients.isEmpty()){
        m_pWebSocketServer->disconnect();
    }
    if(!m_clients.isEmpty()) {
      QWebSocket *pID_Check = m_clients.first();
      if (pID_Check) {
          nCounter++;
          pID_Check->sendTextMessage(obj.createJsonGateEvent((rand() % 3000 + 1)));
        }
    }
}
//! [processTimeout]
