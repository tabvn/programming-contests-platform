#include <QApplication>
#include <QtWidgets>
#include "dashboardwindow.h"
#include "server.h"


int main(int argc, char *argv[])
{


    QApplication a( argc, argv );

    DashboardWindow dash;
    dash.show();

    Server *server = new Server(8080, false);
    QObject::connect(server, &Server::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
