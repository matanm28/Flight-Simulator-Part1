//
// Created by matan on 12/17/19.
//

#ifndef EX1_VAR_H
#define EX1_VAR_H
#define DEFAULT_VALUE 0

#include <string>
#include "Interpreter/Expression.h"

using namespace std;

class Var : public Expression {
private:
    float value;
    string sim, direction;
    bool newValue = false;
public:

    Var(float value, const string &sim, const string &direction);

    Var(const string &sim, const string &direction);

    Var(float value);

    Var(const Var &v); //copy constructor

    float getValue() const;

    const string &getSim() const;

    const string &getDirection() const;

    bool hasNewValue() const;

    void setValue(float value);

    double calculate() override;

    void valueUsed();


};


#endif //EX1_VAR_H
