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

    static vector<string> splitString(string source, const string &delimiter);

    vector<float> convertToNums(vector<string> myVars);
};


enum varNames {
    airspeed_indicator = 0,
    time_warp,
    switches_magnetos,
    heading_indicator,
    altimeter_indicated_altitude,
    altimeter_pressure_alt,
    attitude_indicator_indicated_pitch,
    attitude_indicator_indicated_roll,
    attitude_indicator_internal_pitch,
    attitude_indicator_internal_roll,
    encoder_indicated_altitude,
    encoder_pressure_alt,
    gps_indicated_altitude,
    gps_indicated_ground_speed,
    gps_indicated_vertical_speed,
    indicated_heading,
    magnetic_compass_indicated_heading,
    indicated_slip_skid,
    indicated_turn_rate,
    vertical_speed_indicator_indicated_speed,
    flight_aileron,
    flight_elevator,
    flight_rudder,
    flight_flaps,
    engine_throttle,
    current_engine_throttle,
    switches_master_avionics,
    switches_starter,
    active_engine_auto_start,
    flight_speedbrake,
    brake_parking,
    engine_primer,
    current_engine_mixture,
    switches_master_bat,
    switches_master_alt,
    engine_rpm
};


#endif //EX1_SERVER_H
