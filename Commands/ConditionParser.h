//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_CONDITIONPARSER_H
#define EX1_CONDITIONPARSER_H

#include "Command.h"

class ConditionParser : public Command {
public:
    virtual int execute() = 0;
};


#endif //EX1_CONDITIONPARSER_H
