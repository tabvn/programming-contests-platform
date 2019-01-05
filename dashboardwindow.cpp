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
void setupScoreTableView(QSqlQuery *q,QTableWidget *table, Contest *contest){

    QStringList headers = { "ID", "Name"};
    QStringList problems;
    QString problemName;


    User user;

    q->exec("SELECT name FROM problems");

    while(q->next()){
        problemName = q->value(0).toString();
        headers.append(problemName);
        problems.append(problemName);
    }

    headers.append("Score");

    table->setColumnCount(headers.length());
    table->setHorizontalHeaderLabels(headers);

    int column = 0;
    int score;
    QVariant userProblemScore = -1;
    QVariant userId;

    QVector<User> users = contest->getScoreboardUsers();
    table->setRowCount(users.size());
    for (int row = 0; row < users.size(); row++) {

        user = users[row];
        column = 0;

        table->setItem(row, 0, new QTableWidgetItem(QString::number(user.id)));

        table->setItem(row, 1, new QTableWidgetItem(user.lastname + " " + user.firstname));

        column = 2;
        score = 0;
        for (int i = 0; i < problems.size(); i++) {
           problemName = problems[i];
           userProblemScore = getUserProblemScore(q, user.id, problemName);

           if(userProblemScore.toInt() > 0){
               score += userProblemScore.toInt();
               table->setItem(row, column, new QTableWidgetItem(userProblemScore.toString()));
           }

           column++;
        }

        table->setItem(row, column, new QTableWidgetItem(QString::number(score)));


    }

    table->setShowGrid(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->resizeSection(1, 300);


}


void setupUserTableView(QSqlQuery *q, QTableWidget *table, Contest *contest){

    QVector<User> users = contest->getUsers();
    User user;


    QStringList headers = {"ID", "Class", "First name", "Last name", "Birthday", "Email", "Password"};

    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->setRowCount(users.size() + 1);


    for (int row = 0; row < users.size(); row++) {
        user = users[row];
        table->setItem(row, 0, new QTableWidgetItem(QString::number(user.id)));
        table->setItem(row, 1, new QTableWidgetItem(user.className));
        table->setItem(row, 2, new QTableWidgetItem(user.firstname));
        table->setItem(row, 3, new QTableWidgetItem(user.lastname));
        table->setItem(row, 4, new QTableWidgetItem(user.birthday.toString("dd/MM/yyyy")));
        table->setItem(row, 5, new QTableWidgetItem(user.email));
        table->setItem(row, 6, new QTableWidgetItem(user.password));
    }



    table->horizontalHeader()->setStretchLastSection(true);



}


DashboardWindow::DashboardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DashboardWindow)
{
    ui->setupUi(this);

    QSqlQuery q;
    this->contest = new Contest();

    // setup scoreboard table
    setupScoreTableView(&q, ui->scoreTableWidget, this->contest);
    setupUserTableView(&q, ui->userTableWidget, this->contest);

   // show first tab
    ui->tabWidget->setCurrentIndex(0);


}

DashboardWindow::~DashboardWindow()
{
    delete ui;
}


void DashboardWindow::on_actionQuit_2_triggered()
{
   close();
}
