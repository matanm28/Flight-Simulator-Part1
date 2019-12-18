//
// Created by sapir on 18/12/2019.
//

#ifndef EX1_USEVARCOMMAND_H
#define EX1_USEVARCOMMAND_H

#include "Command.h"

class UseVarCommand : public Command {
public:
    int execute(vector<string>::iterator &iter) override;

};


#endif //EX1_USEVARCOMMAND_H
