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
    void slotCustomMenuRequestedTestCaseTable(QPoint pos);
    void slotRemoveTestCaseTableItem();

    void on_maxScoreTextField_editingFinished();

    void on_problemTextField_editingFinished();

    void on_memoryLimitTextField_editingFinished();

    void on_descriptionTextField_textChanged();

    void on_deleteProblemButton_clicked();

    void on_timelimitTextField_editingFinished();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();
    void on_problemComboBox_currentTextChanged(const QString &arg1);


    void on_actionNew_Contest_triggered();

    void on_addTestCaseBtn_clicked();

    void on_testcaseTableWidget_itemSelectionChanged();

    void on_deleteTestCaseBtn_clicked();

    void on_testcaseTableWidget_cellChanged(int row, int column);



    void on_inputTestCaseTextField_textChanged();

    void on_outputTestCaseTextField_textChanged();

private:

    Ui::DashboardWindow *ui;
    Contest *contest;

};

#endif // DASHBOARDWINDOW_H
