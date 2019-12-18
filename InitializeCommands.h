//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_INITIALIZECOMMANDS_H
#define EX1_INITIALIZECOMMANDS_H

#include <string>
#include <map>
#include "Commands/Command.h"

class InitializeCommands {
    map<string, Command *> mapCommands;
public:
    void CreateMap();

    void Parser(vector<string> flyCommands);

};


#endif //EX1_INITIALIZECOMMANDS_H
