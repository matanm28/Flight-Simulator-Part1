//
// Created by matan on 12/16/19.
//

#include "OpenServerCommand.h"


int OpenServerCommand::execute(vector<string>::iterator &iter) {
    int port;
    try {
        port = stoi(*iter);
    } catch (exception *e) {
        port = DEFAULT_PORT;
    }
    this->server = new Server(port);
    this->server->run();
    iter++;
    return 2;
}

OpenServerCommand::~OpenServerCommand() {

}
