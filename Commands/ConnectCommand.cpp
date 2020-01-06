//
// Created by sapir on 17/12/2019.
//

#include "ConnectCommand.h"


int ConnectCommand::execute(vector<string>::iterator &iter) {
    string ip = *iter;
    iter++;
    Interpreter interpreter;
    int port;
    try {
        port = (int) interpreter.interpret(*iter)->calculate();
    } catch (char *c) {
        port = DEFAULT_CLIENT_PORT;
    } catch (exception *e) {
        port = DEFAULT_CLIENT_PORT;
    }
    Client *client = new Client(ip, port);
    client->runClient();
    iter++;
    return 3;
}
