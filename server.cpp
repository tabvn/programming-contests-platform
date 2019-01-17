#include "server.h"


Server::Server(Contest *contest)
{
    this->contest = contest;
    this->http = new Ued::Http(this->contest);
}

void Server::run()
{
    if(this->contest == nullptr){
        return;
    }

    http->run(this->contest->port);
}
