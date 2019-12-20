//
// Created by matan on 05/11/2019.
//

#ifndef EX1_BINARYOPERATOR_H
#define EX1_BINARYOPERATOR_H


#include "Expression.h"

class BinaryOperator : public Expression {
    Expression *right;
    Expression *left;

public:
    BinaryOperator(Expression *left, Expression *right);


    Expression *getRight();

    Expression *getLeft();

    virtual ~BinaryOperator();

};


#endif //EX1_BINARYOPERATOR_H
