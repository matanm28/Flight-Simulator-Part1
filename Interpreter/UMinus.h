//
// Created by matan on 05/11/2019.
//

#ifndef EX1_UMINUS_H
#define EX1_UMINUS_H

#include "UnaryOperator.h"

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *exp);

    double calculate() override;

};


#endif //EX1_UMINUS_H
