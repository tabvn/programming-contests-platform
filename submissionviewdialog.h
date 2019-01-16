#ifndef SUBMISSIONVIEWDIALOG_H
#define SUBMISSIONVIEWDIALOG_H

#include <QDialog>
#include "contest.h"

namespace Ui {
class SubmissionViewDialog;
}

class SubmissionViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SubmissionViewDialog(QWidget *parent = nullptr, Submission *submission = nullptr);
    ~SubmissionViewDialog();

private:
    Ui::SubmissionViewDialog *ui;
    Submission *submission;

};

#endif // SUBMISSIONVIEWDIALOG_H
