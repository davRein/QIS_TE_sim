#ifndef JSON_OBJECTS_H
#define JSON_OBJECTS_H

#include <QString>
#include <QFile>

class JSON_Objects
{
public:
    JSON_Objects();

    QString readJsonFile(const QString &filename);
    QString createJsonGateEvent(int nUII);
    QString getFn_connEstablished() const;
    QString getFn_gateEvent() const;
    QString getFn_dir() const;

private:
    QFile file;

    const QString fn_dir = "json_files/";

    const QString fn_connEstablished = "id_0_result_ok.json";
    const QString fn_gateEvent = "gateEvent.json";
};

#endif // JSON_OBJECTS_H
