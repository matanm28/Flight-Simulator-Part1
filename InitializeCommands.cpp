//
// Created by sapir on 17/12/2019.
//

#include "InitializeCommands.h"
#include "Commands/OpenServerCommand.h"
#include "Commands/ConnectCommand.h"
#include "Commands/DefineVarCommand.h"
#include "Commands/IfCommand.h"
#include "Commands/LoopCommand.h"
#include "Commands/PrintCommand.h"
#include "Commands/SleepCommand.h"
#include "Commands/UseVarCommand.h"
#include "Commands/Command.h"

#include <string.h>
#include <stdio.h>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

InitializeCommands::InitializeCommands() {
    this->mapCommands.insert({"openDataServer", new OpenServerCommand()});
    this->mapCommands.insert({"connectControlClient", new ConnectCommand()});
    this->mapCommands.insert({"var", new DefineVarCommand()});
    this->mapCommands.insert({"useVar", new UseVarCommand()});
    this->mapCommands.insert({"Print", new PrintCommand()});
    this->mapCommands.insert({"Sleep", new SleepCommand()});
    this->mapCommands.insert({"while", new LoopCommand()});
    this->mapCommands.insert({"if", new IfCommand()});
}

void InitializeCommands::Parser(vector<string> flyCommands) {
    int index = 0;
    auto iter = flyCommands.begin();
    while (index < flyCommands.size()) {
        Command *c;
        if (mapCommands.find(flyCommands[index]) == mapCommands.cend()) {
            c = mapCommands.find("usrVar")->second;
        } else {
            c = mapCommands.find(flyCommands[index])->second;
        }
        if (c != nullptr) {
            index += c->execute(++iter);
        }
    }
}
