//
// Created by sapir on 17/12/2019.
//

#include "DefineVarCommand.h"
#include "../SymbolTable.h"
#include <algorithm>

int DefineVarCommand::execute(vector<string>::iterator &iter) {
    SymbolTable *st = SymbolTable::getSymbolTable();
    string nameVar, direction, oldVar, sim;
    float value;
    nameVar = *iter;
    iter++;
    if (*iter == "=") {
        iter++;
        oldVar = *iter;
        //what if null
        value = st->getVar(oldVar).getValue();
        st->addVar(nameVar, value);
        iter++;
        return 3;
    } else {
        direction = *iter;
        advance(iter, 2);
        sim = *iter;
        st->addVar(nameVar, sim, direction);
        iter++;
        return 5;
    }
}

int DefineVarCommand::execute(const string &name, const string &sim, const string &direction, float value) {
    SymbolTable::getSymbolTable()->addVar(name, sim, direction, value);
}
