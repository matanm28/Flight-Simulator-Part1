//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_SERVER_H
#define EX1_SERVER_H
#define IP "127.0.0.1"
#define DEFAULT_PORT 5400

#include "baseInclude.h"
#include "SymbolTable.h"
#include "Commands/DefineVarCommand.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

typedef chrono::time_point<chrono::high_resolution_clock> runTime;

class Server {
private:
    int serverSocket, port, client_socket;
    // we first need to create the sockaddr obj.
    //in means IP4
    sockaddr_in address;
    vector<thread *> threadVector;
    string simArr[NUM_OF_VARS_ON_XML];
    bool simBoolArr[NUM_OF_VARS_ON_XML] = {false};
    bool timePassed = false;
    runTime connectionStartTime;

public:
    Server(int port);

    void run();

private:
    void buildSimStringArray();

    int createSocket();

    bool listenAndWait();

    void readData();

    bool updateSymbolTable(const vector<float> &myNums);

    bool updateSymbolTable(float value, int varIndex);

    bool checkSimStatus(int index);

    static vector<string> splitString(string source, const string &delimiter);

    vector<float> convertToNums(vector<string> myVars);

    bool isTimePassed();
};


enum varNames {
    airSpeed = 0,
    altitude,
    pressure,
    indicatedPitch,
    roll,
    internalPitch,
    internalRoll,
    indicatedAltitude,
    presureAlt,
    gpsAltitude,
    gpsGroundSpeed,
    gpsVerticalSpeed,
    headingDeg,
    magnetic,
    slipSkid,
    turnRate,
    indicatedVerticalSpeed,
    aileron,
    elevator,
    rudder,
    flaps,
    throttle,
    engineRpm
};


#endif //EX1_SERVER_H
