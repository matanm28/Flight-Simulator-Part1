//
// Created by sapir on 17/12/2019.
//

#ifndef EX1_SYMBOLTABLE_H
#define EX1_SYMBOLTABLE_H

#include "baseInclude.h"
#include "Commands/Command.h"
#include "Var.h"

class SymbolTable {
private:
    static SymbolTable *unifiedSymbolTable;
    mutex simToVarLock;
    mutex nameToVarLock;
    map<string, Var *> nameToVar;
    map<string, Var *> simToVar;

    SymbolTable();

public:
    static SymbolTable *getSymbolTable();

    bool updateSymboleTable(vector<float> myNums);

    bool updateSymboleTable(float value, int varIndex);

    //todo: change return type for adders and setters to bool
    //upon success return true otherwise return false
    void addVar(string varName, string sim, string direction, float value);

    void addVar(string varName, float value);

    void addVar(string varName, string sim, string direction);

    void addVar(string varName, Var *var);

    void setVarByName(string varName, float value);

    void setVarBySim(string sim, float value);

    Var getVar(string varName);

    string varExists(string sim);


};


#endif //EX1_SYMBOLTABLE_H
