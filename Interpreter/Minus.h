//
// Created by matan on 05/11/2019.
//

#ifndef EX1_MINUS_H
#define EX1_MINUS_H

#include "BinaryOperator.h"

class Minus : public BinaryOperator {
public:
    Minus(Expression *left, Expression *right);

private:
    double calculate() override;

};


#endif //EX1_MINUS_H
