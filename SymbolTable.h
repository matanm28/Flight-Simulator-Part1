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
    map<string, Var> varTable;
    int size = 0;

public:
    SymbolTable();
};


#endif //EX1_SYMBOLTABLE_H
