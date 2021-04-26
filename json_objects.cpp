#include "json_objects.h"


//! [constructor]
//! Creates an JSON_Objects object
JSON_Objects::JSON_Objects()
{

}
//! [constructor]


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
            socket.sendTextMessage(protocols.createJson_method_use_IO_COntrol_result_OK(nTmp));
            //socket.sendTextMessage(readJsonFile(fn_dir + fn_connEstablished));
        } else if(rootObj["params"].toObject().find("app").value().operator==("gate")){
            if(m_debug){
                qDebug() << "Connection to gate at " << time.currentTime() << "\n";
            }
            socket.sendTextMessage(protocols.createJson_method_use_gate_result_OK(nTmp));
            //socket.sendTextMessage(readJsonFile(fn_dir + fn_connEstablished));
        }
    } else if(rootObj.find("method").value() == "setOutput"){
        readSetOutput(message);
        socket.sendTextMessage(protocols.createJson_method_setOutput_result_true(nTmp, fResult));
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
