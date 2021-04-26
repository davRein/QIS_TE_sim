#ifndef JSONPROTOCOLS_H
#define JSONPROTOCOLS_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

class JsonProtocols : public QObject
{
    Q_OBJECT
public:
    explicit JsonProtocols(QObject *parent = nullptr);

    QString createJson_method_use_IO_COntrol_result_OK(int &nId);
    QString createJson_method_setOutput_result_true(int &nId, bool &fResult);
    QString createJson_method_use_gate_result_OK(int &nId);
    QString createJson_method_gateEvent(QString &readType, int &nUII);
signals:

};

#endif // JSONPROTOCOLS_H
