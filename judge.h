#ifndef JUDGE_H
#define JUDGE_H

#include "contest.h"

using namespace Ued;

class Judge : public QThread
{
public:
    Judge(Contest* contest = nullptr);
    bool stopped = false;

private:
    Contest *contest;
protected:

    void run();
};


#endif // JUDGE_H
