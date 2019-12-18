//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_SYMBOLTABLE_H
#define EX1_SYMBOLTABLE_H

#include "baseInclude.h"
#include "Commands/Command.h"
#include "Var.h"
#include "Server.h"

class SymbolTable {
private:
    static SymbolTable *unifiedSymbolTable;
    mutex mutexLock;
    string simArr[23];
    map<string, Var *> mapOfVar;

    SymbolTable();

    void buildSimStringArray();

public:
    static SymbolTable *getSymbolTable();

    bool updateSymboleTable(vector<float> myNums);

    bool updateSymboleTable(float value, int varIndex);

    void addVar(string varName, string sim, string direction, float value);

    void addVar(string varName, float value);

    void addVar(string varName, string sim, string direction);

    void addVar(string varName, Var *var);

    void setVar(string varName, float value);

    Var getVar(string varName);


};


#endif //EX1_SYMBOLTABLE_H
