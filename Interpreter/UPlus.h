//
// Created by matan on 05/11/2019.
//

#ifndef EX1_UPLUS_H
#define EX1_UPLUS_H


#include "UnaryOperator.h"

class UPlus : public UnaryOperator {
public:
    UPlus(Expression *exp);

    double calculate() override;
};


#endif //EX1_UPLUS_H
