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
    Parser init;
    while (*iter != "}") {
        index++;
        ifFlyCommands.push_back(*iter);
        *iter++;
    }
    if (inter.interpretCondition(condition)) {
        init.Parse(ifFlyCommands);
    }
    *iter++;
    return (index + 1);
}
