#ifndef HTTP_H
#define HTTP_H

#include <QtDebug>
#include "crow.h"
#include "contest.h"
#include <iostream>
#include <string>
#include <QString>
#include "json.h"

#define router CROW_ROUTE
namespace Ued {

    struct Http{
        Contest *contest;
        crow::SimpleApp app;
        bool started = false;

        Http(Contest *contest){


            this->contest = contest;

        }

        void Error(crow::response& res, int code, std::string message){
            res.code = code;
            res.write(message);
            res.end();

        }

        void auth(const crow::request& req, crow::response& res){

            res.add_header("Access-Control-Allow-Origin", "http://localhost:3000");

            std::string token = req.get_header_value("authorization");



            if(token.empty()){
                 this->Error(res, 401, "{\"error\": \"Unauthorized\"}");
                return;
            }

            if(!this->contest->validateToken(QString::fromStdString(token))){
               this->Error(res, 401, "{\"error\": \"Unauthorized\"}");
               return;
            }



        }
        void run(std::uint16_t port){

            this->started = true;


            router(app, "/")([&](const crow::request&, crow::response& res){

                if(!contest->started){
                    res.code = 400;
                    res.write("Contest has not started yet");
                    res.end();

                    return;
                }

                QFile file(":/app/web.html.ts");
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
                    res.code = 404;
                    res.write("not found");
                    res.end();

                    return;
                }

                QTextStream in(&file);
                QString content = in.readAll();
                file.close();
                res.set_header("Content-Type", "text/html; charset=utf-8");
                res.write(content.toStdString());
                res.end();



            });

            router(app, "/app.js")([&](const crow::request&, crow::response& res){

                QFile file(":/app/web.js.ts");
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
                    res.code = 404;
                    res.write("not found");
                    res.end();

                    return;
                }

                QTextStream in(&file);

                QString content = in.readAll();
                file.close();
                res.set_header("Content-Type", "application/javascript");
                res.write(content.toStdString());
                res.end();

            });


            router(app, "/api")
            ([&](const crow::request& req, crow::response& res){


                res.set_header("Content-Type", "application/json");

                std::string token = req.get_header_value("authorization");

                if(token.empty()){
                    this->Error(res, 401, "{\"error\": \"Access denied\"}");
                    return;
                }

                int userId = contest->getUserIdFromToken(QString::fromStdString(token));

                if(!userId){
                    this->Error(res, 401, "{\"error\": \"Access denied\"}");
                    return;
                }




                nlohmann::json body = nlohmann::json::object();

                QVector<Problem> problems = contest->getProblems();


                nlohmann::json problemJsonArr = nlohmann::json::array();
                nlohmann::json problemObject = nlohmann::json::object();

                for (int i = 0; i < problems.size(); i++) {

                    problemObject["name"] = problems[i].name.toStdString();
                    problemObject["maxScore"] = problems[i].maxScore;
                    problemObject["description"] = problems[i].description.toStdString();

                   problemJsonArr.push_back(problemObject);
                }



                QVector<Scoreboard> scores = contest->getScoreboards();

                nlohmann::json scoreJsonArr = nlohmann::json::array();
                nlohmann::json scoreObject = nlohmann::json::object();
                nlohmann::json scoreProblemObject = nlohmann::json::object();
                nlohmann::json pJsonArr = nlohmann::json::array();

                for (int i = 0; i< scores.size(); i++) {
                    scoreObject["name"] = scores[i].name.toStdString();
                    scoreObject["total"] = scores[i].total;
                    pJsonArr.clear();
                    for (int j = 0; j < scores[i].problems.size(); j++) {
                        scoreProblemObject["name"] = scores[i].problems[j].name.toStdString();
                        scoreProblemObject["score"] = scores[i].problems[j].score;
                        pJsonArr.push_back(scoreProblemObject);
                    }

                    scoreObject["problems"] = pJsonArr;

                    scoreJsonArr.push_back(scoreObject);

                }


                QVector<Submission> submissions = contest->getUserSubmissions(userId);

                nlohmann::json submissionArr = nlohmann::json::array();
                nlohmann::json submissionObj = nlohmann::json::object();




                for (int i = 0; i < submissions.size(); i++) {
                    submissionObj["id"] = submissions[i].id;
                    submissionObj["userId"] = submissions[i].userId;
                    submissionObj["problem"] = submissions[i].problem.toStdString();
                    submissionObj["created"] = submissions[i].created.toTime_t();
                    submissionObj["accepted"] = submissions[i].accepted;
                    submissionObj["error"] = submissions[i].error.toStdString();
                    submissionObj["code"] = submissions[i].code.toStdString();
                    submissionObj["score"] = submissions[i].score;
                    submissionObj["status"] = submissions[i].status;
                    submissionArr.push_back(submissionObj);

                }


                body["problems"] = problemJsonArr;
                body["scoreboard"] = scoreJsonArr;
                body["submissions"] = submissionArr;

                res.set_header("Content-Type", "application/json");

                res.write(body.dump());
                res.end();


            });


            router(app, "/api/logout")([&](const crow::request& req, crow::response& res){


                std::string token = req.get_header_value("authorization");

                res.set_header("Content-Type", "text/html; charset=utf-8");
                if(token.empty()){
                    this->Error(res, 401, "{\"error\": \"wrong token.\"}");
                    return;
                }

                contest->logout(QString::fromStdString(token));

                res.code = 200;
                res.write("{\"message\": \"success.\"}");
                res.end();



            });

            router(app, "/api/login")
            .methods("OPTIONS"_method,"POST"_method)
            ([&](const crow::request& req, crow::response& res){

                res.set_header("Content-Type", "application/json");

                auto x = crow::json::load(req.body);

                qint64 id = x["id"].i();
                QString password = QString::fromStdString(x["password"].s());

                if(!id || password.isEmpty()){
                    this->Error(res, 401, "{\"error\": \"id & password is required.\"}");
                    return ;
                }

                Login login = this->contest->login(id, password);

                if(login.token.isEmpty()){
                    this->Error(res, 401, "{\"error\": \"Wrong id or password\"}");
                    return;
                }


                nlohmann::json user = nlohmann::json::object();
                user["name"] = login.name.toStdString();
                user["token"] = login.token.toStdString();



                res.write(user.dump());
                res.end();


            });


            router(app, "/api/solve")
            .methods("POST"_method)
            ([&](const crow::request& req, crow::response& res){

                res.set_header("Content-Type", "application/json");

                if(!contest->started){
                    this->Error(res, 400, "{\"error\": \"Contest has not started yet.\"}");
                    return;
                }
                std::string token = req.get_header_value("authorization");

                if(token.empty()){
                    this->Error(res, 401, "{\"error\": \"Access denied\"}");
                    return;
                }

                int userId = contest->getUserIdFromToken(QString::fromStdString(token));

                if(!userId){
                    this->Error(res, 401, "{\"error\": \"Access denied\"}");
                    return;
                }

                auto x = crow::json::load(req.body);
                QString problem = QString::fromStdString(x["problem"].s());
                QString code = QString::fromStdString(x["code"].s());

                if(problem.isEmpty() || code.isEmpty()){

                    this->Error(res, 400, "{\"error\": \"Problem & code is required\"}");
                    return ;
                }

                Submission s;

                s.userId = userId;
                s.code = code;
                s.problem = problem;
                s.created = QDateTime::currentDateTime();
                s.accepted = 0;
                s.error = "";
                s.status = 0;

                if(!contest->solveProblem(s)){
                    this->Error(res, 400, "{\"error\": \"Submission could not be saved\"}");
                    return ;
                }
                nlohmann::json body = nlohmann::json::object();

                body["userId"] = userId;
                body["problem"] = problem.toStdString();
                body["created"] = s.created.toTime_t();
                body["id"] = s.id;
                body["accepted"] = s.accepted;
                body["error"] = "";
                body["status"] = 0;
                body["code"] = code.toStdString();
                body["score"] = 0;
                body["created"] = s.created.toTime_t();

                res.write(body.dump());
                res.end();


            });




            app.port(port).multithreaded().run();

        }
        bool isRuning(){
            return this->started;
        }

        void stop(){
            this->started = false;
            app.stop();
        }

    };
}






#endif // HTTP_H
