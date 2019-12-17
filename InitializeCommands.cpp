//
// Created by sapir on 17/12/2019.
//

#include "InitializeCommands.h"
#include "Commands/OpenServerCommand.h"
#include "Commands/DefineVarCommand.h"
#include "Commands/IfCommand.h"
#include "Commands/LoopCommand.h"
#include "Commands/PrintCommand.h"
#include "Commands/SleepCommand.h"
#include "Commands/Command.h"

#include <string.h>
#include <stdio.h>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

void InitializeCommands::CreateMap() {
    this->mapCommands.insert({"openDataServer", new OpenServerCommand()});
    this->mapCommands.insert({"connectControlClient", new OpenServerCommand()});
    this->mapCommands.insert({"var", new DefineVarCommand()});
    this->mapCommands.insert({"Print", new PrintCommand()});
    this->mapCommands.insert({"Sleep", new SleepCommand()});
    this->mapCommands.insert({"while", new LoopCommand()});
    this->mapCommands.insert({"if", new IfCommand()});
}

void InitializeCommands::Parser(list<string> flyCommands) {
    int index = 0;
    while (index < flyCommands.size()) {
        auto iter = flyCommands.cbegin();
        advance(iter, index);
        Command *c = mapCommands.find(*iter)->second;
        if (c != nullptr) {
            index += c->execute();
        }
    }
}
