#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QMainWindow>
#include "contest.h"
#include <QtWidgets>
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
    void on_userTableWidget_itemChanged(QTableWidgetItem *item);
    void slotRemoveRecord();
    void slotCustomMenuRequested(QPoint pos);


    void on_problemComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::DashboardWindow *ui;
    Contest *contest;
    QString selectedProblem;

};

#endif // DASHBOARDWINDOW_H
