#ifndef CONTEST_H
#define CONTEST_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QMap>
#include <QtSql>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QtSql>


struct User{
    qint64 id;
    QString firstname;
    QString lastname;
    QString className;
    QString email;
    QString password;
    QDateTime birthday;



};

struct Test{
    qint64 id;
    qint64 strength;
    QString input;
    QString output;
    QString problem;
};

struct Problem {
    QString name;
    QString description;
    QByteArray file;
    QString fileType;
    int maxScore;
    int timeLimit; // second
    int memoryLimit; // kb
};

struct Submission{
    qint64 userId;
    QString problem;
    int score;
    QString code;
    QString status;
    QString error;
    int accepted;
    QDateTime created;
};

struct Contest{
    QString filePath;
    QString memoryPath = QDir::currentPath() + "/contest.ued";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    bool shouldCreateSchema = true;
    Problem *selectedProblem;
    QVector<User> users;
    QVector<User> scoreboardUsers;
    QVector<Problem> problems;
    QVector<Submission> submissions;

    QSqlQuery q;

    bool updateProblem(QString name, Problem *p){
        if(!q.prepare("update problems set name=:newName, description=:description, fileType=:fileType, file =:file, maxScore=:maxScore, timeLimit=:timeLimit, memoryLimit=:memoryLimit WHERE name=:name")){

            qDebug() << "prepare error" << q.lastError();
            return false;
        }

        q.bindValue(":name", name);
        q.bindValue(":newName",p-> name);
        q.bindValue(":description", p->description);
        q.bindValue(":fileType", p->fileType);
        q.bindValue(":file", p->file);
        q.bindValue(":maxScore", p->maxScore);
        q.bindValue(":memoryLimit", p->memoryLimit);
        q.bindValue(":timeLimit", p->timeLimit);

        if (!q.exec()){

            qDebug() << "exec error" << q.lastError();

            return false;
        }

        return true;
    }

    bool deleteProblem(Problem *p){
        if(!q.prepare("delete from problems where name =:name")){
            return false;
        }

        q.bindValue(":name", p->name);

        if(!q.exec()){
            return false;
        }

        for (int i = 0; i < this->problems.size(); i++) {
            if(this->problems[i].name == p->name){
                this->problems.removeAt(i);

                break;
            }
        }
        return true;
    }
    Problem *findProblemByName(QString name){

        for (int i = 0; i < this->problems.size(); i++) {

            if(this->problems[i].name == name){
                return &this->problems[i];
            }
        }
        return nullptr;
    }

    bool addProblem(Problem p){

        if (!q.prepare("insert into problems (name, description, maxScore, timeLimit, memoryLimit) values(:name, :description, :maxScore, :timeLimit, :memoryLimit)")){

            return false;
        }

        q.bindValue(":name", p.name);
        q.bindValue(":description", p.description);
        q.bindValue(":maxScore", p.maxScore);
        q.bindValue(":timeLimit", p.timeLimit);
        q.bindValue(":memoryLimit", p.memoryLimit);

        if(!q.exec()){

            return false;
        }
        this->problems.push_back(p);
        return true;
    }
    QVector<Problem> getProblems(){

        if(this->problems.empty()){
            this->q.exec("select name, description, file, fileType, maxScore, timeLimit, memoryLimit from problems order by name asc");

            while(this->q.next()){
                Problem p;
                p.name =  q.value(0).toString();
                p.description = q.value(1).toString();
                p.file = q.value(2).toByteArray();
                p.fileType = q.value(3).toString();
                p.maxScore = q.value(4).toInt();
                p.timeLimit = q.value(5).toInt();
                p.memoryLimit = q.value(6).toInt();

                this->problems.push_back(p);
            }
        }
        return this->problems;
    }
    QVector<User> getUsers(){


        if(this->users.empty()){

            this->q.exec("select id, firstname, lastname, className, birthday, email, password from users order by firstname asc");
            while (q.next()) {

                User u;
                u.id = q.value(0).toInt();
                u.firstname = q.value(1).toString();
                u.lastname = q.value(2).toString();
                u.className = q.value(3).toString();
                u.birthday = QDateTime::fromTime_t(q.value(4).toUInt());
                u.email = q.value(5).toString();
                u.password = q.value(6).toString();

                this->users.push_back(u);
            }
        }
        return this->users;
    }

    QVector<User> getScoreboardUsers(){
        User u;


        if(this->scoreboardUsers.empty()){

            this->q.exec("SELECT u.id, u.firstname, u.lastname, u.className, u.birthday, u.email, u.password FROM users as u inner join submissions as s ON s.userId = u.id  order by firstname asc");

            while (q.next()) {
                u.id = q.value(0).toInt();
                u.firstname = q.value(1).toString();
                u.lastname = q.value(2).toString();
                u.className = q.value(3).toString();
                u.birthday = QDateTime::fromTime_t(q.value(4).toUInt());
                u.email = q.value(5).toString();
                u.password = q.value(6).toString();

                this->scoreboardUsers.push_back(u);
            }
        }

        return this->scoreboardUsers;
    }

    bool addUser(User *user){

        if(!user->id || user->id == 0){
            return false;
        }

        if(!q.prepare("insert into users (id, firstname, lastname, className,birthday, email, password) values (:id, :firstname, :lastname, :className, :birthday, :email, :password)")){
            return false;
        }
        q.bindValue(":id", user->id);
        q.bindValue(":firstname", user->firstname);
        q.bindValue(":lastname", user->lastname);
        q.bindValue(":className", user->className);
        q.bindValue(":birthday", user->birthday.toTime_t());
        q.bindValue(":email", user->email);
        q.bindValue(":password", user->password);

        if(!this->q.exec()){
            return false;
        }
        this->users.push_back(*user);
        return true;

    }

    bool removeUser(User *user){

        if(!q.prepare("delete from users where id=:id")){
            return false;
        }
        q.bindValue(":id", user->id);
        if(!q.exec()){
            return false;
        }


        return true;
    }

    bool updateUser(qint64 id, User *user){
        if(!user->id || user->id == 0 || !id || id == 0){
            return false;
        }

        if(!q.prepare("update users set id=:newId, firstname=:firstname, lastname=:lastname, className=:className, birthday=:birthday, email=:email, password=:password where id=:id")){

            return false;
        }
        q.bindValue(":id", id);
        q.bindValue(":newId", user->id);
        q.bindValue(":firstname", user->firstname);
        q.bindValue(":lastname", user->lastname);
        q.bindValue(":className", user->className);
        q.bindValue(":birthday", user->birthday.toTime_t());
        q.bindValue(":email", user->email);
        q.bindValue(":password", user->password);
        if(!this->q.exec()){

            return false;
        }

        return true;
    }

    bool connect(){

        bool isMemoryDb = true;
        if(this->filePath != "" && !this->filePath.isEmpty()){
            QFile file(this->filePath);
            if(file.open(QIODevice::ReadWrite)){
                isMemoryDb = false;
            }
        }

        if(isMemoryDb){
            db.setDatabaseName(memoryPath);
        }else{
            db.setDatabaseName(this->filePath);
        }


        if (!db.open()) {
            qDebug() << "could not open db";

            return false;
        }


        if(this->shouldCreateSchema){

            QSqlQuery query;
            query.exec(QLatin1String("CREATE TABLE variables (name varchar(20) primary key, value varchar(20))"));

            query.exec(QLatin1String("CREATE TABLE users (id PRIMARY KEY, className varchar(20), "
                                     "firstname varchar(20), lastname varchar(20), email vachar(25) UNIQUE, password vachar(50), birthday INTEGER )"));

            query.exec(QLatin1String("CREATE TABLE problems (name varchar(50) primary key, description TEXT, file BLOB, fileType varchar(50), maxScore INTEGER, timeLimit INTEGER, memoryLimit INTEGER)"));

            query.exec(QLatin1String("CREATE TABLE tests (id INTEGER PRIMARY KEY, problem varchar(50), strength INTEGER, input CLOB, output CLOB, "
                                     "FOREIGN KEY(problem) REFERENCES problems(name) ON DELETE CASCADE )"));

            query.exec(QLatin1String("CREATE TABLE submissions (id INTEGER PRIMARY KEY AUTOINCREMENT, userId INTEGER, "
                                     "problem vachar(50), code CLOB, score INTEGER, accepted INTEGER, error TEXT , status varchar(20), created INTEGER, "
                                     "FOREIGN KEY(userId) REFERENCES users(id) ON DELETE CASCADE, FOREIGN KEY(problem) REFERENCES problems(name) ON DELETE CASCADE)"));
        }


        return true;
    }

    void closeConnection(){
        this->db.close();
    }
    bool saveFile(QString filePath){


        if(this->filePath != filePath){

            if(this->filePath != "" && !this->filePath.isNull()){

                if (!QFile::copy(this->filePath, filePath)){
                    return false;
                }
            }else{

                if (!QFile::copy(this->memoryPath, filePath)){
                    return false;
                }

                QFile::remove(this->memoryPath);
            }

            this->closeConnection();

            this->filePath = filePath;

            this->shouldCreateSchema = false;

            this->connect();
        }

        return true;

    }

    bool openFile(QString fileName){

       QFile file(fileName);

       if (!file.open(QIODevice::ReadWrite)) {
                  return false;
       }
       file.close();

       this->filePath = fileName;

       this->closeConnection();

       this->connect();

       this->clear();

       return true;


    }

    void clear(){

        this->problems.clear();
        this->users.clear();
        this->submissions.clear();
        this->scoreboardUsers.clear();

    }


};



#endif // CONTEST_H
