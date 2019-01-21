#include "submissionviewdialog.h"
#include "ui_submissionviewdialog.h"

SubmissionViewDialog::SubmissionViewDialog(QWidget *parent, Submission *submission) :
    QDialog(parent),
    ui(new Ui::SubmissionViewDialog)
{
    ui->setupUi(this);
    this->submission = submission;

    ui->label->setText(submission->name);
    ui->codePlainTextEdit->setPlainText(this->submission->code);
    ui->codePlainTextEdit->setTextInteractionFlags(Qt::TextInteractionFlag::TextSelectableByMouse);

}

SubmissionViewDialog::~SubmissionViewDialog()
{
    delete ui;
}
