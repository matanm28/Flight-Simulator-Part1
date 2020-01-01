
#include "Client.h"


Client::Client(string ip, int port) {
    this->destIp = ip;
    this->destPort = port;
    //We need to create a sockaddr obj to hold address of server
    this->address.sin_family = AF_INET;//IP4
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.
    this->address.sin_addr.s_addr = inet_addr(this->destIp.c_str());  //the destination address
    this->address.sin_port = htons(port);
    this->clientSocket = createSocket();
}

int Client::createSocket() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    return client_socket;
}


void Client::runClient() {
    if (this->establishConnection()) {
        thread *dataSender = new thread(&Client::sendDataWithQueue, this);
        this->threadVector.push_back(dataSender);
        dataSender->detach();
    }
}

bool Client::establishConnection() {
    int addressLength = sizeof(this->address);
    bool connectionEstablished = false, reportError = true;
    this->firstConnectionStartTime = chrono::high_resolution_clock::now();
    while (!(connectionEstablished || this->getTimePassed())) {
        int is_connect = connect(this->clientSocket, (struct sockaddr *) &(this->address), (socklen_t) addressLength);
        if (is_connect == -1) {
            if (reportError) {
                std::cerr << "Could not connect to host server" << std::endl;
                reportError = false;
            }
        } else {
            std::cout << "Client is now connected to server" << std::endl;
            connectionEstablished = true;
        }
    }
    if (this->timePassed) {
        std::cerr << "Timeout on client connection" << std::endl;
        return false;
    }
    return true;
}

void Client::sendData() {
    while (true) {
        vector<string> dataVector = createCommandsVector();
        for (string data : dataVector) {
            int is_sent = send(this->clientSocket, data.c_str(), data.size(), 0);
            if (is_sent == -1) {
                std::cout << "Error sending message" << std::endl;
            } else {
                std::cout << data.substr(0, data.find('\r')) + " sent to server" << std::endl;
            }
        }
    }
}

void Client::sendDataWithQueue() {
    while (true) {
        queue<string> *clientCommands = SymbolTable::getSymbolTable()->getClientCommands();
        while (!clientCommands->empty()) {
            string data = clientCommands->front();
            clientCommands->pop();
            int is_sent = send(this->clientSocket, data.c_str(), data.size(), 0);
            if (is_sent == -1) {
                std::cout << "Error sending message" << std::endl;
            } /*else {
                std::cout << data.substr(0, data.find('\r')) + " sent to server" << std::endl;
            }*/
        }
    }
}

vector<string> Client::createCommandsVector() {
    vector<string> dataVector;
    for (Var *var : SymbolTable::getSymbolTable()->getNameToVar()) {
        if (var->getDirection() == "->" && var->hasNewValue()) {
            dataVector.push_back(turnVarToData(var));
            var->valueUsed();
        }
    }
    return dataVector;
}

string Client::turnVarToData(Var *var) {
    string data = "set ";
    data.append(var->getSim() + " " + to_string(var->getValue()) + " \r\n");
    return data;
}

void Client::isTimePassed() {
    auto now = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(now - this->firstConnectionStartTime);
    if (duration.count() > MAX_SECONDS_FOR_CONNECTION) {
        this->timePassed = true;
    }
}

bool Client::getTimePassed() {
    this->isTimePassed();
    return this->timePassed;
}
