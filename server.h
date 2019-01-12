#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include "http.h"
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
