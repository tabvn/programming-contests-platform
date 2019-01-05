#include <QApplication>
#include <QtWidgets>
#include "connection.h"
#include "dashboardwindow.h"

int main(int argc, char *argv[])
{

     QApplication a( argc, argv );

    if (!createConnection()){
        return EXIT_FAILURE;
    }

    DashboardWindow dash;

    dash.show();

    return a.exec();
}
