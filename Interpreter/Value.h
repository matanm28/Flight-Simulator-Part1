//
// Created by matan on 05/11/2019.
//

#ifndef EX1_VALUE_H
#define EX1_VALUE_H


#include "Expression.h"

class Value : public Expression {
    double value;
public:
    Value(double value);

    double calculate();

    virtual ~Value();
};


#endif //EX1_VALUE_H
