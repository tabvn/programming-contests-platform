/********************************************************************************
** Form generated from reading UI file 'submissionviewdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBMISSIONVIEWDIALOG_H
#define UI_SUBMISSIONVIEWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SubmissionViewDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPlainTextEdit *codePlainTextEdit;

    void setupUi(QDialog *SubmissionViewDialog)
    {
        if (SubmissionViewDialog->objectName().isEmpty())
            SubmissionViewDialog->setObjectName(QString::fromUtf8("SubmissionViewDialog"));
        SubmissionViewDialog->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(SubmissionViewDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(SubmissionViewDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        codePlainTextEdit = new QPlainTextEdit(SubmissionViewDialog);
        codePlainTextEdit->setObjectName(QString::fromUtf8("codePlainTextEdit"));

        verticalLayout->addWidget(codePlainTextEdit);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(SubmissionViewDialog);

        QMetaObject::connectSlotsByName(SubmissionViewDialog);
    } // setupUi

    void retranslateUi(QDialog *SubmissionViewDialog)
    {
        SubmissionViewDialog->setWindowTitle(QApplication::translate("SubmissionViewDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("SubmissionViewDialog", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SubmissionViewDialog: public Ui_SubmissionViewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBMISSIONVIEWDIALOG_H
