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
        /*this->readData();*/
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
    string data, exactData;
    char buffer[256];
    int validRead, pos;
    while (true) {
        //reading from client
        bzero(buffer, 256);
        validRead = read(this->client_socket, buffer, 256);
        data.append(buffer, validRead);
        while (data.find('\n') == string::npos) {
            int currRead = 0;
            bzero(buffer, 256);
            currRead = read(this->client_socket, buffer, 256);
            validRead += currRead;
            data.append(buffer);
        }
        exactData = data.substr(0, data.find('\n'));
        data.erase(0, data.find('\n') + 1);
        vector<string> myVars = splitString(exactData, ",");
        vector<float> varsNums = this->convertToNums(myVars);
        this->updateSymbolTable(varsNums);
        std::cout << exactData << std::endl;

    }
}

bool Server::checkSimStatus(int index) {
    if (!this->simBoolArr[index]) {
        string key;//= SymbolTable::getSymbolTable()->varExists(this->simArr[index]);
        if (!key.empty()) {
            this->simArr[index] = key;
            this->simBoolArr[index] = true;
            return true;
        }
    }
    return false;
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
    simArr[airSpeed] = string("/instrumentation/airspeed-indicator/indicated-speed-kt");
    simArr[altitude] = string("/instrumentation/altimeter/indicated-altitude-ft");
    simArr[pressure] = string("/instrumentation/altimeter/pressure-alt-ft");
    simArr[indicatedPitch] = string("/instrumentation/attitude-indicator/indicated-pitch-deg");
    simArr[roll] = string("/instrumentation/attitude-indicator/indicated-roll-deg");
    simArr[internalPitch] = string("/instrumentation/attitude-indicator/internal-pitch-deg");
    simArr[internalRoll] = string("/instrumentation/attitude-indicator/internal-roll-deg");
    simArr[indicatedAltitude] = string("/instrumentation/encoder/indicated-altitude-ft");
    simArr[presureAlt] = string("/instrumentation/encoder/pressure-alt-ft");
    simArr[gpsAltitude] = string("/instrumentation/gps/indicated-altitude-ft");
    simArr[gpsGroundSpeed] = string("/instrumentation/gps/indicated-ground-speed-kt");
    simArr[gpsVerticalSpeed] = string("/instrumentation/gps/indicated-vertical-speed");
    simArr[headingDeg] = string("/instrumentation/heading-indicator/indicated-heading-deg");
    simArr[magnetic] = string("/instrumentation/magnetic-compass/indicated-heading-deg");
    simArr[slipSkid] = string("/instrumentation/slip-skid-ball/indicated-slip-skid");
    simArr[turnRate] = string("/instrumentation/turn-indicator/indicated-turn-rate");
    simArr[indicatedVerticalSpeed] = string("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    simArr[aileron] = string("/controls/flight/aileron");
    simArr[elevator] = string("/controls/flight/elevator");
    simArr[rudder] = string("/controls/flight/rudder");
    simArr[flaps] = string("/controls/flight/flaps");
    simArr[throttle] = string("/controls/engines/current-engine/throttle");
    simArr[engineRpm] = string("/engines/engine/rpm");
}

bool Server::isTimePassed() {
    if (!this->timePassed) {
        auto now = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::minutes>(now - this->connectionStartTime);
        if (duration.count() > MIN_MINUTES) {
            this->timePassed = true;
        }
    }
    return this->timePassed;
}
