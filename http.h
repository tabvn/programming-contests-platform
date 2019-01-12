#ifndef HTTP_H
#define HTTP_H

#include <QtDebug>
#include "crow.h"
#include "contest.h"
#include <iostream>
#include <string>
#include <QString>

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
            std::string token = req.get_header_value("authorization");

            std::cout << "token:" << token;

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

            router(app, "/")([&](){

                if(contest->started){

                   return "Hello world";
                }
                return "Sorry contest is finished.";

            });



            router(app, "/login")
            .methods("POST"_method)
            ([&](const crow::request& req, crow::response& res){


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


                crow::json::wvalue user;
                user["name"] = login.name.toStdString();
                user["token"] = login.token.toStdString();
                res.set_header("Content-Type", "application/json");
                res.write(crow::json::dump(user));
                res.end();


            });


            router(app, "/solve")
            .methods("POST"_method)
            ([&](const crow::request& req, crow::response& res){


                this->auth(req, res);

                auto x = crow::json::load(req.body);

                QString problem = QString::fromStdString(x["problem"].s());
                QString code = QString::fromStdString(x["code"].s());


                res.set_header("Content-Type", "application/json");

                if(problem.isEmpty() || code.isEmpty()){
                    this->Error(res, 400, "{\"error\": \"Problem & code is required\"}");
                    return ;
                }



                crow::json::wvalue body;
                body["status"] = 0;
                body["problem"] = problem.toStdString();


                res.write(crow::json::dump(body));
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
