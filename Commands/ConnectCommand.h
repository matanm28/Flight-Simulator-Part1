//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_CONNECTCOMMAND_H
#define EX1_CONNECTCOMMAND_H
#define DEFAULT_CLIENT_PORT 5402

#include "Command.h"
#include "../Client.h"

class ConnectCommand : public Command {
public:
    int execute(vector<string>::iterator &iter) override;

};


#endif //EX1_CONNECTCOMMAND_H
