#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include "Server.h"
#include "SymbolTable.h"

#define PORT 8081


Server::Server(int port) {
    this->port = port;
    this->socket = this->createSocket();
    if (this->socket == -1 || this->socket == -2) {
        exit(this->socket);
    }

}

int Server::listenAndWait() {
    // accepting a client
    this->client_socket = accept(this->socket, (struct sockaddr *) &this->address,
                                 (socklen_t *) &this->address);

    if (this->client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }
    close(this->socket); //closing the listening socket
}

void Server::intializeData() {

}

void Server::readData() {
    //reading from client
    char buffer[1024] = {0};
    int valread = read(this->client_socket, buffer, 1024);
    string source((const char *) buffer);
    vector<string> myVars = this->splitString(source, ",");
    vector<double> varsNums = this->convertToNums(myVars);
    //take symbol table and update
    std::cout << buffer << std::endl;
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
    // we first need to create the sockaddr obj.
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my mach->>>ne
    this->address.sin_port = htons(PORT);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }
    return socketfd;
}

vector<double> Server::convertToNums(vector<string> myVars) {
    vector<double> myNums;
    for (string str :myVars) {
        try {
            myNums.push_back(stod(str));
        } catch (exception e) {
            cerr << "Failed for: " + str << endl;
            exit(-1);
        }
    }
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