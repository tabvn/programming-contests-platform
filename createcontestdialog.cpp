#include "createcontestdialog.h"
#include "ui_createcontestdialog.h"

CreateContestDialog::CreateContestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateContestDialog)
{
    ui->setupUi(this);
}

CreateContestDialog::~CreateContestDialog()
{
    delete ui;
}
