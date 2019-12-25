//
// Created by sapir on 17/12/2019.
//

#include "Parser.h"
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

Parser::Parser() {
    this->mapCommands.insert({"openDataServer", new OpenServerCommand()});
    this->mapCommands.insert({"connectControlClient", new ConnectCommand()});
    this->mapCommands.insert({"var", new DefineVarCommand()});
    this->mapCommands.insert({"useVar", new UseVarCommand()});
    this->mapCommands.insert({"Print", new PrintCommand()});
    this->mapCommands.insert({"Sleep", new SleepCommand()});
    this->mapCommands.insert({"while", new LoopCommand()});
    this->mapCommands.insert({"if", new IfCommand()});
}

void Parser::Parse(vector<string> flyCommands) {
    int index = 0;
    auto iter = flyCommands.begin();
    while (index < flyCommands.size()) {
        Command *c;
        if (mapCommands.find(flyCommands[index]) == mapCommands.cend()) {
            if (flyCommands[index] == "func1") { //implementaion func
                index += this->AddfuncToMap(++iter);
                c = nullptr;
            } else if (flyCommands[index] == "func2") { // func call
                index += this->FuncCall(++iter);
                c = nullptr;
            } else {
                c = mapCommands.find("useVar")->second;
            }
        } else {
            c = mapCommands.find(flyCommands[index])->second;
        }
        if (c != nullptr) {
            index += c->execute(++iter);
        }
    }
}

int Parser::AddfuncToMap(vector<string>::iterator &iter) {
    int index = 1;
    int count = 0;
    string funcName = *iter;
    iter++;
    vector<string> funcCommands;
    while (true) {
        if (*iter == "if") {
            count++;
        }
        if (*iter == "while") {
            count++;
        }
        if (*iter == "}") {
            --count;
            if (count == -1) {
                funcCommands.push_back(*iter);
                iter++;
                index++;
                break;
            }
        }
        funcCommands.push_back(*iter);
        iter++;
        index++;
    }
    this->mapFunctions.insert({funcName, funcCommands});
    return index + 1;
}

int Parser::FuncCall(vector<string>::iterator &iter) {
    vector<string> funcCommands = this->mapFunctions.find(*iter)->second;
    //todo: check null
    int index = 0;
    auto itFunc = funcCommands.begin();
    vector<string> vars;
    vector<string> forParse;
    Command *c = new DefineVarCommand;
    while (*itFunc != "{") {
        vars.push_back(*itFunc);
        vars.push_back(*(++itFunc));
        vars.push_back("=");
        vars.push_back(*(++iter));
        iter++;
        itFunc++;
    }
    itFunc++;
    auto itVar = vars.begin();
    while (index < vars.size()) {
        index += c->execute(++itVar);
    }
    int count = 0;
    while (true) {
        if (*itFunc == "{") {
            count++;
        }
        if (*itFunc == "}") {
            --count;
            if (count == -1) {
                break;
            }
        }
        forParse.push_back(*itFunc);
        itFunc++;
    }
    this->Parse(forParse);
    return 3;
}
