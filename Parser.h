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
public:
    Parser();

    void CreateMap();

    void Parse(vector<string> flyCommands);

};


#endif //EX1_PARSER_H
