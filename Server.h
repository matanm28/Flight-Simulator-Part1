//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_SERVER_H
#define EX1_SERVER_H
#define IP '127.0.0.1'

#include "baseInclude.h"

class Server {
private:
    int socket, port;
    string ip;
public:
    Server(int port);

    void intializeData();

    int initServer(int argc, char const *argv[]);
};


#endif //EX1_SERVER_H
