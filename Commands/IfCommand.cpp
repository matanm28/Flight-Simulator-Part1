//
// Created by sapir on 17/12/2019.
//

#include "IfCommand.h"

int IfCommand::execute(vector<string>::iterator &iter) {
    int index = 1;
    vector<string> ifFlyCommands;
    string condition = *iter;
    Interpreter inter;
    advance(iter, 2);
    index += 2;
    InitializeCommands init;

    while (*iter != "}") {
        index++;
        ifFlyCommands.push_back(*iter);
        *iter++;
    }
    while (inter.interpretCondition(condition)) {
        init.Parser(ifFlyCommands);
        break;
    }
    *iter++;
    return (index + 1);
}
