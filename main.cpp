#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "ws_server.h"

//! [main] the main ...
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bool debug = false;
    int port = 1234;

    WS_Server *server = new WS_Server(port, debug);
    QObject::connect(server, &WS_Server::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
