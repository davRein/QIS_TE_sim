#ifndef WS_SERVER_H
#define WS_SERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <QTimer>
#include "json_objects.h"
#include "jsonprotocols.h"


QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class WS_Server : public QObject
{
    Q_OBJECT
public:
    explicit WS_Server(quint16 port, bool debug = false, QObject *parent = nullptr);
    ~WS_Server();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void socketDisconnected();
    void processTimeout();

private:
    QWebSocket *messageSocket;
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug = false;
    bool connGateEstablished;
    int nCounter;
    JSON_Objects obj;
    JsonProtocols protocols;
    QString readType = "goodRead";
};
#endif // WS_SERVER_H
