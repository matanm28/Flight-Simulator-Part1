//
// Created by sapir on 17/12/2019.
//

#include "ConnectCommand.h"


int ConnectCommand::execute(vector<string>::iterator &iter) {
    string ip = *iter;
    iter++;
    int port = stoi(*iter);
    Client *client = new Client(ip, port);
    client->runClient();
    iter++;
    return 3;
}
