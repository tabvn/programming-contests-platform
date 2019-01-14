#ifndef SERVER_H
#define SERVER_H

#include "http.h"
#include <QThread>
#include "contest.h"

class Server : public QThread
{

public:
    Server(Contest* contest = nullptr);

private:

    Ued::Http *http;
    Contest *contest;

protected:

    void run();
};

#endif // SERVER_H
