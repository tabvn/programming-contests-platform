#include "server.h"


Server::Server(Contest *contest)
{
    this->contest = contest;
    this->http = new Ued::Http(this->contest);

    contest->subscribe("closeServer", [&](QVariant){
       this->http->stop();
    });

}

void Server::run()
{
    if(this->contest == nullptr){
        return;
    }

    http->run(this->contest->port);
}
