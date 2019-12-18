//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_SERVER_H
#define EX1_SERVER_H
#define IP "127.0.0.1"

#include "baseInclude.h"

class Server {
private:
    int serverSocket, port, client_socket;
    // we first need to create the sockaddr obj.
    //in means IP4
    // struct sockaddr_in address;
    string ip;

public:
    Server(int port);

    void intializeData();

    void readData();

private:
    int createSocket();

    int listenAndWait();

    vector<string> splitString(string source, const string &delimiter);

    vector<double> convertToNums(vector<string> myVars);

};


enum varNames {
    airSpeed,
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
