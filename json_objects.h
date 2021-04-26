#ifndef JSON_OBJECTS_H
#define JSON_OBJECTS_H

#include <QString>
#include <QFile>
#include <QWebSocket>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "jsonprotocols.h"

class JSON_Objects
{
public:
    JSON_Objects();

    QString readJsonFile(const QString &filename);
    QString createJsonGateEvent(int nUII);
    void checkJsonMessage(QString &message, QWebSocket &socket);
    void readSetOutput(QString &message);

private:
    bool m_debug = false;
    JsonProtocols protocols;

    // TMP
    int nTmp = 1;
    bool fResult = true;
};

#endif // JSON_OBJECTS_H
