#include "judge.h"

Judge::Judge(Contest *c)
{
    this->contest = c;

}

void Judge::run()
{

    qDebug() << contest->submissionsQueue.size();
    while(true){
        Submission s;

        if(!contest->submissionsQueue.empty()){
            s = contest->submissionsQueue.front();
            qDebug() << "Processing submission" << s.problem << s.id;
            // do job
            QString dir = "/Users/toan/Desktop/ued/"+QString::number(s.userId) + "_"+QString::number(s.id);
            if (!QDir(dir).exists()){
                if (!QDir().mkpath(dir)){
                    qDebug() << "can not create file" << dir;
                    contest->publish("error", "Could not create file for compile submission.");
                    break;
                }
            }

            QString filename = dir + "/"+ s.problem +".cpp";
            QFile file(filename);

            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){

                contest->publish("error", "Could not create " + filename + " for compile submission.");

                break;
            }

            QTextStream out(&file);
            out << s.code;
            file.close();

            // let compile file

            QProcess builder;
            builder.setProcessChannelMode(QProcess::MergedChannels);
            builder.start("g++ " + filename + " -o " +  dir + "/"+ s.problem);

            if (!builder.waitForFinished()){
                s.error = "Complie error.";
                s.accepted = 0;
                s.status = 2;
                s.score = 0;

                contest->updateSubmission(s);
                qDebug() << "Complie error" << s.error;

            }else{

                QString err = builder.readAll();
                qDebug() << "complie with erro" << err << err.isEmpty();

                if(err.isEmpty()){
                    // continue run test

                }else{
                    s.error = "Complie error.";
                    s.accepted = 0;
                    s.status = 2;
                    s.score = 0;
                    contest->updateSubmission(s);

                }
            }


            QDir d(dir);
            //d.removeRecursively();

            contest->submissionsQueue.pop();
        }

    }

}
