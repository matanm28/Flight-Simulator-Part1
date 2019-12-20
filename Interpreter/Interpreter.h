//
// Created by matan on 07/11/2019.
//

#ifndef EX1_INTERPRETER_H
#define EX1_INTERPRETER_H
#define L_BRACKET '('
#define R_BRACKET ')'
#define C_PLUS '+'
#define C_MINUS '-'
#define PLUS "+"
#define MINUS "-"
#define C_U_MINUS '~'
#define C_U_PLUS '$'
#define U_MINUS "~"
#define U_PLUS "$"
#define C_MULT '*'
#define C_DIV '/'
#define MULT "*"
#define DIV "/"

#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <stack>
#include <regex>
#include "Variable.h"
#include "Value.h"
#include "Plus.h"
#include "Div.h"
#include "Minus.h"
#include "Mul.h"
#include "UMinus.h"
#include "UPlus.h"
#include "../SymbolTable.h"


using namespace std;

class Interpreter {
private:
    list<Variable *> *expList = NULL;
public:
    Interpreter();

    Expression *interpret(const string exp);

    bool interpretCondition(string exp);

    void setVariables(string values);

    queue<std::string> *stringToRPN(const string expString);

    ~Interpreter();

private:
    void updateExpList(Variable *var);

    static bool charIsNumber(const char c);

    static bool charIsVar(const char c);

    static bool charIsOperator(const char c);

    static bool checkUnaryPlus(const string, int i);

    static bool isNumber(const string str);

    static bool isVar(const string str);

    static bool isOperator(const string str);

    Variable *findVar(string varString);

    Expression *stringToExpression(const string expString);

    int trans(string op);
};


#endif //EX1_INTERPRETER_H
