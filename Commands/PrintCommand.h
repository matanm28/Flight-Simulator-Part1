//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_PRINTCOMMAND_H
#define EX1_PRINTCOMMAND_H

#include "Command.h"
#include <stdio.h>

class PrintCommand : public Command {
public:
    int execute(vector<string>::iterator &iter) override;

};


#endif //EX1_PRINTCOMMAND_H
