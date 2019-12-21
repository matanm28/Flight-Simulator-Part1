//
// Created by matan on 07/11/2019.
//
#include "Interpreter.h"

Interpreter::Interpreter() {
    this->expList = new list<Variable *>();
}

Expression *Interpreter::interpret(const string exp) {
    queue<string> *rpn = this->stringToRPN(exp);
    stack<Expression *> *expStack = new stack<Expression *>();
    string token;
    Expression *left, *right, *newExp;
    while ((!rpn->empty() || expStack->size() > 1)) {
        token = rpn->front();
        rpn->pop();
        if (isOperator(token)) {
            right = expStack->top();
            expStack->pop();
            switch (token[0]) {
                case C_PLUS:
                    left = expStack->top();
                    expStack->pop();
                    newExp = new Plus(left, right);
                    break;
                case C_MINUS:
                    left = expStack->top();
                    expStack->pop();
                    newExp = new Minus(left, right);
                    break;
                case C_DIV:
                    left = expStack->top();
                    expStack->pop();
                    newExp = new Div(left, right);
                    break;
                case C_MULT:
                    left = expStack->top();
                    expStack->pop();
                    newExp = new Mul(left, right);
                    break;
                case C_U_PLUS:
                    newExp = new UPlus(right);
                    break;
                case C_U_MINUS:
                    newExp = new UMinus(right);
                    break;
                default:
                    newExp = nullptr;
                    break;
            }
        } else {
            newExp = this->stringToExpression(token);
        }
        if (newExp != nullptr) {
            expStack->push(newExp);
        } else {
            throw "illegal math expression";
        }
        newExp = nullptr;
        left = nullptr;
        right = nullptr;
    }
    return expStack->top();
}

Expression *Interpreter::stringToExpression(const string expString) {
    double value;
    try {
        value = stod(expString);
        return new Value(value);
    } catch (exception z) {
        SymbolTable *st = SymbolTable::getSymbolTable();
        Var v = st->getVar(expString);
        return new Variable(expString, v.getValue());
    }
}

void Interpreter::setVariables(string values) {
    double value = 0;
    string token, delimiter;
    delimiter = ";";
    int pos, equalSign;
    regex pattern("[a-zA-Z][a-zA-Z0-9]*_?[a-zA-Z0-9]*=-?[0-9]+\\.?[0-9]*");
    while (values.length() > 0) {
        pos = values.find(delimiter);
        if (pos == string::npos) {
            pos = values.length();
        }
        token = values.substr(0, pos);
        if (regex_match(token, pattern)) {
            equalSign = token.find("=");
            try {
                value = stod(token.substr(equalSign + 1, token.length()));
                Variable *var = new Variable(token.substr(0, equalSign), value);
                updateExpList(var);
            } catch (exception z) {
                cout << z.what() << endl;
            }
        } else {
            throw "illegal variable assignment!";
        }
        values.erase(0, pos + delimiter.length());
    }
}

queue<string> *Interpreter::stringToRPN(const string expString) {
    queue<string> *reverseNotation = new queue<string>;
    stack<string> *operatorStack = new stack<string>;
    string temp;
    for (int i = 0; i < expString.length(); i++) {
        if (charIsNumber(expString[i]) || charIsVar(expString[i])) {
            temp.push_back(expString[i]);
            if (i == expString.length() - 1) {
                string *exp = new string(temp);
                temp.erase();
                reverseNotation->push(*exp);
            }
        } else {
            if (temp.length() > 0) {
                string *exp = new string(temp);
                temp.erase();
                reverseNotation->push(*exp);
            }
            switch (expString[i]) {
                case '+':
                case '-':
                    if (i == 0 || charIsOperator(expString[i - 1])) {
                        if (expString[i] == C_MINUS) {
                            operatorStack->push(U_MINUS);
                        } else {
                            operatorStack->push(U_PLUS);
                        }
                    } else {
                        if (!operatorStack->empty() && (operatorStack->top() == MULT || operatorStack->top() == DIV
                                                        || operatorStack->top() == U_PLUS ||
                                                        operatorStack->top() == U_MINUS)) {
                            while (!operatorStack->empty() &&
                                   (operatorStack->top() == MULT || operatorStack->top() == DIV
                                    || operatorStack->top() == U_PLUS || operatorStack->top() == U_MINUS)) {
                                reverseNotation->push(operatorStack->top());
                                operatorStack->pop();
                            }
                            operatorStack->push(expString.substr(i, 1));

                        } else {
                            operatorStack->push(expString.substr(i, 1));
                        }
                    }
                    break;
                case '*':
                case '/':
                    if (!operatorStack->empty() && (operatorStack->top() == PLUS || operatorStack->top() == MINUS)) {
                        operatorStack->push(expString.substr(i, 1));
                    } else if (!operatorStack->empty() && (operatorStack->top() == MULT || operatorStack->top() == DIV
                                                           || operatorStack->top() == U_MINUS ||
                                                           operatorStack->top() == U_PLUS)) {
                        while (!operatorStack->empty() && (operatorStack->top() == MULT || operatorStack->top() == DIV
                                                           || operatorStack->top() == U_MINUS ||
                                                           operatorStack->top() == U_PLUS)) {
                            reverseNotation->push(operatorStack->top());
                            operatorStack->pop();
                        }
                        operatorStack->push(expString.substr(i, 1));
                    } else {
                        operatorStack->push(expString.substr(i, 1));
                    }
                    break;
                case '(':
                    operatorStack->push(expString.substr(i, 1));
                    break;
                case ')':
                    while (!(operatorStack->top() == "(")) {
                        reverseNotation->push(operatorStack->top());
                        operatorStack->pop();
                    }
                    operatorStack->pop();
                    break;
                default:
                    break;
            }
        }
    }
    while (!operatorStack->empty()) {
        reverseNotation->push(operatorStack->top());
        operatorStack->pop();
    }
    return reverseNotation;
}


Variable *Interpreter::findVar(string varString) {

    for (Variable *var : *this->expList) {
        if (var->getName() == varString) {
            return new Variable(*var);
        }
    }
    return nullptr;
}

bool Interpreter::charIsNumber(const char c) {
    return ((c >= '0' && c <= '9') || c == '.');
}

bool Interpreter::charIsVar(const char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'z'));
}

bool Interpreter::charIsOperator(const char c) {
    return !(charIsNumber(c) || charIsVar(c) || c == R_BRACKET || c == ' ');
}

bool Interpreter::isNumber(const string str) {
    for (char c: str) {
        if (!charIsNumber(c)) {
            return false;
        }
    }
    return true;
}

bool Interpreter::isVar(const string str) {
    for (char c : str) {
        if (!charIsVar(c)) {
            return false;
        }
    }
    return true;
}

bool Interpreter::isOperator(const string str) {
    for (char c : str) {
        if (!charIsOperator(c)) {
            return false;
        }
    }
    return true;
}

void Interpreter::updateExpList(Variable *var) {
    for (Variable *varInList: *this->expList) {
        if (varInList->getName() == var->getName()) {
            this->expList->remove(varInList);
            break;
        }
    }
    this->expList->push_back(var);
}

Interpreter::~Interpreter() {
    delete this->expList;
}

bool Interpreter::interpretCondition(string exp) {
    string ex1, ex2, op;
    int j, t, i = 0;
    for (i = 0; i < exp.size(); i++) {
        if (!(exp.at(i) == '=' || exp.at(i) == '<' || exp.at(i) == '>' || exp.at(i) == '!' || exp.at(i) == ' ')) {
            ex1 += exp.at(i);
        } else {
            break;
        }
    }
    for (j = i; j < exp.size(); j++) {
        if (exp.at(j) == '=' || exp.at(j) == '<' || exp.at(j) == '>' || exp.at(j) == '!') {
            op += exp.at(j);
        } else {
            break;
        }
    }
    for (t = j; t < exp.size(); t++) {
        if (!(exp.at(t) == '=' || exp.at(t) == '<' || exp.at(t) == '>' || exp.at(t) == '!' || exp.at(t) == ' ')) {
            ex2 += exp.at(t);
        } else {
            break;
        }
    }
    switch (trans(op)) {
        case 1:
            return (this->interpret(ex1)->calculate() <= this->interpret(ex2)->calculate());
        case 2:
            return (this->interpret(ex1)->calculate() == this->interpret(ex2)->calculate());
        case 3:
            return (this->interpret(ex1)->calculate() >= this->interpret(ex2)->calculate());
        case 4:
            return (this->interpret(ex1)->calculate() < this->interpret(ex2)->calculate());
        case 5:
            return (this->interpret(ex1)->calculate() > this->interpret(ex2)->calculate());
        case 6:
            return (this->interpret(ex1)->calculate() != this->interpret(ex2)->calculate());
        default:
            cout << "error interpret condition didn't work" << endl;
            return false;
    }
}

int Interpreter::trans(string op) {
    if (op == "<=") {
        return 1;
    } else if (op == "==") {
        return 2;
    } else if (op == ">=") {
        return 3;
    } else if (op == "<") {
        return 4;
    } else if (op == ">") {
        return 5;
    } else if (op == "!=") {
        return 6;
    } else {
        return -1;
    }
}

