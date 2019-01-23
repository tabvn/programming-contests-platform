/********************************************************************************
** Form generated from reading UI file 'dashboardwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARDWINDOW_H
#define UI_DASHBOARDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DashboardWindow
{
public:
    QAction *actionQuit_2;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionNew_Contest;
    QAction *actionExcel;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_10;
    QTabWidget *tabWidget;
    QWidget *scoreboard;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *contestlabel;
    QPushButton *contestButton;
    QTableWidget *scoreTableWidget;
    QWidget *problems;
    QVBoxLayout *verticalLayout_2;
    QComboBox *problemComboBox;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *problemDetailTabWidget;
    QWidget *tab;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_14;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label;
    QLineEdit *problemTextField;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_2;
    QLineEdit *maxScoreTextField;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_3;
    QLineEdit *memoryLimitTextField;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QLineEdit *timelimitTextField;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QTextEdit *descriptionTextField;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *pdfFileLabel;
    QPushButton *selectPdfpushButton;
    QPushButton *deleteProblemButton;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *addTestCaseBtn;
    QPushButton *deleteTestCaseBtn;
    QTableWidget *testcaseTableWidget;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_6;
    QPlainTextEdit *inputTestCaseTextField;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_7;
    QPlainTextEdit *outputTestCaseTextField;
    QWidget *users;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *userTableWidget;
    QWidget *submissions;
    QVBoxLayout *verticalLayout_11;
    QTableWidget *submissionsTableWidget;
    QMenuBar *menubar;
    QMenu *menuDashboard;
    QMenu *menuExport_to;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DashboardWindow)
    {
        if (DashboardWindow->objectName().isEmpty())
            DashboardWindow->setObjectName(QString::fromUtf8("DashboardWindow"));
        DashboardWindow->resize(883, 734);
        actionQuit_2 = new QAction(DashboardWindow);
        actionQuit_2->setObjectName(QString::fromUtf8("actionQuit_2"));
        actionOpen = new QAction(DashboardWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(DashboardWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setShortcutVisibleInContextMenu(true);
        actionSave_as = new QAction(DashboardWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionNew_Contest = new QAction(DashboardWindow);
        actionNew_Contest->setObjectName(QString::fromUtf8("actionNew_Contest"));
        actionExcel = new QAction(DashboardWindow);
        actionExcel->setObjectName(QString::fromUtf8("actionExcel"));
        centralwidget = new QWidget(DashboardWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_10 = new QVBoxLayout(centralwidget);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        scoreboard = new QWidget();
        scoreboard->setObjectName(QString::fromUtf8("scoreboard"));
        verticalLayout_12 = new QVBoxLayout(scoreboard);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        contestlabel = new QLabel(scoreboard);
        contestlabel->setObjectName(QString::fromUtf8("contestlabel"));
        contestlabel->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        contestlabel->setFont(font);

        horizontalLayout->addWidget(contestlabel);

        contestButton = new QPushButton(scoreboard);
        contestButton->setObjectName(QString::fromUtf8("contestButton"));
        contestButton->setMaximumSize(QSize(200, 16777215));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        contestButton->setFont(font1);

        horizontalLayout->addWidget(contestButton);


        verticalLayout->addLayout(horizontalLayout);

        scoreTableWidget = new QTableWidget(scoreboard);
        scoreTableWidget->setObjectName(QString::fromUtf8("scoreTableWidget"));
        scoreTableWidget->setFont(font1);
        scoreTableWidget->setSortingEnabled(true);

        verticalLayout->addWidget(scoreTableWidget);


        verticalLayout_12->addLayout(verticalLayout);

        tabWidget->addTab(scoreboard, QString());
        problems = new QWidget();
        problems->setObjectName(QString::fromUtf8("problems"));
        verticalLayout_2 = new QVBoxLayout(problems);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        problemComboBox = new QComboBox(problems);
        problemComboBox->setObjectName(QString::fromUtf8("problemComboBox"));
        problemComboBox->setMinimumSize(QSize(200, 0));
        problemComboBox->setEditable(false);

        verticalLayout_2->addWidget(problemComboBox);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        problemDetailTabWidget = new QTabWidget(problems);
        problemDetailTabWidget->setObjectName(QString::fromUtf8("problemDetailTabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(21, 13, 674, 473));
        verticalLayout_14 = new QVBoxLayout(layoutWidget);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(150, 0));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label);

        problemTextField = new QLineEdit(layoutWidget);
        problemTextField->setObjectName(QString::fromUtf8("problemTextField"));
        problemTextField->setMinimumSize(QSize(300, 0));

        horizontalLayout_11->addWidget(problemTextField);


        verticalLayout_13->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(150, 0));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_2);

        maxScoreTextField = new QLineEdit(layoutWidget);
        maxScoreTextField->setObjectName(QString::fromUtf8("maxScoreTextField"));
        maxScoreTextField->setMinimumSize(QSize(300, 0));

        horizontalLayout_10->addWidget(maxScoreTextField);


        verticalLayout_13->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(150, 0));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_3);

        memoryLimitTextField = new QLineEdit(layoutWidget);
        memoryLimitTextField->setObjectName(QString::fromUtf8("memoryLimitTextField"));
        memoryLimitTextField->setMinimumSize(QSize(300, 0));

        horizontalLayout_9->addWidget(memoryLimitTextField);


        verticalLayout_13->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(150, 0));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_4);

        timelimitTextField = new QLineEdit(layoutWidget);
        timelimitTextField->setObjectName(QString::fromUtf8("timelimitTextField"));
        timelimitTextField->setMinimumSize(QSize(300, 0));

        horizontalLayout_8->addWidget(timelimitTextField);


        verticalLayout_13->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(150, 0));
        label_5->setMaximumSize(QSize(150, 16777215));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_5);

        descriptionTextField = new QTextEdit(layoutWidget);
        descriptionTextField->setObjectName(QString::fromUtf8("descriptionTextField"));
        descriptionTextField->setMinimumSize(QSize(500, 250));
        descriptionTextField->setAutoFormatting(QTextEdit::AutoAll);

        horizontalLayout_7->addWidget(descriptionTextField);


        verticalLayout_13->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(150, 0));
        label_8->setMaximumSize(QSize(150, 16777215));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pdfFileLabel = new QLabel(layoutWidget);
        pdfFileLabel->setObjectName(QString::fromUtf8("pdfFileLabel"));

        horizontalLayout_3->addWidget(pdfFileLabel);

        selectPdfpushButton = new QPushButton(layoutWidget);
        selectPdfpushButton->setObjectName(QString::fromUtf8("selectPdfpushButton"));

        horizontalLayout_3->addWidget(selectPdfpushButton);


        horizontalLayout_6->addLayout(horizontalLayout_3);


        verticalLayout_13->addLayout(horizontalLayout_6);


        verticalLayout_14->addLayout(verticalLayout_13);

        deleteProblemButton = new QPushButton(layoutWidget);
        deleteProblemButton->setObjectName(QString::fromUtf8("deleteProblemButton"));
        deleteProblemButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 13, 19);"));

        verticalLayout_14->addWidget(deleteProblemButton);

        problemDetailTabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_9 = new QVBoxLayout(tab_2);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        addTestCaseBtn = new QPushButton(tab_2);
        addTestCaseBtn->setObjectName(QString::fromUtf8("addTestCaseBtn"));

        horizontalLayout_4->addWidget(addTestCaseBtn);

        deleteTestCaseBtn = new QPushButton(tab_2);
        deleteTestCaseBtn->setObjectName(QString::fromUtf8("deleteTestCaseBtn"));
        deleteTestCaseBtn->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 15);"));

        horizontalLayout_4->addWidget(deleteTestCaseBtn);


        verticalLayout_8->addLayout(horizontalLayout_4);

        testcaseTableWidget = new QTableWidget(tab_2);
        testcaseTableWidget->setObjectName(QString::fromUtf8("testcaseTableWidget"));
        testcaseTableWidget->setMaximumSize(QSize(140, 16777215));

        verticalLayout_8->addWidget(testcaseTableWidget);


        horizontalLayout_5->addLayout(verticalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_4->addWidget(label_6);

        inputTestCaseTextField = new QPlainTextEdit(tab_2);
        inputTestCaseTextField->setObjectName(QString::fromUtf8("inputTestCaseTextField"));

        verticalLayout_4->addWidget(inputTestCaseTextField);


        verticalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_5->addWidget(label_7);

        outputTestCaseTextField = new QPlainTextEdit(tab_2);
        outputTestCaseTextField->setObjectName(QString::fromUtf8("outputTestCaseTextField"));

        verticalLayout_5->addWidget(outputTestCaseTextField);


        verticalLayout_6->addLayout(verticalLayout_5);


        verticalLayout_7->addLayout(verticalLayout_6);


        horizontalLayout_5->addLayout(verticalLayout_7);


        verticalLayout_9->addLayout(horizontalLayout_5);

        problemDetailTabWidget->addTab(tab_2, QString());

        verticalLayout_3->addWidget(problemDetailTabWidget);


        verticalLayout_2->addLayout(verticalLayout_3);

        tabWidget->addTab(problems, QString());
        users = new QWidget();
        users->setObjectName(QString::fromUtf8("users"));
        horizontalLayout_2 = new QHBoxLayout(users);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        userTableWidget = new QTableWidget(users);
        userTableWidget->setObjectName(QString::fromUtf8("userTableWidget"));
        userTableWidget->setContextMenuPolicy(Qt::NoContextMenu);

        horizontalLayout_2->addWidget(userTableWidget);

        tabWidget->addTab(users, QString());
        submissions = new QWidget();
        submissions->setObjectName(QString::fromUtf8("submissions"));
        verticalLayout_11 = new QVBoxLayout(submissions);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        submissionsTableWidget = new QTableWidget(submissions);
        submissionsTableWidget->setObjectName(QString::fromUtf8("submissionsTableWidget"));

        verticalLayout_11->addWidget(submissionsTableWidget);

        tabWidget->addTab(submissions, QString());

        verticalLayout_10->addWidget(tabWidget);

        DashboardWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DashboardWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 883, 22));
        menuDashboard = new QMenu(menubar);
        menuDashboard->setObjectName(QString::fromUtf8("menuDashboard"));
        menuExport_to = new QMenu(menuDashboard);
        menuExport_to->setObjectName(QString::fromUtf8("menuExport_to"));
        DashboardWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(DashboardWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DashboardWindow->setStatusBar(statusbar);

        menubar->addAction(menuDashboard->menuAction());
        menuDashboard->addAction(actionNew_Contest);
        menuDashboard->addAction(actionOpen);
        menuDashboard->addAction(actionSave);
        menuDashboard->addAction(actionSave_as);
        menuDashboard->addAction(menuExport_to->menuAction());
        menuDashboard->addSeparator();
        menuDashboard->addAction(actionQuit_2);
        menuExport_to->addAction(actionExcel);

        retranslateUi(DashboardWindow);

        tabWidget->setCurrentIndex(1);
        problemDetailTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DashboardWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DashboardWindow)
    {
        DashboardWindow->setWindowTitle(QApplication::translate("DashboardWindow", "Ued programming contests platform", nullptr));
        actionQuit_2->setText(QApplication::translate("DashboardWindow", "Quit", nullptr));
        actionOpen->setText(QApplication::translate("DashboardWindow", "Open", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("DashboardWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("DashboardWindow", "Save", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("DashboardWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave_as->setText(QApplication::translate("DashboardWindow", "Save As ...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave_as->setShortcut(QApplication::translate("DashboardWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionNew_Contest->setText(QApplication::translate("DashboardWindow", "New Contest", nullptr));
#ifndef QT_NO_SHORTCUT
        actionNew_Contest->setShortcut(QApplication::translate("DashboardWindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actionExcel->setText(QApplication::translate("DashboardWindow", "Excel...", nullptr));
        contestlabel->setText(QApplication::translate("DashboardWindow", "Contest is stopped", nullptr));
        contestButton->setText(QApplication::translate("DashboardWindow", "Start", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(scoreboard), QApplication::translate("DashboardWindow", "Scoreboard", nullptr));
        label->setText(QApplication::translate("DashboardWindow", "Problem", nullptr));
        problemTextField->setText(QString());
        label_2->setText(QApplication::translate("DashboardWindow", "Max Score", nullptr));
        maxScoreTextField->setText(QApplication::translate("DashboardWindow", "30", nullptr));
        label_3->setText(QApplication::translate("DashboardWindow", "Memory limit(Mb)", nullptr));
        memoryLimitTextField->setText(QApplication::translate("DashboardWindow", "256", nullptr));
        label_4->setText(QApplication::translate("DashboardWindow", "Time limit(Second)", nullptr));
        timelimitTextField->setText(QApplication::translate("DashboardWindow", "1", nullptr));
        label_5->setText(QApplication::translate("DashboardWindow", "Description", nullptr));
        descriptionTextField->setHtml(QApplication::translate("DashboardWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label_8->setText(QApplication::translate("DashboardWindow", "PDF upload", nullptr));
        pdfFileLabel->setText(QApplication::translate("DashboardWindow", "problem.pdf", nullptr));
        selectPdfpushButton->setText(QApplication::translate("DashboardWindow", "Select PDF file", nullptr));
        deleteProblemButton->setText(QApplication::translate("DashboardWindow", "Delete this problem?", nullptr));
        problemDetailTabWidget->setTabText(problemDetailTabWidget->indexOf(tab), QApplication::translate("DashboardWindow", "Details", nullptr));
        addTestCaseBtn->setText(QApplication::translate("DashboardWindow", "+Test", nullptr));
        deleteTestCaseBtn->setText(QApplication::translate("DashboardWindow", "Delete", nullptr));
        label_6->setText(QApplication::translate("DashboardWindow", "Input", nullptr));
        label_7->setText(QApplication::translate("DashboardWindow", "Output", nullptr));
        problemDetailTabWidget->setTabText(problemDetailTabWidget->indexOf(tab_2), QApplication::translate("DashboardWindow", "Test cases", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(problems), QApplication::translate("DashboardWindow", "Problems", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(users), QApplication::translate("DashboardWindow", "Users", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(submissions), QApplication::translate("DashboardWindow", "Submissions", nullptr));
        menuDashboard->setTitle(QApplication::translate("DashboardWindow", "Ued", nullptr));
        menuExport_to->setTitle(QApplication::translate("DashboardWindow", "Export to", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DashboardWindow: public Ui_DashboardWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARDWINDOW_H
