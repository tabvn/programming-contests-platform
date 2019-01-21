#ifndef EXPORT_H
#define EXPORT_H

#include <QString>
#include <xlsxwriter.h>
#include "contest.h"
#include <QByteArray>
#include <QDebug>
#include <QVector>

using namespace Ued;

namespace Ued {

struct Export{

    void xls(Contest *contest, QString filename){



            QByteArray ba = filename.toLocal8Bit();


            lxw_workbook  *workbook  = workbook_new(ba.data());
            lxw_worksheet *scoreboardSheet = workbook_add_worksheet(workbook, "Scoreboard");
            lxw_worksheet *userSheet = workbook_add_worksheet(workbook, "Users");

            lxw_format *format = workbook_add_format(workbook);
            format_set_bold(format);

            worksheet_set_column(scoreboardSheet, 0, 0, 5, nullptr);
            worksheet_set_column(scoreboardSheet, 0, 1, 15, nullptr);

            worksheet_set_column(userSheet, 0, 0, 5, nullptr);
            worksheet_set_column(userSheet, 0, 1, 15, nullptr);
            worksheet_set_column(userSheet, 0, 3, 10, nullptr);



            QVector<Scoreboard> scores = contest->getScoreboards();
            QVector<Problem> problems = contest->getProblems();

            worksheet_write_string(scoreboardSheet, 0, 0, "ID", format);
            worksheet_write_string(scoreboardSheet, 0, 1, "Name", format);
            worksheet_write_string(scoreboardSheet, 0, 2, "Class", format);
            // load problems

            uint32_t columns = 0;

            for(int i = 0; i < problems.size(); i++){
                columns = uint32_t(i) + 3;
                worksheet_write_string(scoreboardSheet, 0, columns, problems[i].name.toLocal8Bit().data(), format);
            }

            columns++;

            worksheet_write_string(scoreboardSheet, 0, columns, "Score", format);



            // write row
            uint32_t row = 1;
            columns = 0;
            for(int i = 0; i < scores.size(); i++){
               worksheet_write_number(scoreboardSheet, row, 0, scores[i].userId, nullptr);
               worksheet_write_string(scoreboardSheet, row, 1, scores[i].name.toLocal8Bit().data(), nullptr);
               worksheet_write_string(scoreboardSheet, row, 2, scores[i].className.toLocal8Bit().data(), nullptr);

               columns = 3;
               for(int j = 0; j < problems.size(); j++){
                   int userScore = 0;
                   for (int k=0;k < scores[i].problems.size();k++) {
                       if(scores[i].problems[k].name == problems[i].name){
                           userScore = scores[i].problems[k].score;
                           break;
                       }
                   }

                   worksheet_write_number(scoreboardSheet, row, columns, userScore, nullptr);
                   columns++;
               }

               worksheet_write_number(scoreboardSheet, row, columns, scores[i].total, nullptr);
               row++;
            }

            // sheets for users


            worksheet_write_string(userSheet, 0, 0, "ID", format);
            worksheet_write_string(userSheet, 0, 1, "Name", format);
            worksheet_write_string(userSheet, 0, 2, "Class", format);
            worksheet_write_string(userSheet, 0, 3, "Birthday", format);
            worksheet_write_string(userSheet, 0, 4, "Email", format);

            QVector<User> users = contest->getUsers();

            row = 1;
            QString name;
            for (int i = 0; i < users.size(); i++) {
                worksheet_write_number(userSheet, row, 0, users[i].id, nullptr);
                name = users[i].lastname +" "+ users[i].firstname;
                worksheet_write_string(userSheet, row, 1, name.toLocal8Bit().data(), format);
                worksheet_write_string(userSheet, row, 2, users[i].className.toLocal8Bit().data(), nullptr);
                worksheet_write_string(userSheet, row, 3, users[i].birthday.toString("dd/MM/yyyy").toLocal8Bit().data(), nullptr);
                worksheet_write_string(userSheet, row, 4, users[i].email.toLocal8Bit().data(), nullptr);
                row++;
            }

            workbook_close(workbook);


    }
};

}
#endif // EXPORT_H
