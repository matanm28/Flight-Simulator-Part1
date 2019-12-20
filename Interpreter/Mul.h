//
// Created by matan on 05/11/2019.
//

#ifndef EX1_MUL_H
#define EX1_MUL_H


#include "BinaryOperator.h"

class Mul : public BinaryOperator {
public:
    Mul(Expression *left, Expression *right);

private:
    double calculate() override;

};


#endif //EX1_MUL_H
