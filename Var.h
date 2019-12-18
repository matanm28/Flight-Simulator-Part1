//
// Created by matan on 12/17/19.
//

#ifndef EX1_VAR_H
#define EX1_VAR_H
#define DEFAULT_VALUE 0

#include "baseInclude.h"

class Var {
private:
    float value;
    string sim, direction;
public:
    Var(float value, const string &sim, const string &direction);

    Var(const string &sim, const string &direction);

    Var(float value);

    Var(const Var &v); //copy constructor

    float getValue() const;

    const string &getSim() const;

    const string &getDirection() const;

    void setValue(float value);


};


#endif //EX1_VAR_H
