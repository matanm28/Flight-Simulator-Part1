//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_CONNECTCOMMAND_H
#define EX1_CONNECTCOMMAND_H

#include "Command.h"

class ConnectCommand : public Command {
public:
    int execute(vector<string>::iterator &iter) override;

};


#endif //EX1_CONNECTCOMMAND_H
