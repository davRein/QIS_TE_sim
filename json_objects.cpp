#include "json_objects.h"


//! [constructor]
//! Creates an JSON_Objects object
JSON_Objects::JSON_Objects()
{

}
//! [constructor]

//! [readJsonFile]
//! Opens and reads a JSON file
QString JSON_Objects::readJsonFile(const QString &filename){
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();
    return val;
}
//! [readJsonFile]

//! [createJsonGateEvent]
//! Creates a gateEvent with a given UII
//! @param nUII: Transponder ID (randomly generated
//! @returns a JSON gateEvent as QString
QString JSON_Objects::createJsonGateEvent(int nUII){
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
//! [createJsonGateEvent]

//! [checkJsonMessage]
//! Checks the incoming message and sends the anwer back to the server
//! @param message: json file message
//! @param socket: QWebSocket socket, to answer to the client
void JSON_Objects::checkJsonMessage(QString &message, QWebSocket &socket)
{
    QTime time;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject rootObj = doc.object();
    if(rootObj.find("method").value().operator==("use")){
        if(rootObj["params"].toObject().find("app").value().operator==("iocontrol")){
            if(m_debug){
                qDebug() << "Connection to iocontrol at " << time.currentTime();
            }

            socket.sendTextMessage(readJsonFile(fn_dir + fn_connEstablished));
        } else if(rootObj["params"].toObject().find("app").value().operator==("gate")){
            if(m_debug){
                qDebug() << "Connection to gate at " << time.currentTime() << "\n";
            }
            socket.sendTextMessage(readJsonFile(fn_dir + fn_connEstablished));
        }
    } else if(rootObj.find("method").value() == "setOutput"){
        readSetOutput(message);
        socket.sendTextMessage(readJsonFile(fn_dir + fn_resultTrue));
    } else {
        if(m_debug){
            qDebug() << "Unknown JSON protocol";
        }
    }
}
//! [checkJsonMessage]

//! [readSetOutput]
//! Reads the setOutput JSON object and prints out the result
//! @param message: a JSON message as QString
void JSON_Objects::readSetOutput(QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject rootObj = doc.object();
    QString value, name = "";
    value = rootObj["params"].toObject().find("value").value().toString();
    name = rootObj["params"].toObject().find("name").value().toString();

    if(name.compare("red") == 0){
        qDebug() << name.toUpper() << "\t\t : " << value;
        qDebug() << "----------------------------------------\n";
    } else {
        qDebug() << name.toUpper() << "\t : " << value;
    }
}
//! [readSetOutput]
