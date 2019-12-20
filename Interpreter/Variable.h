//
// Created by matan on 04/11/2019.
//

#ifndef EX1_VARIABLE_H
#define EX1_VARIABLE_H

#include <iostream>
#include <string>
#include "Expression.h"
#include "../Var.h"

using namespace std;

class Variable : public Expression {
    string name;
    double value;

public:
    Variable(const string &name, double value);

    Variable(Variable &var);

    double calculate() override;

    double getValue() const;

    const string &getName() const;

    //prefix
    Variable &operator++();

    Variable &operator--();

    //postfix
    Variable &operator++(int);

    Variable &operator--(int);

    Variable &operator+=(double val);

    Variable &operator-=(double val);

    bool operator==(const Variable &other) const;

    bool operator!=(const Variable &other) const;

    bool operator<(const Variable &other) const;

    bool operator>(const Variable &other) const;

    bool operator<=(const Variable &other) const;

    bool operator>=(const Variable &other) const;

    Variable &operator+(Expression &other);

    Variable &operator-(Expression &other);

    virtual ~Variable();
};


#endif //EX1_VARIABLE_H
