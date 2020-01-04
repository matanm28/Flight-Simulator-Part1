#include "Server.h"


Server::Server(int port) {
    this->port = port;
    this->buildSimStringArray();
    this->serverSocket = this->createSocket();
    if (this->serverSocket == -1 || this->serverSocket == -2 || this->serverSocket == -3) {
        exit(this->serverSocket);
    }
}

void Server::run() {
    if (this->listenAndWait()) {
        this->connectionStartTime = chrono::high_resolution_clock::now();
        thread *receiveData = new thread(&Server::readData, this);
        this->threadVector.push_back(receiveData);
        receiveData->detach();
    }
}

bool Server::listenAndWait() {
    // accepting a client
    int addressLength = sizeof(this->address);
    this->client_socket = accept(this->serverSocket, (struct sockaddr *) &(this->address),
                                 (socklen_t *) &addressLength);
    if (this->client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return false;
    }
    std::cout << "Server is now connected" << std::endl;
    close(this->serverSocket); //closing the listening socket
    return true;
}

void Server::readData() {
    string data, exactData, prevData;
    char buffer[BUFFER_SIZE];
    int validRead;
    while (true) {
        //reading from client
        bzero(buffer, BUFFER_SIZE);
        validRead = read(this->client_socket, buffer, BUFFER_SIZE);
        data.append(buffer, validRead);
        while (data.find('\n') == string::npos) {
            int currRead = 0;
            bzero(buffer, BUFFER_SIZE);
            currRead = read(this->client_socket, buffer, BUFFER_SIZE);
            validRead += currRead;
            data.append(buffer, currRead);
        }
        exactData = data.substr(0, data.find('\n'));
        data.erase(0, data.find('\n') + 1);
        vector<string> myVars = splitString(exactData, ",");
        vector<float> varsNums = this->convertToNums(myVars);
        this->updateSymbolTable(varsNums);
        //std::cout << exactData << std::endl;

    }
}

bool Server::updateSymbolTable(const vector<float> &myNums) {
    bool flag = true;
    int index = 0;
    for (float value : myNums) {
        flag = this->updateSymbolTable(value, index % NUM_OF_VARS_ON_XML);
        index++;
    }
    return flag;
}

bool Server::updateSymbolTable(float value, int varIndex) {
    //todo: add if to check if set action was successful
    SymbolTable::getSymbolTable()->setVarBySim(this->simArr[varIndex], value);
    //todo: check if needed
}

int Server::createSocket() {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    //bind socket to IP address
    //create the sockaddr obj.
    this->address.sin_family = AF_INET;
    //give me any IP allocated for my machine
    this->address.sin_addr.s_addr = INADDR_ANY;
    //convert our port to a number that the network understands.
    this->address.sin_port = htons(this->port);

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1) {
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }
    return socketfd;
}

vector<float> Server::convertToNums(vector<string> myVars) {
    vector<float> myNums;
    for (string str :myVars) {
        float num;
        try {
            num = stof(str);
        } catch (exception &e) {
            cerr << "Failed for: " + str << endl;
            num = 0;
        }
        myNums.push_back(num);
    }
    return myNums;
}

vector<string> Server::splitString(string source, const string &delimiter) {
    vector<string> tokensList;
    size_t pos = 0;
    string token;
    while ((pos = source.find(delimiter)) != std::string::npos) {
        token = source.substr(0, pos);
        tokensList.push_back(token);
        source.erase(0, pos + delimiter.length());
    }
    tokensList.push_back(source);
    return tokensList;

}

void Server::buildSimStringArray() {
    //make and array of sim's based on generic_small.xml - Hard Coded
    simArr[airspeed_indicator] = string("/instrumentation/airspeed-indicator/indicated-speed-kt");
    simArr[time_warp] = string("/sim/time/warp");
    simArr[switches_magnetos] = string("/controls/switches/magnetos");
    simArr[heading_indicator] = string("/instrumentation/heading-indicator/offset-deg");
    simArr[altimeter_indicated_altitude] = string("/instrumentation/altimeter/indicated-altitude-ft");
    simArr[altimeter_pressure_alt] = string("/instrumentation/altimeter/pressure-alt-ft");
    simArr[attitude_indicator_indicated_pitch] = string("/instrumentation/attitude-indicator/indicated-pitch-deg");
    simArr[attitude_indicator_indicated_roll] = string("/instrumentation/attitude-indicator/indicated-roll-deg");
    simArr[attitude_indicator_internal_pitch] = string("/instrumentation/attitude-indicator/internal-pitch-deg");
    simArr[attitude_indicator_internal_roll] = string("/instrumentation/attitude-indicator/internal-roll-deg");
    simArr[encoder_indicated_altitude] = string("/instrumentation/encoder/indicated-altitude-ft");
    simArr[encoder_pressure_alt] = string("/instrumentation/encoder/pressure-alt-ft");
    simArr[gps_indicated_altitude] = string("/instrumentation/gps/indicated-altitude-ft");
    simArr[gps_indicated_ground_speed] = string("/instrumentation/gps/indicated-ground-speed-kt");
    simArr[gps_indicated_vertical_speed] = string("/instrumentation/gps/indicated-vertical-speed");
    simArr[indicated_heading] = string("/instrumentation/heading-indicator/indicated-heading-deg");
    simArr[magnetic_compass_indicated_heading] = string("/instrumentation/magnetic-compass/indicated-heading-deg");
    simArr[indicated_slip_skid] = string("/instrumentation/slip-skid-ball/indicated-slip-skid");
    simArr[indicated_turn_rate] = string("/instrumentation/turn-indicator/indicated-turn-rate");
    simArr[vertical_speed] = string("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    simArr[flight_aileron] = string("/controls/flight/aileron");
    simArr[flight_elevator] = string("/controls/flight/elevator");
    simArr[flight_rudder] = string("/controls/flight/rudder");
    simArr[flight_flaps] = string("/controls/flight/flaps");
    simArr[engine_throttle] = string("/controls/engines/engine/throttle");
    simArr[current_engine_throttle] = string("/controls/engines/current-engine/throttle");
    simArr[switches_master_avionics] = string("/controls/switches/master-avionics");
    simArr[switches_starter] = string("/controls/switches/starter");
    simArr[active_engine_auto_start] = string("/engines/active-engine/auto-start");
    simArr[flight_speedbrake] = string("/controls/flight/speedbrake");
    simArr[brake_parking] = string("/sim/model/c172p/brake-parking");
    simArr[engine_primer] = string("/controls/engines/engine/primer");
    simArr[current_engine_mixture] = string("/controls/engines/current-engine/mixture");
    simArr[switches_master_bat] = string("/controls/switches/master-bat");
    simArr[switches_master_alt] = string("/controls/switches/master-alt");
    simArr[engine_rpm] = string("/engines/engine/rpm");
}


