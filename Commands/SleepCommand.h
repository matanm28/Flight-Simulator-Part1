//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_SLEEPCOMMAND_H
#define EX1_SLEEPCOMMAND_H

#include "Command.h"

class SleepCommand : public Command {
public:
    int execute() override;

};


#endif //EX1_SLEEPCOMMAND_H
