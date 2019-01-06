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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
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
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *scoreboard;
    QVBoxLayout *verticalLayout;
    QTableWidget *scoreTableWidget;
    QWidget *problems;
    QVBoxLayout *verticalLayout_2;
    QComboBox *problemComboBox;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget_2;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_3;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *problemTextField;
    QLabel *label_2;
    QLineEdit *maxScoreTextField;
    QLabel *label_3;
    QLineEdit *memoryLimitTextField;
    QLabel *label_4;
    QLineEdit *timelimitTextField;
    QLabel *label_5;
    QTextEdit *descriptionTextField;
    QPushButton *deleteProblemButton;
    QWidget *tab_2;
    QListWidget *listWidget;
    QWidget *users;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *userTableWidget;
    QWidget *submissions;
    QMenuBar *menubar;
    QMenu *menuDashboard;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DashboardWindow)
    {
        if (DashboardWindow->objectName().isEmpty())
            DashboardWindow->setObjectName(QString::fromUtf8("DashboardWindow"));
        DashboardWindow->resize(883, 679);
        actionQuit_2 = new QAction(DashboardWindow);
        actionQuit_2->setObjectName(QString::fromUtf8("actionQuit_2"));
        actionOpen = new QAction(DashboardWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(DashboardWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setShortcutVisibleInContextMenu(true);
        actionSave_as = new QAction(DashboardWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        centralwidget = new QWidget(DashboardWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        scoreboard = new QWidget();
        scoreboard->setObjectName(QString::fromUtf8("scoreboard"));
        verticalLayout = new QVBoxLayout(scoreboard);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scoreTableWidget = new QTableWidget(scoreboard);
        scoreTableWidget->setObjectName(QString::fromUtf8("scoreTableWidget"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        scoreTableWidget->setFont(font);
        scoreTableWidget->setSortingEnabled(true);

        verticalLayout->addWidget(scoreTableWidget);

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
        tabWidget_2 = new QTabWidget(problems);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_3 = new QHBoxLayout(tab);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        problemTextField = new QLineEdit(tab);
        problemTextField->setObjectName(QString::fromUtf8("problemTextField"));
        problemTextField->setMinimumSize(QSize(300, 0));

        formLayout->setWidget(0, QFormLayout::FieldRole, problemTextField);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        maxScoreTextField = new QLineEdit(tab);
        maxScoreTextField->setObjectName(QString::fromUtf8("maxScoreTextField"));
        maxScoreTextField->setMinimumSize(QSize(300, 0));

        formLayout->setWidget(1, QFormLayout::FieldRole, maxScoreTextField);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        memoryLimitTextField = new QLineEdit(tab);
        memoryLimitTextField->setObjectName(QString::fromUtf8("memoryLimitTextField"));
        memoryLimitTextField->setMinimumSize(QSize(300, 0));

        formLayout->setWidget(2, QFormLayout::FieldRole, memoryLimitTextField);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        timelimitTextField = new QLineEdit(tab);
        timelimitTextField->setObjectName(QString::fromUtf8("timelimitTextField"));
        timelimitTextField->setMinimumSize(QSize(300, 0));

        formLayout->setWidget(3, QFormLayout::FieldRole, timelimitTextField);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_5);

        descriptionTextField = new QTextEdit(tab);
        descriptionTextField->setObjectName(QString::fromUtf8("descriptionTextField"));
        descriptionTextField->setMinimumSize(QSize(500, 250));
        descriptionTextField->setAutoFormatting(QTextEdit::AutoAll);

        formLayout->setWidget(5, QFormLayout::FieldRole, descriptionTextField);

        deleteProblemButton = new QPushButton(tab);
        deleteProblemButton->setObjectName(QString::fromUtf8("deleteProblemButton"));
        deleteProblemButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 13, 19);"));

        formLayout->setWidget(6, QFormLayout::FieldRole, deleteProblemButton);


        horizontalLayout_3->addLayout(formLayout);

        tabWidget_2->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget_2->addTab(tab_2, QString());

        verticalLayout_3->addWidget(tabWidget_2);


        verticalLayout_2->addLayout(verticalLayout_3);

        listWidget = new QListWidget(problems);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_2->addWidget(listWidget);

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
        tabWidget->addTab(submissions, QString());

        horizontalLayout->addWidget(tabWidget);

        DashboardWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DashboardWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 883, 22));
        menuDashboard = new QMenu(menubar);
        menuDashboard->setObjectName(QString::fromUtf8("menuDashboard"));
        DashboardWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(DashboardWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DashboardWindow->setStatusBar(statusbar);

        menubar->addAction(menuDashboard->menuAction());
        menuDashboard->addAction(actionOpen);
        menuDashboard->addAction(actionSave);
        menuDashboard->addAction(actionSave_as);
        menuDashboard->addSeparator();
        menuDashboard->addAction(actionQuit_2);

        retranslateUi(DashboardWindow);

        tabWidget->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(0);


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
        actionSave_as->setText(QApplication::translate("DashboardWindow", "Save as ...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave_as->setShortcut(QApplication::translate("DashboardWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_NO_SHORTCUT
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
        deleteProblemButton->setText(QApplication::translate("DashboardWindow", "Delete this problem?", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QApplication::translate("DashboardWindow", "Details", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QApplication::translate("DashboardWindow", "Test cases", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(problems), QApplication::translate("DashboardWindow", "Problems", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(users), QApplication::translate("DashboardWindow", "Users", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(submissions), QApplication::translate("DashboardWindow", "Submissions", nullptr));
        menuDashboard->setTitle(QApplication::translate("DashboardWindow", "Ued", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DashboardWindow: public Ui_DashboardWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARDWINDOW_H
