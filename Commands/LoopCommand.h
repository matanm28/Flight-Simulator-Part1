//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_LOOPCOMMAND_H
#define EX1_LOOPCOMMAND_H

#include "ConditionParser.h"
#include "../Parser.h"
#include "../Interpreter/Interpreter.h"
#include <algorithm>


class LoopCommand : public ConditionParser {
public:
    int execute(vector<string>::iterator &iter) override;

};


#endif //EX1_LOOPCOMMAND_H
