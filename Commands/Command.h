//
// Created by matan on 12/16/19.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include "../baseInclude.h"

class Command {
public:
    virtual int execute(vector<string>::iterator &iter) = 0;

    virtual ~Command() = default;
};


#endif //EX3_COMMAND_H
