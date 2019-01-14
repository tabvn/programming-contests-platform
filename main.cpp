#include <QApplication>
#include <QtWidgets>
#include "dashboardwindow.h"

#include <QApplication>
#include <QFileOpenEvent>
#include <QtDebug>
#include "server.h"
#include "contest.h"

int main(int argc, char *argv[])
{

    QApplication a( argc, argv );

    Contest *c = new Contest();


    DashboardWindow dash(nullptr, c);
    dash.show();

    Server s(c);
    s.start();


    return a.exec();


}
