//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_IFCOMMAND_H
#define EX1_IFCOMMAND_H

#include "ConditionParser.h"
#include "../Interpreter/Interpreter.h"
#include "../Parser.h"

class IfCommand : public ConditionParser {
public:
    int execute(vector<string>::iterator &iter) override;

};


#endif //EX1_IFCOMMAND_H
