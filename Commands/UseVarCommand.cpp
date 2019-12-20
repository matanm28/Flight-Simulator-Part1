//
// Created by sapir on 18/12/2019.
//
#include "UseVarCommand.h"

//[nameVar] = Expression
int UseVarCommand::execute(vector<string>::iterator &iter) {
    iter--;
    SymbolTable *st = SymbolTable::getSymbolTable();
    string nameVar = *iter;
    Interpreter in;
    advance(iter, 2);
    string strExp = *iter;
    float value;
    try {
        Expression *ex = in.interpret(strExp);
        value = ex->calculate();
    } catch (const exception &e) {
        *iter--;
        value = 0;
    }
    st->setVarByName(nameVar, value);
    iter++;
    return 3;
}
