#include "json_objects.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

JSON_Objects::JSON_Objects()
{
    //QString filename = "json_files/use_iocontrol.json";
    //qDebug() << readJsonFile(filename);
    //qDebug() << createJsonGateEvent(1000);
}

//Reads the json document and returns a QString with its content
QString JSON_Objects::readJsonFile(const QString &filename){
    QString val;
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    return val;
}

QString JSON_Objects::createJsonGateEvent(int nUII){
    //fills RSVAG array with the given values
    QJsonArray RSVAG_Array;
    RSVAG_Array.push_back(-70);
    RSVAG_Array.push_back(0);
    RSVAG_Array.push_back(0);
    RSVAG_Array.push_back(0);

    QJsonArray tagsArray;
    QJsonObject qObj;
    qObj.insert("RSVAG", RSVAG_Array);

    QString qsUII = QString::number(nUII);
    qObj.insert("UII", qsUII);
    tagsArray.push_back(qObj);

    //Creates top level json object
    QJsonObject gateEventObj;
    gateEventObj.insert("jsonrpc", "2.0");
    gateEventObj.insert("method", "gateEvent");

    QJsonObject paramsObj;
    paramsObj.insert("readType", "goodRead");
    paramsObj.insert("tags", tagsArray);
    gateEventObj.insert("params", paramsObj);

    QJsonDocument doc(gateEventObj);
    QString result(doc.toJson(QJsonDocument::Compact));
    return result;
}

QString JSON_Objects::getFn_connEstablished() const
{
    return fn_connEstablished;
}

QString JSON_Objects::getFn_gateEvent() const
{
    return fn_gateEvent;
}

QString JSON_Objects::getFn_dir() const
{
    return fn_dir;
}

