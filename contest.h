#ifndef CONTEST_H
#define CONTEST_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QMap>


struct User{

    qint64 id;
    QString firstname;
    QString lastname;
    qint64 studentId;
    QString className;
    QString email;
    QString password;
};

struct Test{
    qint64 id;
    qint64 strength;
    QString input;
    QString output;
};

struct Problem{

    QString name;
    QByteArray description;
    int maxScore;
    qint64 timeLimit; // second
    qint64 memoryLimit; // kb
    QVector<Test> tests;

};

struct Score{
    User *user;
    int score;
    QMap<QString, qint64> scores;
};

struct TestResult{
    Test *test;
    Problem *problem;
    bool error;
    QString errorMessage;
    bool accepted;
    qint64 time;
    qint64 memory;

};

struct Submission{
    Problem *problem;
    User *user;
    int score;
    QString code;
    QVector<TestResult> results;
    QString status;
    QDateTime created;

};

struct Contest{
    QString name;
    QDateTime start;
    QDateTime end;
    QVector<User> users;
    QVector<Problem> problems;
    QMap<qint64, Score> scores; // map by user id, with score of each problem
    QVector<Submission> submissions;
};



#endif // CONTEST_H
