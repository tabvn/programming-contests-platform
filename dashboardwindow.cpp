#include "dashboardwindow.h"
#include "ui_dashboardwindow.h"
#include <QTableView>
#include <QStringList>
#include <QTableWidgetItem>
#include <QtSql>
#include "contest.h"
#include <QVector>

/**
 *Get user score by problem
 * @brief getUserProblemScore
 * @param q
 * @param userId
 * @param problem
 * @return
 */
QVariant getUserProblemScore(QSqlQuery *q, QVariant userId, QString problem){


    if (!q->prepare("select score, accepted, error from submissions where status=1 AND userId=:userId AND problem=:problem order by score desc limit 1")){
        return -1;
    }
    q->bindValue(":userId", userId.toInt());
    q->bindValue(":problem", problem);

    q->exec();

    while(q->next()){

        return q->value(0);
    }

    return -1;
}

/**
 * Setup table view for scoreboard
 * @brief setupScoreTableView
 * @param table
 */
void setupScoreTableView(QTableWidget *table){

    QStringList headers = { "ID", "Name"};
    QStringList problems;
    QString problemName;
    QSqlQuery q;
    QVector<User> users;
    User user;

    q.exec("SELECT name FROM problems");

    while(q.next()){
        problemName = q.value(0).toString();
        headers.append(problemName);
        problems.append(problemName);
    }

    headers.append("Score");

    table->setColumnCount(headers.length());
    table->setHorizontalHeaderLabels(headers);
    table->setRowCount(10);
    table->setShowGrid(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    q.exec("select u.id, u.firstname, u.lastname from users as u inner join submissions as s on s.userId = u.id");


    int column = 0;
    int score;
    QVariant userProblemScore = -1;

    QVariant userId;

    while(q.next()){

         user.id = q.value(0).toInt();
         user.firstname = q.value(1).toString();
         user.lastname = q.value(2).toString();

         users.push_back(user);
    }

    for (int row = 0; row < users.size(); row++) {

        user = users[row];
        column = 0;

        table->setItem(row, 0, new QTableWidgetItem(QString::number(user.id)));

        table->setItem(row, 1, new QTableWidgetItem(user.lastname + " " + user.firstname));

        column = 2;
        score = 0;
        for (int i = 0; i < problems.size(); i++) {
           problemName = problems[i];
           userProblemScore = getUserProblemScore(&q, user.id, problemName);

           if(userProblemScore.toInt() > 0){
               score += userProblemScore.toInt();
               table->setItem(row, column, new QTableWidgetItem(userProblemScore.toString()));
           }

           column++;
        }

        table->setItem(row, column, new QTableWidgetItem(QString::number(score)));


    }

    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->resizeSection(1, 300);


}


DashboardWindow::DashboardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DashboardWindow)
{
    ui->setupUi(this);


    // setup scoreboard table
    setupScoreTableView(ui->scoreTableWidget);



}

DashboardWindow::~DashboardWindow()
{
    delete ui;
}


void DashboardWindow::on_actionQuit_2_triggered()
{
   close();
}
