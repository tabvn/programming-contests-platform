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


QVariant getUserProblemScore(QVariant userId, QString problem){


    QSqlQuery q;

    if (!q.prepare("select score, accepted, error from submissions where status=1 AND userId=:userId AND problem=:problem order by score desc limit 1")){
        qDebug() << q.lastError();
        return -1;
    }
    q.bindValue(":userId", userId.toInt());
    q.bindValue(":problem", problem);

    if(!q.exec()){
        qDebug() << q.lastError();
        return -1;
    }
    while(q.next()){
        return q.value(0);
    }
    return -1;
}

/**
 * Setup table view for scoreboard
 * @brief setupScoreTableView
 * @param table
 */
void setupScoreTableView(QTableWidget *table, Contest *contest){



    table->clear();


    QStringList headers = { "ID", "Name"};
    QVector<Problem> problems = contest->getProblems();
    QString problemName;

    User user;

    headers.append("Score");

    table->setColumnCount(headers.length());
    table->setHorizontalHeaderLabels(headers);

    int column = 0;
    int score;
    QVariant userProblemScore = -1;
    QVariant userId;

    QVector<User> users = contest->getScoreboardUsers();
    table->setRowCount(users.size());
    if(!problems.isEmpty()){
        for (int row = 0; row < users.size(); row++) {

            user = users[row];
            column = 0;

            table->setItem(row, 0, new QTableWidgetItem(QString::number(user.id)));

            table->setItem(row, 1, new QTableWidgetItem(user.lastname + " " + user.firstname));

            column = 2;
            score = 0;
            for (int i = 0; i < problems.size(); i++) {

               userProblemScore = getUserProblemScore(user.id, problems[i].name);

               if(userProblemScore.toInt() > 0){
                   score += userProblemScore.toInt();
                   table->setItem(row, column, new QTableWidgetItem(userProblemScore.toString()));
               }

               column++;
            }

            table->setItem(row, column, new QTableWidgetItem(QString::number(score)));


        }
    }


    table->setShowGrid(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->resizeSection(1, 300);


}


void setupUserTableView(QTableWidget *table, Contest *contest){


    table->clear();
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

void setupProblemListComboBox(Ui::DashboardWindow *ui, Contest *contest){




   QVector<Problem> problems = contest->getProblems();
   ui->problemComboBox->clear();
   for (int i =0; i< problems.size(); i++) {
       ui->problemComboBox->addItem(problems[i].name);
       ui->problemComboBox->setCurrentIndex(0);
   }

   ui->problemComboBox->addItem("+ New problem");

}

void setupProblemDetails(Ui::DashboardWindow *ui, Problem *problem){
    if(problem == nullptr){
        return;
    }

    ui->problemTextField->setText(problem->name);
    ui->maxScoreTextField->setText(QString::number(problem->maxScore));
    ui->memoryLimitTextField->setText(QString::number(problem->memoryLimit));
    ui->timelimitTextField->setText(QString::number(problem->timeLimit));
    ui->descriptionTextField->setHtml(problem->description);


}

void onSelectProblemTest(Ui::DashboardWindow *ui, Contest *contest, Test *t){

    if (contest->selectedProblem == nullptr || t == nullptr){
        return;
    }

    t->loadInputOutput();
    contest->selectedProblem->selectedTest = t;
    ui->inputTestCaseTextField->setPlainText(t->input);
    ui->outputTestCaseTextField->setPlainText(t->output);

}

void insertItemToTableTestCase(Ui::DashboardWindow *ui, Test *t, int row){

    ui->testcaseTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(t->strength)));


}
void setupTestcaseTable(Ui::DashboardWindow *ui, Contest *contest){

    if(contest->selectedProblem == nullptr){
        return;
    }
    ui->testcaseTableWidget->clear();

    QStringList headers = {"Strength"};

    ui->testcaseTableWidget->setColumnCount(1);
    ui->testcaseTableWidget->setHorizontalHeaderLabels(headers);
    QVector<Test> tests = contest->selectedProblem->getTests();
    Test t;

    ui->testcaseTableWidget->setRowCount(tests.size());

    for(int row = 0; row < tests.size(); row++){

       t = tests[row];
       insertItemToTableTestCase(ui, &t, row);

    }

    ui->testcaseTableWidget->horizontalHeader()->setStretchLastSection(true);

    if(contest->selectedProblem->selectedTest == nullptr){
        ui->inputTestCaseTextField->setPlainText("");
        ui->outputTestCaseTextField->setPlainText("");
    }



}
void setupProblemsTab(Ui::DashboardWindow *ui, Contest *contest){


     ui->problemDetailTabWidget->setCurrentIndex(0);
     setupProblemListComboBox(ui, contest);
     setupProblemDetails(ui, contest->selectedProblem);
}

void setupViews(Ui::DashboardWindow *ui, Contest *contest){

    // setup scoreboard table

    ui->tabWidget->show();

    setupScoreTableView(ui->scoreTableWidget, contest);

    setupUserTableView(ui->userTableWidget, contest);
    setupProblemsTab(ui, contest);

   // show first tab

    ui->actionSave->setEnabled(true);
    ui->actionSave_as->setEnabled(true);
    if(contest->filePath.isEmpty()){
         ui->actionSave->setEnabled(false);
         ui->actionSave_as->setEnabled(false);
    }

    ui->tabWidget->setCurrentIndex(0);



}

/**
  * Window did mount
 * @brief DashboardWindow::DashboardWindow
 * @param parent
 */

DashboardWindow::DashboardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DashboardWindow)
{



    this->contest = new Contest();

    ui->setupUi(this);

    this->ui->tabWidget->hide();
    this->ui->userTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->testcaseTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->userTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

    connect(ui->testcaseTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequestedTestCaseTable(QPoint)));

    ui->actionSave->setEnabled(false);
    ui->actionSave_as->setEnabled(false);

}

void DashboardWindow::slotCustomMenuRequestedTestCaseTable(QPoint pos)
{

    QMenu * menu = new QMenu(this);

    QAction *del = new QAction(tr("Delete"), this);

    connect(del, SIGNAL(triggered()), this, SLOT(slotRemoveTestCaseTableItem())); // Handler delete records

    ui->testcaseTableWidget->selectRow(ui->testcaseTableWidget->currentRow());
    menu->addAction(del);

   menu->popup(ui->testcaseTableWidget->viewport()->mapToGlobal(pos));

}

void DashboardWindow::slotRemoveTestCaseTableItem(){

}

void DashboardWindow::slotCustomMenuRequested(QPoint pos)
{

    QMenu * menu = new QMenu(this);

    QAction *del = new QAction(tr("Delete"), this);

    connect(del, SIGNAL(triggered()), this, SLOT(slotRemoveRecord())); // Handler delete records

    ui->userTableWidget->selectRow(ui->userTableWidget->currentRow());
    menu->addAction(del);

   menu->popup(ui->userTableWidget->viewport()->mapToGlobal(pos));

}

void DashboardWindow::slotRemoveRecord()
{

    int row = ui->userTableWidget->selectionModel()->currentIndex().row();
    if(row < 0 || row >= this->contest->users.size()){
        return;
    }
    if (contest->removeUser(&this->contest->users[row])){
        this->contest->users.removeAt(row);
        ui->userTableWidget->removeRow(row);
        QModelIndex next_index = ui->userTableWidget->model()->index(row -1, 0);
        ui->userTableWidget->setCurrentIndex(next_index);
    }


}

DashboardWindow::~DashboardWindow()
{
    QSqlDatabase::removeDatabase(this->contest->filePath);

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



void DashboardWindow::on_problemComboBox_currentTextChanged(const QString &value)
{

    if(value == "+ New problem" && ui->tabWidget->currentIndex() == 1){
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

               if(!this->contest->problems.isEmpty()){
                   setupProblemListComboBox(this->ui, this->contest);
                  this->ui->problemComboBox->setCurrentIndex(this->contest->problems.size() -1);
               }

           }

       }else{
           this->ui->problemComboBox->setCurrentIndex(0);
       }


    }else{

        contest->selectedProblem = this->contest->findProblemByName(value);
        setupProblemDetails(ui, contest->selectedProblem);
        setupTestcaseTable(this->ui, contest);
    }

}



void DashboardWindow::on_maxScoreTextField_editingFinished()
{

    if(contest->selectedProblem != nullptr){
       QString name = contest->selectedProblem->name;
       int maxScore =  ui->maxScoreTextField->text().toInt();
       contest->selectedProblem->maxScore = maxScore;
       this->contest->updateProblem(name, contest->selectedProblem);
    }
}

void DashboardWindow::on_problemTextField_editingFinished()
{
    if(contest->selectedProblem != nullptr){
       QString name = contest->selectedProblem->name;
       int index = this->contest->findProblemIndex(name);
       contest->selectedProblem->name = ui->problemTextField->text();
       this->contest->updateProblem(name, contest->selectedProblem);

       if(index > 0){
           ui->problemComboBox->setItemText(index, contest->selectedProblem->name);
       }


    }
}

void DashboardWindow::on_memoryLimitTextField_editingFinished()
{
    if(contest->selectedProblem != nullptr){
       contest->selectedProblem->memoryLimit = ui->memoryLimitTextField->text().toInt();
       this->contest->updateProblem(contest->selectedProblem->name, contest->selectedProblem);
    }
}

void DashboardWindow::on_descriptionTextField_textChanged()
{
    if(contest->selectedProblem != nullptr){
       contest->selectedProblem->description = ui->descriptionTextField->toPlainText();
       this->contest->updateProblem(contest->selectedProblem->name, contest->selectedProblem);
    }

}

void DashboardWindow::on_deleteProblemButton_clicked()
{



    if(contest->selectedProblem == nullptr){
        return;
    }

    if (QMessageBox::question(this, "Delete problem confirmation", "Are you sure want to delete problem: " + contest->selectedProblem->name,QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
        //

        if (!this->contest->deleteProblem(contest->selectedProblem)){
            QMessageBox::warning(this, "Error", "Problem "+contest->selectedProblem->name + " could not be deleted.");
        }else{

            if(contest->selectedProblem != nullptr){
                setupProblemListComboBox(ui, contest);
                contest->selectedProblem = nullptr;


            }


        }
    }
}

void DashboardWindow::on_timelimitTextField_editingFinished()
{
    if(contest->selectedProblem != nullptr){

       contest->selectedProblem->timeLimit = ui->timelimitTextField->text().toInt();
       this->contest->updateProblem(contest->selectedProblem->name, contest->selectedProblem);
    }

}

void DashboardWindow::on_actionSave_triggered()
{

    if(this->contest->filePath.isEmpty()){

        QString fileName = QFileDialog::getSaveFileName(this,
                tr("Save Contest"), "",
                tr("Contest (*.ued);;All Files (*)"));

            if (fileName.isEmpty())
                return;
            else {
                if(!this->contest->saveFile(fileName)){
                    QMessageBox::information(this, tr("Unable to open file"),
                        "An error saving.");
                    return;
                }
            }
    }

}

void DashboardWindow::on_actionOpen_triggered()
{


    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Open contest"), QDir::homePath(),
           tr("Contest (*.ued);;All Files (*)"));

       if (fileName.isEmpty())
           return;
       else {

           if(!this->contest->openFile(fileName)){

               QMessageBox::information(this, tr("Unable to open file"),
                   "Could not open file");
           }else{
                //handle reload UI

               setupViews(this->ui, this->contest);
               this->setWindowTitle(fileName);

           }

       }

}

void DashboardWindow::on_actionSave_as_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Contest"), QDir::homePath(),
            tr("Contest (*.ued);;All Files (*)"));


    if(fileName != contest->filePath){

        QFile file(fileName);
        if(file.exists()){
            file.remove();
            file.close();
        }

    }
        if (fileName.isEmpty())
            return;
        else {
            if(!contest->saveFile(fileName)){
                QMessageBox::information(this, tr("Unable to open file"),
                    "An error saving.");
                return;
            }
        }

        this->setWindowTitle(fileName);

}

void DashboardWindow::on_actionNew_Contest_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,tr("New Contest"), QDir::homePath(), tr("Contest (*.ued);;All Files (*)"));

    if (fileName.isEmpty()){
        return;
    }


    QFile file(fileName);
    if(file.exists()){

        file.remove();
        file.close();
    }
    if(contest->createContest(fileName)){

        setupViews(this->ui, contest);
        this->setWindowTitle(fileName);

    }else{

        QMessageBox::information(this, tr("An error"),
            "An error creating new contest.");
    }


}


void DashboardWindow::on_addTestCaseBtn_clicked()
{
    Test t;
    t.strength = 10;
    t.problem = contest->selectedProblem->name;
    if (contest->addTestCase(&t)){
       contest->selectedProblem->tests.push_back(t);
       setupTestcaseTable(this->ui, contest);
       ui->testcaseTableWidget->setCurrentCell(ui->testcaseTableWidget->rowCount() -1, 0);
       ui->testcaseTableWidget->scrollToBottom();


    }
}


void DashboardWindow::on_testcaseTableWidget_itemSelectionChanged()
{

    onSelectProblemTest(ui,contest, contest->selectedProblem->findTestByIndex(ui->testcaseTableWidget->currentRow()));

}

void DashboardWindow::on_deleteTestCaseBtn_clicked()
{

    QModelIndexList indexList = ui->testcaseTableWidget->selectionModel()->selectedIndexes();
    int row = -1;

    foreach (QModelIndex index, indexList) {
        row = index.row();
        if(contest->selectedProblem == nullptr){
            return;
        }

        Test *t = contest->selectedProblem->findTestByIndex(row);
        if(t != nullptr){
            t->remove();
        }

        contest->selectedProblem->selectedTest = nullptr;

    }



    if(row > -1){
        setupTestcaseTable(ui, contest);
        if(ui->testcaseTableWidget->rowCount() > 0){
            if(row == 0){
                ui->testcaseTableWidget->setCurrentCell(0, 0);
            }else{
                ui->testcaseTableWidget->setCurrentCell(row-1, 0);
            }
        }
    }


}


void DashboardWindow::on_testcaseTableWidget_cellChanged(int row, int column)
{

    if(contest->selectedProblem == nullptr){
        return;
    }
    if(contest->selectedProblem->selectedTest == nullptr){
        return;
    }
    if(column == 0){
        int value = ui->testcaseTableWidget->item(row, column)->text().toInt();
        if(contest->selectedProblem->tests[row].strength == value){
            return;
        }

        contest->selectedProblem->selectedTest->strength = value;
        contest->selectedProblem->selectedTest->save();


    }
}

void DashboardWindow::on_inputTestCaseTextField_textChanged()
{

    if(contest->selectedProblem == nullptr){
        return ;
    }

    if(contest->selectedProblem->selectedTest == nullptr){
        return;
    }

    QString input = ui->inputTestCaseTextField->toPlainText();
    contest->selectedProblem->selectedTest->input = input;

    if (!contest->selectedProblem->selectedTest->updateInput(input)){
        QMessageBox::warning(this, "Error save test case", "An error saving testcase");
    }
}

void DashboardWindow::on_outputTestCaseTextField_textChanged()
{

    if(contest->selectedProblem == nullptr){
        return ;
    }

    if(contest->selectedProblem->selectedTest == nullptr){
        return;
    }
    QString output = ui->outputTestCaseTextField->toPlainText();
    contest->selectedProblem->selectedTest->output = output;

    if (!contest->selectedProblem->selectedTest->updateOutput(output)){
        QMessageBox::warning(this, "Error save test case", "An error saving testcase");
    }

}
