//
// Created by matan on 05/11/2019.
//

#ifndef EX1_UNARYOPERATOR_H
#define EX1_UNARYOPERATOR_H


#include "Expression.h"

class UnaryOperator : public Expression {
    Expression *exp;

public:
    UnaryOperator(Expression *exp);

    Expression *getExp();

    virtual ~UnaryOperator();

};


#endif //EX1_UNARYOPERATOR_H
