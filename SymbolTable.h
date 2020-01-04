//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_SYMBOLTABLE_H
#define EX1_SYMBOLTABLE_H

#include <mutex>
#include <map>

#include "Commands/Command.h"
#include "Var.h"
#include "Client.h"

class SymbolTable {
private:
    static SymbolTable *unifiedSymbolTable;
    mutex simToVarLock;
    mutex nameToVarLock;
    map<string, Var *> nameToVar;
    map<string, Var *> simToVar;
    queue<string> clientCommands;

    SymbolTable();

public:
    static SymbolTable *getSymbolTable();

    void addVar(string varName, string sim, string direction, float value);

    void addVar(string varName, float value);

    void addVar(string varName, string sim, string direction);

    void setVarByName(string varName, float value);

    void setVarBySim(string sim, float value);

    queue<string> *getClientCommands();

    vector<Var *> getNameToVar();

    Var getVar(string varName);

    Var getVarBySim(string sim);


};


#endif //EX1_SYMBOLTABLE_H
