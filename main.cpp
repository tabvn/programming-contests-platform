#include <QApplication>
#include <QtWidgets>
#include "dashboardwindow.h"

#include <QApplication>
#include <QFileOpenEvent>
#include <QtDebug>
#include "server.h"
#include "contest.h"
#include "judge.h"

using namespace Ued;

int main(int argc, char *argv[])
{

    QApplication a( argc, argv );

    Contest *c = new Contest();
    Server *s = new Server(c);
    s->start();

    Judge *j = new Judge(c);
    j->start();

    DashboardWindow *dash = new DashboardWindow(nullptr, c, s, j);
    dash->show();

    return a.exec();


}
