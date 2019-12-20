//
// Created by matan on 05/11/2019.
//

#ifndef EX1_PLUS_H
#define EX1_PLUS_H

#include "BinaryOperator.h"

class Plus : public BinaryOperator {
public:
    Plus(Expression *left, Expression *right);

    double calculate() override;

};


#endif //EX1_PLUS_H
