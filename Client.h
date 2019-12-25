//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_CLIENT_H
#define EX1_CLIENT_H

#include <sys/socket.h>
#include <strings.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "baseInclude.h"
#include "Var.h"
#include "SymbolTable.h"

typedef chrono::time_point<chrono::high_resolution_clock> runTime;

class Client {
private:
    int clientSocket, destPort;
    string destIp;
    sockaddr_in address;
    vector<thread *> threadVector;
    bool timePassed = false;
    runTime firstConnectionStartTime;

public:
    Client(string ip, int port);

    void runClient();

private:
    //functions:
    static int createSocket();

    bool establishConnection();

    void sendData();

    static string turnVarToData(Var *var);

    static vector<string> createCommandsVector();

    void isTimePassed();

    bool getTimePassed();
};


#endif //EX1_CLIENT_H
