#ifndef JSON_OBJECTS_H
#define JSON_OBJECTS_H

#include <QString>
#include <QFile>
#include <QWebSocket>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class JSON_Objects
{
public:
    JSON_Objects();

    QString readJsonFile(const QString &filename);
    QString createJsonGateEvent(int nUII);
    void checkJsonMessage(QString &message, QWebSocket &socket);
    void readSetOutput(QString &message);

private:
    const QString fn_dir = "json_files/";
    const QString fn_connEstablished = "id_0_result_ok.json";
    const QString fn_gateEvent = "gateEvent.json";
    const QString fn_resultTrue = "id_1_result_true.json";

    bool m_debug = false;
};

#endif // JSON_OBJECTS_H
