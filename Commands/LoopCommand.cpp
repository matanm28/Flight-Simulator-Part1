//
// Created by sapir on 17/12/2019.
//

#include "LoopCommand.h"
#include "../InitializeCommands.h"

int LoopCommand::execute(vector<string>::iterator &iter) {
    int index = 0;
    vector<string> loopFlyCommands;
    iter++;
    index++;
    InitializeCommands init;
    //todo: take out loop condition
    while (*iter != "}") {
        index++;
        loopFlyCommands.push_back(*iter);
        *iter++;
    }
    //todo: add loop control
    while (true) {
        init.Parser(loopFlyCommands);
        break;
    }
    return index + 1;
}
