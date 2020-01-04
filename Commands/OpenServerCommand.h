//
// Created by matan on 12/16/19.
//

#ifndef EX1_OPENSERVERCOMMAND_H
#define EX1_OPENSERVERCOMMAND_H

#include "Command.h"
#include "../Server.h"

class OpenServerCommand : public Command {
private:
    Server *server;
public:
    int execute(vector<string>::iterator &iter) override;

    virtual ~OpenServerCommand();
};


#endif //EX1_OPENSERVERCOMMAND_H
