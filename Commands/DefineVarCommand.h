//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_DEFINEVARCOMMAND_H
#define EX1_DEFINEVARCOMMAND_H

#include "Command.h"

class DefineVarCommand : public Command {
public:
    int execute(vector<string>::iterator &iter) override;

    int execute(const string &name, const string &sim, const string &direction, float value);
};


#endif //EX1_DEFINEVARCOMMAND_H
