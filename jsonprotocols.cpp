#include "jsonprotocols.h"

JsonProtocols::JsonProtocols(QObject *parent) : QObject(parent)
{

}

QString JsonProtocols::createJson_method_use_IO_COntrol_result_OK(int &nId)
{
    QJsonObject rootObj;
    rootObj.insert("id", nId);
    rootObj.insert("jsonrpc", "2.0");
    rootObj.insert("result", "OK");

    QJsonDocument doc(rootObj);
    QString result(doc.toJson(QJsonDocument::Compact));

    return result;
}

QString JsonProtocols::createJson_method_setOutput_result_true(int &nId, bool &fResult)
{
    QJsonObject rootObj;
    rootObj.insert("id", nId);
    rootObj.insert("jsonrpc", "2.0");
    rootObj.insert("result", fResult);

    QJsonDocument doc(rootObj);
    QString result(doc.toJson(QJsonDocument::Compact));

    return result;
}

QString JsonProtocols::createJson_method_use_gate_result_OK(int &nId)
{
    QJsonObject rootObj;
    rootObj.insert("id", nId);
    rootObj.insert("jsonrpc", "2.0");
    rootObj.insert("result", "OK");

    QJsonDocument doc(rootObj);
    QString result(doc.toJson(QJsonDocument::Compact));

    return result;
}

QString JsonProtocols::createJson_method_gateEvent(QString &readType, int &nUII)
{
    QJsonArray RSVAG_Array;
    RSVAG_Array.push_back(-70);
    RSVAG_Array.push_back(0);
    RSVAG_Array.push_back(0);
    RSVAG_Array.push_back(0);

    QJsonArray tagsArray;
    QJsonObject tagsObj;
    tagsObj.insert("RSVAG", RSVAG_Array);

    QString strUii = QString::number(nUII);
    tagsObj.insert("UII", strUii);
    tagsArray.push_back(tagsObj);

    QJsonObject rootObj;
    rootObj.insert("jsonrpc", "2.0");
    rootObj.insert("method", "gateEvent");

    QJsonObject paramsObj;
    paramsObj.insert("readType", readType);
    paramsObj.insert("tags", tagsArray);
    rootObj.insert("params", paramsObj);

    QJsonDocument doc(rootObj);
    QString result(doc.toJson(QJsonDocument::Compact));

    return result;
}
























