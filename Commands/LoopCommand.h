//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_LOOPCOMMAND_H
#define EX1_LOOPCOMMAND_H

#include "ConditionParser.h"

class LoopCommand : public ConditionParser {
public:
    int execute() override;

};


#endif //EX1_LOOPCOMMAND_H
