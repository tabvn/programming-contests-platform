#ifndef JUDGE_H
#define JUDGE_H

#include "contest.h"
class Judge : public QThread
{
public:
    Judge(Contest* contest = nullptr);

private:
    Contest *contest;
protected:

    void run();
};


#endif // JUDGE_H
