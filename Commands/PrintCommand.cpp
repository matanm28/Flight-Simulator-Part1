//
// Created by sapir on 17/12/2019.
//

#include "PrintCommand.h"

int PrintCommand::execute(vector<string>::iterator &iter) {
    int size = (*iter).size();
    if ((*iter).at(0) == '\"' && (*iter).at(size - 1) == '\"') {
        cout << (*iter).substr(1, size - 2) << endl;
    } else {
        SymbolTable *st = SymbolTable::getSymbolTable();
        Var v = st->getVar(*iter);
        //todo: check if v is val
        cout << v.getValue() << endl;
    }
    iter++;
    return 2;
}
