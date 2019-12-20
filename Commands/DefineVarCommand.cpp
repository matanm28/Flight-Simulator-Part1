//
// Created by sapir on 17/12/2019.
//

#include "DefineVarCommand.h"
#include "../SymbolTable.h"
#include <algorithm>
#include "../Interpreter/ex1.h"
#include "../Interpreter/ex1.h"

int DefineVarCommand::execute(vector<string>::iterator &iter) {
    SymbolTable *st = SymbolTable::getSymbolTable();
    string nameVar, direction, strExp, sim;
    Interpreter in;
    float value;
    nameVar = *iter;
    iter++;
    //var [nameVar] = Expression
    if (*iter == "=") {
        iter++;
        //expString could be a number(value), or a var(variable) or both(Expression)
        strExp = *iter;
        //translate string to expression
        try {
            Expression *ex = in.interpret(strExp);
            value = ex->calculate();
            st->addVar(nameVar, value);
        } catch (const exception &e) {
            exit(-1);
        }
        //calculate the expression
        iter++;
        return 3;
    } else { //var [nameVar] = sim -> " " or [nameVar] = sim <- " "
        direction = *iter;
        advance(iter, 2);
        sim = *iter;
        st->addVar(nameVar, sim, direction);
        iter++;
        return 5;
    }
}


