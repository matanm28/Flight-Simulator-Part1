//
// Created by sapir on 17/12/2019.
//

#include "LoopCommand.h"

int LoopCommand::execute(vector<string>::iterator &iter) {
    int index = 1;
    vector<string> loopFlyCommands;
    string condition = *iter;
    Interpreter inter;
    advance(iter, 2);
    index += 2;
    Parser init;
    while (*iter != "}") {
        index++;
        loopFlyCommands.push_back(*iter);
        *iter++;
    }
    while (inter.interpretCondition(condition)) {
        init.Parse(loopFlyCommands);
    }
    *iter++;
    return (index + 1);
}
