//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_PARSER_H
#define EX1_PARSER_H

#include <string>
#include <map>
#include "Commands/Command.h"

class Parser {
    map<string, Command *> mapCommands;
    map<string, vector<string>> mapFunctions;
public:
    Parser();

    void Parse(vector<string> flyCommands);

    int AddfuncToMap(vector<string>::iterator &iter);

    int FuncCall(vector<string>::iterator &iter);

};


#endif //EX1_PARSER_H
