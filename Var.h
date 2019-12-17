//
// Created by matan on 12/17/19.
//

#ifndef EX1_VAR_H
#define EX1_VAR_H
#define DEFAULT_VALUE 0

#include "baseInclude.h"

class Var {
private:
    int value;
    string sim, direction;
public:
    Var(int value, const string &sim, const string &direction);

    Var(const string &sim, const string &direction);

    int getValue() const;

    const string &getSim() const;

    const string &getDirection() const;

};


#endif //EX1_VAR_H
