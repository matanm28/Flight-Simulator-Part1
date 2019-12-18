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
    mutex mutexLock;
    string simArr[23];
    map<string, Var> varTable;
    int size = 0;

public:
    SymbolTable();

    bool updateSymboleTable(vector<double> myNums);

    bool updateSymboleTable(double value, int varIndex);

private:
    void buildSimStringArray();
};


#endif //EX1_SYMBOLTABLE_H
