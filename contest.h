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
    QString memoryPath;
    bool shouldCreateSchema = true;
    Problem *selectedProblem = nullptr;
    QVector<User> users;
    QVector<User> scoreboardUsers;
    QVector<Problem> problems;
    QVector<Submission> submissions;
    bool connected;

    Contest(){

        this->connected = false;
        this->shouldCreateSchema = true;
        this->memoryPath = ":memory.db";
    }

    void setupSchema(){

        QSqlQuery q;

        q.exec(QLatin1String("CREATE TABLE variables (name varchar(20) primary key, value varchar(20))"));

        q.exec(QLatin1String("CREATE TABLE users (id PRIMARY KEY, className varchar(20), "
                                 "firstname varchar(20), lastname varchar(20), email vachar(25) UNIQUE, password vachar(50), birthday INTEGER )"));

        q.exec(QLatin1String("CREATE TABLE problems (name varchar(50) primary key, description TEXT, file BLOB, fileType varchar(50), maxScore INTEGER, timeLimit INTEGER, memoryLimit INTEGER)"));

        q.exec(QLatin1String("CREATE TABLE tests (id INTEGER PRIMARY KEY, problem varchar(50), strength INTEGER, input CLOB, output CLOB, "
                                 "FOREIGN KEY(problem) REFERENCES problems(name) ON DELETE CASCADE )"));

        q.exec(QLatin1String("CREATE TABLE submissions (id INTEGER PRIMARY KEY AUTOINCREMENT, userId INTEGER, "
                                 "problem vachar(50), code CLOB, score INTEGER, accepted INTEGER, error TEXT , status varchar(20), created INTEGER, "
                                 "FOREIGN KEY(userId) REFERENCES users(id) ON DELETE CASCADE, FOREIGN KEY(problem) REFERENCES problems(name) ON DELETE CASCADE)"));

    }

    int findProblemIndex(QString name){
        for (int i = 0; i < problems.size(); i++) {
            if(name == problems[i].name){
                return i;
            }
        }
        return -1;
    }

    bool updateProblem(QString name, Problem *p){
         QSqlQuery q;

        if(!q.prepare("update problems set name=:newName, description=:description, fileType=:fileType, file =:file, maxScore=:maxScore, timeLimit=:timeLimit, memoryLimit=:memoryLimit WHERE name=:name")){

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

            return false;
        }



        return true;
    }

    bool deleteProblem(Problem *p){

    QSqlQuery q;
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
        QSqlQuery q;


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


        QSqlQuery q;
        if(this->problems.empty()){
            if(!q.prepare("select name, description,maxScore, timeLimit, memoryLimit from problems where name is not null order by name asc")){
                qDebug() << q.lastError();
                return this->problems;
            }

            if(!q.exec()){
                qDebug() << q.lastError();
                return this->problems;
            }

            while(q.next()){
                Problem p;
                p.name =  q.value(0).toString();
                p.description = q.value(1).toString();
                p.maxScore = q.value(2).toInt();
                p.timeLimit = q.value(3).toInt();
                p.memoryLimit = q.value(4).toInt();

                this->problems.push_back(p);
            }
        }
        return this->problems;
    }
    QVector<User> getUsers(){


        QSqlQuery q;

        if(this->users.empty()){

            if(!q.prepare("select id, firstname, lastname, className, birthday, email, password from users order by firstname asc")){
                return this->users;
            }
            if(!q.exec()){
                return this->users;
            }

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
        q.clear();
        return this->users;
    }

    QVector<User> getScoreboardUsers(){
        User u;


        QSqlQuery q;

        if(this->scoreboardUsers.empty()){

            if(!q.prepare("SELECT u.id, u.firstname, u.lastname, u.className, u.birthday, u.email, u.password FROM users as u inner join submissions as s ON s.userId = u.id  order by firstname asc")){
                return this->scoreboardUsers;
            }
            if (!q.exec()){
                return this->scoreboardUsers;
            }

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


        QSqlQuery q;
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

        if(!q.exec()){
            return false;
        }
        this->users.push_back(*user);
        return true;

    }

    bool removeUser(User *user){

        QSqlQuery q;

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
        QSqlQuery q;
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
        if(!q.exec()){

            return false;
        }

        return true;
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



            this->filePath = filePath;

            this->shouldCreateSchema = false;

            //this->connect();
        }

        return true;

    }

    bool openFile(QString fileName){

       QString path = this->filePath;

       this->shouldCreateSchema = false;
       this->filePath = fileName;

       QSqlDatabase _db = QSqlDatabase::addDatabase("QSQLITE");

        _db.setDatabaseName(this->filePath);

        if(_db.open()){

            qDebug() << _db.lastError();
            this->clear();
            return true;
        }

       // QSqlDatabase::removeDatabase(path);


       return false;


    }

    void clear(){

        if(!this->problems.empty()){
            this->problems.clear();
        }

        if(!this->users.isEmpty()){
            this->users.clear();
        }
        if(!this->submissions.empty()){
            this->submissions.clear();
        }

        if(!this->scoreboardUsers.empty()){
            this->scoreboardUsers.clear();
        }

    }


};



#endif // CONTEST_H
