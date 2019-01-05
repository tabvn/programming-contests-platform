#ifndef CONTEST_H
#define CONTEST_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QMap>
#include <QtSql>
#include <QMessageBox>


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

struct Problem{

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

    QVector<User> users;
    QVector<User> scoreboardUsers;
    QVector<Problem> problems;
    QVector<Submission> submissions;
    QSqlQuery q;

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
};



#endif // CONTEST_H
