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


                crow::response response;

                response.add_header("Access-Control-Allow-Origin", "http://localhost:3000");
                response.add_header("Access-Control-Allow-Headers", "Content-Type");


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


                // this->auth(req, res);



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


                body["problems"] = problemJsonArr;
                body["scoreboard"] = scoreJsonArr;


                res.set_header("Content-Type", "application/json");

                res.write(body.dump());
                res.end();


            });


            router(app, "/api/login")
            .methods("OPTIONS"_method,"POST"_method)
            ([&](const crow::request& req, crow::response& res){


                res.add_header("Access-Control-Allow-Origin", "*");
                res.add_header("Access-Control-Allow-Headers", "Content-Type");

                auto x = crow::json::load(req.body);

                qint64 id = x["id"].i();
                QString password = QString::fromStdString(x["password"].s());

                if(!id || password.isEmpty()){
                    this->Error(res, 401, "Login wrong.");
                    return ;
                }

                Login login = this->contest->login(id, password);

                if(login.token.isEmpty()){
                    this->Error(res, 401, "Login wrong.");
                    return;
                }


                nlohmann::json user = nlohmann::json::object();
                user["name"] = login.name.toStdString();
                user["token"] = login.token.toStdString();


                res.set_header("Content-Type", "application/json");
                res.write(user.dump());
                res.end();


            });


            router(app, "/api/solve")
            .methods("POST"_method)
            ([&](const crow::request& req, crow::response& res){

                res.set_header("Content-Type", "application/json");

                std::string token = req.get_header_value("authorization");

                if(token.empty()){
                    this->Error(res, 400, "{\"error\": \"Access denied\"}");
                    return;
                }

                int userId = contest->getUserIdFromToken(QString::fromStdString(token));

                if(!userId){
                    this->Error(res, 400, "{\"error\": \"Access denied\"}");
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
