//
// Created by matan on 12/16/19.
//

#include "OpenServerCommand.h"


int OpenServerCommand::execute(vector<string>::iterator &iter) {
    Interpreter interpreter;
    int port;
    try {
        port = (int) interpreter.interpret(*iter)->calculate();
    } catch (char *c) {
        port = DEFAULT_PORT;
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
