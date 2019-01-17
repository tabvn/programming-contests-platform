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
#include <functional>
#include <QtNetwork>
#include <QUuid>
#include <queue>
#include "crow.h"
#include "json.h"
#include <mutex>
#include <unordered_set>
#include <unordered_map>


namespace Ued {


struct Login{
    qint64 id;
    QString name;
    QString token;
};

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
    Test *selectedTest = nullptr;
    QVector<Test> tests;
    QVector<Test> getTests(){

        if(!this->tests.isEmpty()){
             tests.clear();
        }
         QSqlQuery q;
         if (!q.prepare("select id,strength from tests where problem=:problem")){
             return this->tests;
         }
         q.bindValue(":problem", this->name);

         if(!q.exec()){
             return this->tests;
         }

         while(q.next()){
             Test t;
             t.id = q.value(0).toInt();
             t.strength = q.value(1).toInt();
             this->tests.push_back(t);
         }

         return this->tests;


    }

    bool removeTestCaseAtIndex(int index){

        if(this->tests.size() <= index){
            return false;
        }



        QSqlQuery q;

        if(!q.prepare("delete from tests where id=:id")){
            return false;
        }

        q.bindValue(":id", this->tests[index].id);

        if(q.exec()){
            this->tests.remove(index);
            return true;
        }

        return false;


    }

    Test* findTestByIndex(int index){
        if(index < this->tests.length()){
            return &this->tests[index];
        }

        return nullptr;
    }
};

struct Submission{
    qint64 id;
    qint64 userId;
    QString name;
    QString problem;
    int score;
    QString code;
    int status;
    int accepted;
    QString error;
    QDateTime created;
};


struct Subscriber{
    int id;
    QString event;

    //void(*callback)(QVariant arg);
    std::function<void(QVariant arg)> callback;
};

struct TestCaseInputOutPut{
    int strength;
    QByteArray input;
    QByteArray output;
};

struct ProblemScore{
    QString name;
    int score;
};

struct Scoreboard{

      QString name;
      int uesrId;
      int total;
      QVector<ProblemScore> problems;

};


struct Contest{

    std::uint16_t port = 8080;
    static QString argument;
    QString filePath;
    QString memoryPath;
    bool shouldCreateSchema = true;
    Problem *selectedProblem = nullptr;
    QVector<User> users;
    QVector<User> scoreboardUsers;
    QVector<Problem> problems;
    QVector<Subscriber> subscribers;
    QVector<Scoreboard> scoreboards;
    bool connected;
    bool started = false;
    QSqlQuery *query = nullptr;
    std::queue<Submission> submissionsQueue;
    std::queue<Submission> submissionRealtimeQuee; // use to update to tableview;
    std::unordered_set<crow::websocket::connection*> connections;
    std::unordered_map<crow::websocket::connection*, qint64> user_connections;
    std::mutex mtx;




    Contest(){

        this->connected = false;
        this->shouldCreateSchema = true;
        this->memoryPath = ":memory.db";


    }

    void start(){
      this->started = true;
    }
    void stop(){
        this->started = false;
    }


    QString getIpAddress(){

        foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
                 return  address.toString();
        }


        return "";

    }

    /**
     * @brief Subscribe to an event
     * @param event
     */


    //void(*callback)(void*),void* callback_arg
    //void(*cb)(QString event, QVariant arg)

    void subscribe(QString event,std::function<void(QVariant data)> cb){

        Subscriber sub;
        sub.id = this->subscribers.size();
        sub.event = event;
        sub.callback = cb;
        this->subscribers.push_back(sub);
    }


    /**
     * @brief Publish to an event with data
     * @param event
     * @param arg
     */

    void publish(QString event, QVariant data){

        for (int i = 0; i < this->subscribers.size(); i++) {
            if(this->subscribers[i].event == event){
                this->subscribers[i].callback(data);
            }
        }
    }


    /**
     * @brief Create new contest
     * @param path
     * @return
     */
    bool createContest(QString path){

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path);
        if(!db.open()){

            return false;
        }

        if (!setupSchema()){
            return false;
        }

        if(this->query != nullptr){
            delete this->query;
        }
        this->query = new QSqlQuery(db);

        return true;

    }
    /**
     * @brief Setup schema when create new contest
     * @return
     */
    bool setupSchema(){

        QSqlQuery q;

        if (!q.exec(QLatin1String("CREATE TABLE users (id INTEGER PRIMARY KEY, className varchar(20), "
                                  "firstname varchar(20), lastname varchar(20), email vachar(25) UNIQUE, password vachar(50), birthday INTEGER, token vachar(50) )"))){
            return false;
        }

        if (!q.exec(QLatin1String("CREATE TABLE problems (name varchar(50) primary key, description TEXT, file BLOB, fileType varchar(50), maxScore INTEGER, timeLimit INTEGER, memoryLimit INTEGER)"))){


            return false;
        }

        q.exec("insert into problems (name, description, maxScore, timeLimit, memoryLimit) values('A', '', 30, 1,256)");

        if(!q.exec(QLatin1String("CREATE TABLE tests (id INTEGER PRIMARY KEY AUTOINCREMENT, problem varchar(50), strength INTEGER, input CLOB, output CLOB, "
                                 "FOREIGN KEY(problem) REFERENCES problems(name) ON DELETE CASCADE )"))){
            return false;
        }

        if (!q.exec(QLatin1String("CREATE TABLE submissions (id INTEGER PRIMARY KEY AUTOINCREMENT, userId INTEGER, "
                                 "problem vachar(50), code CLOB, score INTEGER, accepted INTEGER, error TEXT , status int, created INTEGER, "
                                  "FOREIGN KEY(userId) REFERENCES users(id) ON DELETE CASCADE, FOREIGN KEY(problem) REFERENCES problems(name) ON DELETE CASCADE)"))){
            return false;
        }

        return true;

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
        if(this->query == nullptr){
            qDebug() << "not connected db";
           return false;
        }
        QSqlQuery q = *this->query;


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

        q.prepare("update tests set problem=:problem where problem=:p");
        q.bindValue(":p", name);
        q.bindValue(":problem", p->name);
        q.exec();

        q.prepare("update submissions set problem=:problem where problem=:p");
        q.bindValue(":p", name);
        q.bindValue(":problem", p->name);
        q.exec();



        return true;
    }

    bool deleteProblem(Problem *p){

        if(this->query == nullptr){
            qDebug() << "not connected db";
            return false;
        }
        QSqlQuery q = *this->query;

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

        if(this->query == nullptr){
            qDebug() << "not connected db";
            return false;
        }
        QSqlQuery q = *this->query;



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
    Problem getProblem(QString name){

        Problem p;

        if(this->query == nullptr){
            qDebug() << "not connected db";
            return p;
        }


        QSqlQuery q = *this->query;



        if(!q.prepare("select name, description,maxScore, timeLimit, memoryLimit from problems where name=:name limit 1")){
            qDebug() << q.lastError();
            return p;
        }

        q.bindValue(":name", name);

        if(!q.exec()){
            qDebug() << q.lastError();
            return p;
        }

        while(q.next()){

            p.name =  q.value(0).toString();
            p.description = q.value(1).toString();
            p.maxScore = q.value(2).toInt();
            p.timeLimit = q.value(3).toInt();
            p.memoryLimit = q.value(4).toInt();

            this->problems.push_back(p);
        }


        return p;
    }

    QVector<Test> getTestsByProblem(QString problem){
        QVector<Test> pTests;
        if(this->query == nullptr){
            qDebug() << "not connected db";
            return pTests;
        }

         if (!query->prepare("select id,strength from tests where problem=:problem")){
             qDebug() << query->lastError();
             return pTests;
         }

         query->bindValue(":problem", problem);

         if(!query->exec()){
             qDebug() << query->lastError();
             return pTests;
         }

         Test t;
         while(query->next()){
             t.id = query->value(0).toInt();
             t.strength = query->value(1).toInt();
             //t.input = query->value(2).toString();
             //t.output = query->value(3).toString();
             pTests.push_back(t);
         }

         return pTests;

    }

    QVector<TestCaseInputOutPut> getTestCasesInputOutput(QString problem){

        QVector<TestCaseInputOutPut> pTests;
        if(this->query == nullptr){
            qDebug() << "not connected db";
            return pTests;
        }

         if (!query->prepare("select strength, input, output from tests where problem=:problem")){
             return pTests;
         }

         query->bindValue(":problem", problem);

         if(!query->exec()){
             return pTests;
         }

         TestCaseInputOutPut t;
         while(query->next()){

             t.strength = query->value(0).toInt();
             t.input = query->value(1).toByteArray();
             t.output = query->value(2).toByteArray();

             pTests.push_back(t);
         }

         return pTests;
    }



    QVector<Problem> getProblems(){

        this->problems.clear();

        if(this->query == nullptr){
            qDebug() << "not connected db";
            return this->problems;
        }

        QSqlQuery q = *this->query;



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


        return this->problems;
    }
    QVector<User> getUsers(){


        if(this->query == nullptr){
            qDebug() << "not connected db";
            return this->users;
        }
        QSqlQuery q = *this->query;


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

        this->scoreboardUsers.clear();

        if(this->query == nullptr){
            qDebug() << "not connected db";
            return this->scoreboardUsers;
        }
        QSqlQuery q = *this->query;


        if(!q.prepare("SELECT u.id, u.firstname, u.lastname, u.className, u.birthday FROM users as u where u.id in (select userId from submissions)  order by firstname asc")){
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

            this->scoreboardUsers.push_back(u);
        }

        return this->scoreboardUsers;
    }

    QVariant getUserProblemScore(QVariant userId, QString problem){

        if(this->query == nullptr){
            qDebug() << "not connected db";
            return -1;
        }
        QSqlQuery q = *this->query;


        if (!q.prepare("select max(score) from submissions where status=2 AND userId=:userId AND problem=:problem")){
            qDebug() << q.lastError();
            return -1;
        }
        q.bindValue(":userId", userId.toInt());
        q.bindValue(":problem", problem);

        if(!q.exec()){
            qDebug() << q.lastError();
            return -1;
        }
        while(q.next()){
            return q.value(0);
        }
        return -1;
    }


    QVector<Scoreboard> getScoreboards(){

        Scoreboard s;
        ProblemScore p;
        int total = 0;

        this->scoreboards.clear();
        QVector<User> scoreUsers = this->getScoreboardUsers();
        QVector<Problem> plist = this->getProblems();

        for (int i = 0; i < scoreUsers.size(); i++) {

            s.name = scoreUsers[i].lastname + " " + scoreUsers[i].firstname;

            s.problems.clear();
            total = 0;

            for (int j = 0; j < plist.size(); j++) {
                p.name = plist[j].name;
                p.score = this->getUserProblemScore(scoreUsers[i].id, plist[j].name).toInt();
                s.problems.push_back(p);
                if(p.score > 0){
                    total += p.score;
                }
            }

            s.total = total;
            this->scoreboards.push_back(s);

        }

        return this->scoreboards;
    }



    bool addUser(User *user){

        if(this->query == nullptr){
            qDebug() << "not connected db";
            return false;
        }
        QSqlQuery q = *this->query;

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

        if(this->query == nullptr){
            qDebug() << "not connected db";
            return false;
        }
        QSqlQuery q = *this->query;

        if(!q.prepare("delete from users where id=:id")){
            return false;
        }
        q.bindValue(":id", user->id);
        if(!q.exec()){
            return false;
        }


        return true;
    }


    bool addTestCase(Test *t){

        if(this->query == nullptr){
            qDebug() << "not connected db";
            return false;
        }
        QSqlQuery q = *this->query;

        if(this->selectedProblem == nullptr){
            return false;
        }

        if(!q.prepare("insert into tests (problem, strength) values (:problem, :strength)")){
            qDebug() << q.lastError();
            return false;
        }

        q.bindValue(":problem", this->selectedProblem->name);
        q.bindValue(":strength", t->strength);


        if(!q.exec()){
            qDebug() << q.lastError();
            return false;
        }

        t->id = q.lastInsertId().toInt();


        return true;

    }


    bool updateUser(qint64 id, User *user){

        if(this->query == nullptr){
            qDebug() << "not connected db";
            return false;
        }
        QSqlQuery q = *this->query;

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

        /*q.prepare("update submissions set userId=:userId where userId=:id");
        q.bindValue(":userId", user->id);
        q.bindValue(":id", id);
        q.exec();*/

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
        }

        return true;

    }

    bool openFile(QString fileName){

       QString path = this->filePath;

       this->shouldCreateSchema = false;
       this->filePath = fileName;

       QSqlDatabase _db = QSqlDatabase::addDatabase("QSQLITE");

        _db.setDatabaseName(this->filePath);

        if(_db.isOpen()){
            return true;
        }
        if(_db.open()){

            if(this->query != nullptr){
                delete this->query;
            }

            this->query = new QSqlQuery(_db);

            this->clear();
            return true;
        }



       return false;


    }

    void clear(){

        if(!this->problems.empty()){
            this->problems.clear();
        }

        if(!this->users.isEmpty()){
            this->users.clear();
        }

        if(!this->scoreboardUsers.empty()){
            this->scoreboardUsers.clear();
        }

    }



    bool validateToken(QString token){

        if(query == nullptr){
            qDebug() << "Error can not connected db";
            return false;
        }
       if(!query->prepare("select count(*) from users where token=:token")){

           qDebug() << "Error prepare validate token" << query->lastError();
           return  false;
       }
       query->bindValue(":token", token);

       if(!query->exec()){
           return false;

       }

       while(query->next()){

           if(query->value(0).toInt() > 0){
                return true;
           }
       }



        return false;

    }

    int getUserIdFromToken(QString token){

        if(query == nullptr){
            return 0;
        }
       if(!query->prepare("select id from users where token=:token limit 1")){

           return  0;
       }
       query->bindValue(":token", token);

       if(!query->exec()){
           return 0;

       }

       while(query->next()){
          return query->value(0).toInt();
       }

        return 0;
    }

    bool solveProblem(Submission& s){

        if(query == nullptr){
            return false;
        }

        if(!this->query->prepare("select count(*) from problems where name=:problem limit 1")){
            return false;
        }

        query->bindValue(":problem", s.problem);
        if(!query->exec()){
            return false;
        }

        while(query->next()){
            if(query->value(0) == 0){
                return false;
            }
        }

        if(!query->prepare("insert into submissions (userId, problem,code,accepted,status,created) values(:userId, :problem, :code, :accepted, :status, :created)")){
            return 0;
        }

        query->bindValue(":userId", s.userId);
        query->bindValue(":problem", s.problem);
        query->bindValue(":accepted", s.accepted);
        query->bindValue(":status", s.status);
        query->bindValue(":created", s.created.toTime_t());
        query->bindValue(":code", s.code);

        if(!query->exec()){
            return false;
        }



        s.id = query->lastInsertId().toInt();
        Submission sub = getSubmissionById(s.id);

        s.name = sub.name;

        this->submissionsQueue.push(s); // save to queue



        this->submissionRealtimeQuee.push(s);

        this->publish("onNewSubmission", s.id);

        return true;
    }

    bool updateSubmission(Submission& s){

        if(query == nullptr){
            return false;
        }


        if(!query->prepare("update submissions set problem=:problem,accepted=:accepted,status=:status,error=:error,score=:score where id=:id")){

           qDebug() << "Can not update submission";
           return false;
        }

        query->bindValue(":id", s.id);
        query->bindValue(":problem", s.problem);
        query->bindValue(":accepted", s.accepted);
        query->bindValue(":status", s.status);
        query->bindValue(":error", s.error);
        query->bindValue(":score", s.score);


        if(!query->exec()){
                qDebug() << "Can not save submission";
            return false;
        }



        this->submissionRealtimeQuee.push(s);
        this->publish("onSubmissionUpdated", s.id);

        // send socket data

        nlohmann::json submissionObj = nlohmann::json::object();

        submissionObj["id"] = s.id;
        submissionObj["userId"] = s.userId;
        submissionObj["problem"] = s.problem.toStdString();
        submissionObj["created"] = s.created.toTime_t();
        submissionObj["accepted"] = s.accepted;
        submissionObj["error"] = s.error.toStdString();
        submissionObj["code"] = s.code.toStdString();
        submissionObj["score"] = s.score;
        submissionObj["status"] = s.status;

        // send to user id socket realtime

        nlohmann::json j = nlohmann::json::object();

        j["action"] = "submission";
        j["payload"] = submissionObj;

        this->sendRealtime(s.userId, j.dump());
        this->sendAll("{\"action\": \"reload\"}");

        return true;
    }

   void sendAll(std::string data){

       for (std::pair<crow::websocket::connection*, qint64> element : this->user_connections)
       {
           if(element.second != 0){
              element.first->send_text(data);
           }
       }
    }


    void sendRealtime(qint64 userId, std::string data){

        for (std::pair<crow::websocket::connection*, qint64> element : this->user_connections)
        {
            if(element.second == userId){

                element.first->send_text(data);
                // just send one
                break;
            }
        }

    }


    bool logout(QString token){
        if(this->query == nullptr){
            qDebug() << "not connected db";
            return false;
        }

        if(query->prepare("update users set token=:t where token=:token")){
            return false;

        }

        query->bindValue(":t", "");
        query->bindValue(":token", token);

        if(!query->exec()){
            return false;
        }

        return true;
    }
    Login login(qint64 id, QString password){

        Login l;

        if(this->query == nullptr){
            qDebug() << "not connected db";
            return l;
        }
        QSqlQuery q = *this->query;


        if (!q.prepare("select firstname, lastname from users where id=:id AND password=:password")){
            qDebug() << "Prepare error" << q.lastError();
            return l;
        }

        q.bindValue(":id", id);
        q.bindValue(":password", password);

        if (!q.exec()){
            return l;
        }

        while(q.next()){

            l.id = id;
            l.name = q.value(0).toString() + " " + q.value(1).toString();
            l.token = QUuid::createUuid().toString().mid(1,36).toUpper();
        }

        if(!l.token.isEmpty()){
            if (!q.prepare("update users set token=:token where id=:id")){
                 l.token = "";
            }

            q.bindValue(":id", id);
            q.bindValue(":token", l.token);
            if(!q.exec()){
                l.token = "";
            }

        }

        return l;

    }

    Submission getSubmissionById(qint64 id){

        Submission s;
        s.id = id;
        if(this->query == nullptr){

            qDebug() << "Is not connect db";
            return s;
        }

        if(!query->prepare("select s.id, s.userId, s.problem, s.code,s.score,s.accepted,s.error, s.status, s.created, u.firstname, u.lastname from submissions as s inner join users as u on u.id = s.userId where s.id=:id limit 1")){
            qDebug() << "Error" << query->lastError();
            return s;
        }
        query->bindValue(":id", id);

        if(!query->exec()){
            qDebug() << "Error" << query->lastError();
            return s;
        }

        while(query->next()){
            // only scan first one
            s.id = id;
            s.userId = query->value(1).toInt();
            s.problem = query->value(2).toString();
            s.code = query->value(3).toString();
            s.score = query->value(4).toInt();
            s.accepted = query->value(5).toInt();
            s.error = query->value(6).toString();
            s.status = query->value(7).toInt();
            s.created = QDateTime::fromTime_t(query->value(8).toUInt());
            s.name = query->value(10).toString() + " "+ query->value(9).toString(); // last + firstname in Vietnam :)

            return s;
        }

        return s;
    }
    QVector<Submission> getSubmissions(){



        QVector<Submission> submissions;

        if(this->query == nullptr){
            qDebug() << "Could not connected db";
            return submissions;
        }

        if (!query->prepare("select s.id, s.userId, s.problem, s.code,s.score,s.accepted,s.error, s.status, s.created, u.firstname, u.lastname from submissions as s inner join users as u on u.id = s.userId order by created desc limit 300")){
            return submissions;
        }

        if(!query->exec()){
            return submissions;
        }

        Submission s;

        while(query->next()){

            s.id = query->value(0).toInt();
            s.userId = query->value(1).toInt();
            s.problem = query->value(2).toString();
            s.code = query->value(3).toString();
            s.score = query->value(4).toInt();
            s.accepted = query->value(5).toInt();
            s.error = query->value(6).toString();
            s.status = query->value(7).toInt();
            s.created = QDateTime::fromTime_t(query->value(8).toUInt());
            s.name = query->value(10).toString() + " "+ query->value(9).toString(); // last + firstname in Vietnam :)

           submissions.push_back(s);
        }

        return submissions;


    }

    QVector<Submission> getUserSubmissions(qint64 userId){

        QVector<Submission> userSubmissions;
        Submission s;

        if(this->query == nullptr){
            qDebug() << "Could not connected db";
            return userSubmissions;
        }

        if (!query->prepare("select id, userId, problem, code,score,accepted,error, status, created from submissions where userId=:userId order by created desc")){
            return userSubmissions;
        }
        query->bindValue(":userId", userId);

        if(!query->exec()){
            return userSubmissions;
        }



        while(query->next()){

            s.id = query->value(0).toInt();
            s.userId = query->value(1).toInt();
            s.problem = query->value(2).toString();
            s.code = query->value(3).toString();
            s.score = query->value(4).toInt();
            s.accepted = query->value(5).toInt();
            s.error = query->value(6).toString();
            s.status = query->value(7).toInt();
            s.created = QDateTime::fromTime_t(query->value(8).toUInt());

           userSubmissions.push_back(s);
        }

        return userSubmissions;


    }


    bool saveTest(Test *s){


        if(!s->id || this->query == nullptr){
            return false;
        }
        if(!query->prepare("update tests set strength=:strength where id=:id")){
            return false;
        }

        query->bindValue(":strength", s->strength);
        query->bindValue(":id", s->id);

        if(query->exec()){

            return true;
        }

        return false;
    }

    bool removeTest(qint64 testId){

        if(!testId || this->query == nullptr){
            return false;
        }



        if(!query->prepare("delete from tests where id=:id")){
            return false;
        }

        query->bindValue(":id", testId);

        if(query->exec()){

            return true;
        }

        return false;

    }

    bool updateTestInput(Test *s, QString input){

        input = input.trimmed();

        if(!s->id || this->query == nullptr){
            return false;
        }

        if(!query->prepare("update tests set input=:input where id=:id")){
            return false;
        }

        query->bindValue(":input", input);

        query->bindValue(":id", s->id);

        if(query->exec()){

            return true;
        }

        return false;

    }

    bool updateTestOutput(Test *s, QString output){


        output = output.trimmed();
        if(!s->id || this->query == nullptr){
            return false;
        }

        if(!this->query->prepare("update tests set output=:output where id=:id")){
            return false;
        }

        query->bindValue(":output", output);

        query->bindValue(":id", s->id);

        if(query->exec()){

            return true;
        }

        return false;

    }



    bool loadTestInputOutput(Test *s){


        if(!s->id || this->query == nullptr){
            qDebug() << "Error" << s->id << "No connect db";
            return false;
        }

        if(!query->prepare("select input, output from tests where id=:id")){
            qDebug() << query->lastError();
            return false;
        }

        query->bindValue(":id", s->id);

        if(!query->exec()){
            return false;
        }
        while(query->next()){
            s->input = query->value(0).toString();
            s->output = query->value(1).toString();
            return true;
        }


        return false;
    }



};

}



#endif // CONTEST_H
