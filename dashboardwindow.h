#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QMainWindow>
#include "contest.h"

namespace Ui {
class DashboardWindow;
}

class DashboardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DashboardWindow(QWidget *parent = nullptr);
    ~DashboardWindow();

private slots:


    void on_actionQuit_2_triggered();

private:
    Ui::DashboardWindow *ui;
    Contest *contest;

};

#endif // DASHBOARDWINDOW_H
