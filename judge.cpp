#include "judge.h"

Judge::Judge(Contest *c)
{
    this->contest = c;

}


void Judge::run()
{

    qDebug() << contest->submissionsQueue.size();
    while(this->stopped == false){
        Submission s;

        if(!contest->submissionsQueue.empty()){
            s = contest->submissionsQueue.front();
            Problem p = contest->getProblem(s.problem);

            int timeLimit = 1000;
            if(p.timeLimit > 0 ){
               timeLimit = p.timeLimit *1000;
            }

           // qDebug() << "Processing submission" << s.problem << s.id << "Problem:" << p.name;
            // do job
            QTemporaryDir tempDir;
            if (!tempDir.isValid()) {
                  qDebug() << "Invalid dir";
                  break;
            }

            QString dir =  tempDir.path() + QString::number(s.userId) + "_"+QString::number(s.id);
            qDebug() << "DDir:" << dir;

            if (!QDir(dir).exists()){
                if (!QDir().mkpath(dir)){
                    qDebug() << "can not create file" << dir;
                   // contest->publish("error", "Could not create file for compile submission.");
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
            QString programePath = dir + "/"+ s.problem;
            builder.start("g++ " + filename + " -o " +  programePath);

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
                        QVector<TestCaseInputOutPut> tests = this->contest->getTestCasesInputOutput(p.name);

                        int totalScore = 0;
                        int maxScore = p.maxScore;
                        int totalStrength = 0;

                        for (int i = 0; i < tests.size(); i++) {
                            totalStrength += tests[i].strength;
                        }

                        for (int i =0;i< tests.size(); i++) {
                            qDebug() << "Running on test " << i;

                            QProcess runExec;
                            runExec.start(programePath);
                            if (!runExec.waitForStarted(2000)){
                                  qDebug() << "Program has not started on test " << i;
                                  s.error = "Running error.";
                                  s.accepted = 0;
                                  s.status = 2;

                                  break;


                            }else{
                                qDebug() << "Send input:" <<QString::fromStdString(tests[i].input.toStdString());

                                runExec.write(tests[i].input);

                                runExec.closeWriteChannel();

                                if (!runExec.waitForFinished(timeLimit)){

                                    qDebug() << "Error running on test: timout limit excecution" << i;
                                    s.error = "Time limit execution on test #"+QString::number(i+1);
                                    s.accepted = 0;
                                    s.status = 2;

                                    break;

                                }else{

                                    QByteArray result = runExec.readAll();

                                    // xoa dau xong la khong trong va cuoi la khoang trong. hay xuong dong.
                                    if(!result.isEmpty() && (result[result.size()-1] == '\n' || result[result.size()-1] == ' ')){
                                        result.remove(result.size()-1,1);
                                    }
                                    if(!result.isEmpty() && (result[0] == '\n' || result[0] == ' ')){
                                        result.remove(0,1);
                                    }

                                    qDebug() << "Result is matched:" << (result == tests[i].output);

                                    runExec.close();
                                    if(result == tests[i].output){
                                        // calculate score ....
                                        totalScore += tests[i].strength * maxScore / totalStrength;

                                    }else{
                                        s.error = "Wrong answer on test #" + QString::number(i+1);
                                        s.accepted = 0;
                                        s.status = 2;


                                    }


                                }

                            }


                        }

                        if(s.error.isEmpty() || s.error.isNull()){
                            s.accepted = 1;

                        }
                        s.status = 2;
                        s.score = totalScore;
                        contest->updateSubmission(s);


                }else{
                    s.error = "Complie error.";
                    s.accepted = 0;
                    s.status = 2;
                    s.score = 0;
                    contest->updateSubmission(s);

                }
            }

            QDir d(dir);
            d.removeRecursively(); // delete run test folder

            contest->submissionsQueue.pop();
        }

    }

}
