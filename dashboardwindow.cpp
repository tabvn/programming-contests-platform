#include "dashboardwindow.h"
#include "ui_dashboardwindow.h"
#include <QTableView>
#include <QStringList>
#include <QTableWidgetItem>
#include <QtSql>
#include "contest.h"
#include <QVector>
#include <QMessageBox>
#include <QSqlTableModel>

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



    QStringList headers = {"ID", "Class", "First name", "Last name", "Birthday", "Email", "Password"};

    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->setRowCount(users.size() + 1);



    for (int row = 0; row < users.size(); row++) {

        table->setItem(row, 0, new QTableWidgetItem(QString::number(users[row].id)));
        table->setItem(row, 1, new QTableWidgetItem(users[row].className));
        table->setItem(row, 2, new QTableWidgetItem(users[row].firstname));
        table->setItem(row, 3, new QTableWidgetItem(users[row].lastname));
        table->setItem(row, 4, new QTableWidgetItem(users[row].birthday.toString("dd/MM/yyyy")));
        table->setItem(row, 5, new QTableWidgetItem(users[row].email));
        table->setItem(row, 6, new QTableWidgetItem(users[row].password));

    }



    table->horizontalHeader()->setStretchLastSection(true);


}

void setupProblemListComboBox(QComboBox *box, Contest *contest){

    QVector<Problem> problems = contest->getProblems();

    box->clear();

    for (int i = 0; i < problems.size(); i++) {
        box->addItem(problems[i].name);
    }



    box->addItem("+ New problem");

}

void setupProblemDetails(Ui::DashboardWindow *ui, Problem *problem){
    if(problem == nullptr){
        return;
    }

    ui->problemTextField->setText(problem->name);

}

DashboardWindow::DashboardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DashboardWindow)
{

    ui->setupUi(this);

    this->ui->userTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->userTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));



    QSqlQuery q;
    this->contest = new Contest();

    // setup scoreboard table
    setupScoreTableView(&q, ui->scoreTableWidget, this->contest);
    setupUserTableView(&q, ui->userTableWidget, this->contest);
    setupProblemListComboBox(ui->problemComboBox, contest);


    setupProblemDetails(ui, this->selectedProblem);


   // show first tab
    ui->tabWidget->setCurrentIndex(0);


}

void DashboardWindow::slotCustomMenuRequested(QPoint pos)
{

    QMenu * menu = new QMenu(this);

    QAction * deleteDevice = new QAction(trUtf8("Delete"), this);

    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(slotRemoveRecord())); // Handler delete records

    ui->userTableWidget->selectRow(ui->userTableWidget->currentRow());
    menu->addAction(deleteDevice);

   menu->popup(ui->userTableWidget->viewport()->mapToGlobal(pos));

}

void DashboardWindow::slotRemoveRecord()
{

    int row = ui->userTableWidget->selectionModel()->currentIndex().row();

    if(row >= 0){
        if(row < this->contest->users.size()){
            if (contest->removeUser(&this->contest->users[row])){
                this->contest->users.removeAt(row);
                ui->userTableWidget->removeRow(row);
                QModelIndex next_index = ui->userTableWidget->model()->index(row -1, 0);
                ui->userTableWidget->setCurrentIndex(next_index);
            }

        }
    }
}


DashboardWindow::~DashboardWindow()
{
    delete ui;
}


void DashboardWindow::on_actionQuit_2_triggered()
{
   close();
}

void setUserDataByColumnIndex(User *user, int column, QString value){

    switch (column) {
    case 0: {
        if(!value.isNull() && !value.isEmpty()){
            user->id = value.toInt();
        }

        break;
    }
    case 1: {
        user->className = value;
        break;
    }
    case 2: {
        user->firstname = value;
        break;
    }
    case 3: {
        user->lastname = value;
        break;
    }
    case 4: {
        user->birthday = QDateTime::fromString(value, "dd/MM/yyyy");
        break;
    }
    case 5: {
        user->email = value;
        break;
    }
    case 6: {
        user->password = value;
        break;
    }
    default:
        break;
    }

}

void DashboardWindow::on_userTableWidget_itemChanged(QTableWidgetItem *item)
{


    if(item->row() == this->ui->userTableWidget->currentRow()  && item->column() == this->ui->userTableWidget->currentColumn()){


        QColor color = item->textColor();

        if(item->row() < this->contest->users.size()){
            User *user = &this->contest->users[item->row()];
            qint64 id = user->id;
            setUserDataByColumnIndex(user, item->column(), item->text());

            if (!this->contest->updateUser(id,user)){
                setUserDataByColumnIndex(user, item->column(), "");
                item->setData(0, "");

            }else{
                item->setTextColor(color);
            }

        }else{

            User user;
            setUserDataByColumnIndex(&user, item->column(), item->text());
            if(this->contest->addUser(&user)){
                this->ui->userTableWidget->setRowCount(this->contest->users.size()+1);
            }else{
                setUserDataByColumnIndex(&user, item->column(), "");
                item->setData(0, "");
            }
        }


    }



}

/**
 * Handle problem changes from select box
 * @brief DashboardWindow::on_problemComboBox_currentIndexChanged
 * @param value
 */

void DashboardWindow::on_problemComboBox_currentIndexChanged(const QString &value)
{

    if(value == "+ New problem"){
       bool ok;
       QString text = QInputDialog::getText(this, tr("Add Problem"),
                                            tr("Problem Name:"), QLineEdit::Normal,
                                            "", &ok);
       if (ok && !text.isEmpty()){
           // create new problem
           Problem p;
           p.name = text;
           p.maxScore = 30;
           p.memoryLimit = 256;
           p.timeLimit = 1;

           if(!contest->addProblem(p)){
               QMessageBox::warning(this, tr("Add problem error"), tr("Problem could not be saved."));
               this->ui->problemComboBox->setCurrentIndex(0);

           }else{
               setupProblemListComboBox(this->ui->problemComboBox, this->contest);
               this->ui->problemComboBox->setCurrentIndex(this->contest->problems.size() -1);
           }

       }else{
           this->ui->problemComboBox->setCurrentIndex(0);
       }


    }else{

        this->selectedProblem = this->contest->findProblemByName(value);
        setupProblemDetails(ui, this->selectedProblem);
    }
}
