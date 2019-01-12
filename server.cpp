#include "server.h"

Server::Server(Contest *contest)
{

    this->contest = contest;
    this->http = new Ued::Http(contest);
}

void Server::run()
{
    http->run(8080);
}
