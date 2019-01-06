#include <QApplication>
#include <QtWidgets>
#include "dashboardwindow.h"
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );
    DashboardWindow dash;
    dash.show();

    bool debug = true;
    int port = 8080;

    Server *server = new Server(port, debug);
    QObject::connect(server, &Server::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
