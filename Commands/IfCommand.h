//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_IFCOMMAND_H
#define EX1_IFCOMMAND_H

#include "ConditionParser.h"

class IfCommand : public ConditionParser {
public:
    int execute() override;

};


#endif //EX1_IFCOMMAND_H
