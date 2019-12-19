//
// Created by sapir on 18/12/2019.
//
#include <algorithm>
#include "UseVarCommand.h"
#include "../SymbolTable.h"

int UseVarCommand::execute(vector<string>::iterator &iter) {
    iter--;
    string nameVar = *iter;
    advance(iter, 2);
    SymbolTable *st = SymbolTable::getSymbolTable();
    //TODO: add try catch value = 0
    float value = stof(*iter);
    //TODO: USE INTERPUTER
    st->setVarByName(nameVar, value);
    iter++;
    return 3;
}
