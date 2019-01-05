#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QtSql>

static bool createConnection()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString db_path = "/Users/toan/Desktop"; //QDir::currentPath();
    db.setDatabaseName(":memory:");
    db_path =  db_path + QString("/db.sqlite");
    db.setDatabaseName(db_path);
    qDebug() <<db_path;    //current path
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"), QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;

    query.exec(QLatin1String("CREATE TABLE variables (id INTEGER PRIMARY KEY AUTOINCREMENT, name varchar(20) NOT NULL UNIQUE, value varchar(20))"));

    query.exec(QLatin1String("CREATE TABLE users (id PRIMARY KEY, className varchar(20), "
                             "firstname varchar(20), lastname varchar(20), email vachar(25) UNIQUE, password vachar(50) NOT NULL )"));

    query.exec(QLatin1String("CREATE TABLE problems (name varchar(50) primary key not null, description TEXT, file BLOB, fileType varchar(50), maxScore INTEGER, timeLimit INTEGER, memoryLimit INTEGER)"));

    query.exec(QLatin1String("CREATE TABLE tests (id INTEGER PRIMARY KEY AUTOINCREMENT, problem varchar(50), strength INTEGER, input CLOB, output CLOB, "
                             "FOREIGN KEY(problem) REFERENCES problems(name) ON DELETE CASCADE )"));

    query.exec(QLatin1String("CREATE TABLE submissions (id INTEGER PRIMARY KEY AUTOINCREMENT, userId INTEGER, "
                             "problem vachar(50), code CLOB, score INTEGER, accepted INTEGER, error TEXT , status varchar(20), created INTEGER, "
                             "FOREIGN KEY(userId) REFERENCES users(id) ON DELETE CASCADE, FOREIGN KEY(problem) REFERENCES problems(name) ON DELETE CASCADE)"));

    query.exec(QLatin1String("CREATE TABLE scores (userId INTEGER, problem varchar(50), score INTEGER, FOREIGN KEY(userId) REFERENCES users(id) ON DELETE CASCADE, "
                             "FOREIGN KEY(problem) REFERENCES problems(name) ON DELETE CASCADE)"));


    return true;
}

#endif // CONNECTION_H
