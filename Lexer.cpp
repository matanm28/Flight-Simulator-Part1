//
// Created by sapir on 16/12/2019.
//

#include "Lexer.h"
#include <stdio.h>
#include <iostream>

using namespace std;

Lexer::Lexer(const string &path) : path(path) {
    this->path = path;
}

string Lexer::subString(string source, string del_1, string del_2) {
    size_t first, last;
    first = source.find(del_1);
    last = source.find(del_2, first + 1);
    if (del_2 == "") {
        last = source.length() + 1;
    }
    if (del_1 == "") {
        source = this->trimChar(source.substr(0, last), ' ');
        return source;
    }
    return source.substr(first + 1, last - (first + 1));
}

vector<string> Lexer::lexering() {
    ifstream in_file{this->path, ios::in};
    if (!in_file) {
        cerr << "Error - file not found";
    }
    string line;
    while (getline(in_file, line)) {
        this->lexLine(in_file, line);
    }
    return commandsList;
}

string Lexer::getString(char x) {
    string s(1, x);
    return s;
}

void Lexer::lexLine(ifstream &in_file, string line) {
    string command, command2;
    size_t first, last;
    if (line.find("openDataServer") != string::npos) {
        commandsList.push_back("openDataServer");
        commandsList.push_back(subString(line, "(", ")"));
    } else if (line.find("connectControlClient") != string::npos) {
        commandsList.push_back("connectControlClient");
        commandsList.push_back(subString(line, "\"", "\""));
        commandsList.push_back(subString(line, ",", ")"));
    } else if (line.find("var ") != string::npos) {
        if (line.find("<-") != string::npos) {
            commandsList.push_back("var");
            line = line.erase(0, 4); //no "var "
            line = this->trimChar(line, ' '); //no spaces
            commandsList.push_back(subString(line, "", "<-"));
            commandsList.push_back("<-");
            commandsList.push_back("sim");
            commandsList.push_back(subString(subString(line, "(", ","), "\"", "\""));
        } else if (line.find("->") != string::npos) {
            commandsList.push_back("var");
            line = line.erase(0, 4); //no "var "
            line = this->trimChar(line, ' '); //no spaces
            commandsList.push_back(subString(line, "", "->"));
            commandsList.push_back("->");
            commandsList.push_back("sim");
            commandsList.push_back(subString(subString(line, "(", ","), "\"", "\""));
        } else if (line.find('=') != string::npos) {
            commandsList.push_back("var");
            line = line.erase(0, 4); //no "var "
            line = this->trimChar(line, ' '); //no spaces
            commandsList.push_back(subString(line, "", "="));
            commandsList.push_back("=");
            line.erase(0, line.find("="));
            commandsList.push_back(subString(line, "=", ""));
        } else if (line.find("(") != string::npos && line.find('(') < line.find("var")) { //parameter of function
            commandsList.push_back("func1");
            this->func(in_file, line);
//            string in = subString(line, "(", ")");
//            this->lexLine(in_file, in);
//            in = this->eraseParameters(line);
//            this->lexLine(in_file, in);
        } else {
            commandsList.push_back("var");
            line = line.erase(0, 4); //no "var "
            commandsList.push_back(subString(line, "", ""));
        }
    } else if (line.find("Print") != string::npos) {
        commandsList.push_back("Print");
        commandsList.push_back(subString(line, "(", ")"));
    } else if (line.find("Sleep") != string::npos) {
        commandsList.push_back("Sleep");
        commandsList.push_back(subString(line, "(", ")"));
    } else if (line.find("while") != string::npos) {
        commandsList.push_back("while");
        line = line.erase(0, 6);
        line = subString(line, "", "{");
        line = this->trimChar(line, ' ');
        commandsList.push_back(line);
        //getline(in_file, line);
        this->loop(in_file, line);
    } else if (line.find("if") != string::npos) {
        commandsList.push_back("if");
        line = line.erase(0, 3);
        line = subString(line, "", "{");
        line = this->trimChar(line, ' ');
        commandsList.push_back(line);
        //getline(in_file, line);
        this->loop(in_file, line);
    } else if (line.find("=") != string::npos) { //[nameVar] = expression
        line = this->trimChar(line, ' ');
        commandsList.push_back(subString(line, "", "="));
        commandsList.push_back("=");
        line.erase(0, line.find("="));
        commandsList.push_back(subString(line, "=", ""));
    } else if (line.find("(") != string::npos) {
        if (this->funcOrNot(line)) {
            commandsList.push_back("func1");
            this->func(in_file, line);
        } else {
            commandsList.push_back("func2");
            commandsList.push_back(subString(line, "", "("));
            commandsList.push_back(subString(line, "(", ")"));
        }
    } else {
        cerr << "Error" << endl;
    }
}

string Lexer::eraseParameters(string source) {
    int start, end;
    for (int i = 0; i < source.size(); i++) {
        if (source[i] == '(') {
            start = i;
        }
        if (source[i] == ')') {
            end = i;
            break;
        }
    }
    source.erase(start + 1, end - start - 1);
    return source;
}

bool Lexer::funcOrNot(string source) {
    for (int i = source.size() - 1; i >= 0; i--) {
        if (source[i] == '{') {
            return true;
        }
    }
    return false;
}

void Lexer::loop(ifstream &in_file, string line) {
    string in;
    commandsList.push_back("{");
    getline(in_file, line);
    while (line != "}" && this->trimChar(line, ' ') != "}") {
        if (line.find("if") != string::npos) {
            in = "i" + subString(line, "i", "");
            this->lexLine(in_file, in);
        } else if (line.find("while") != string::npos) {
            in = "w" + subString(line, "w", "");
            this->lexLine(in_file, in);
//            commandsList.push_back("while");
//            line = line.erase(0, 6);
//            this->loop(in_file, line);
        } else {
            in = subString(line, "", "");
            in = this->trimChar(in, '\t');
            in = this->trimChar(in, ' ');
            this->lexLine(in_file, in);
            //commandsList.push_back(in);
        }
        getline(in_file, line);
    }
    commandsList.push_back("}");
}

void Lexer::func(ifstream &in_file, string line) {
    commandsList.push_back(subString(line, "", "("));
    this->lexLine(in_file, subString(line, "(", ")"));
    commandsList.push_back("{");
    getline(in_file, line);
    while (line != "}" && this->trimChar(line, ' ') != "}") {
        if (line.find("if") != string::npos) {
            line = "i" + subString(line, "i", "");
            this->lexLine(in_file, line);
        } else if (line.find("while") != string::npos) {
            line = "w" + subString(line, "w", "");
            this->lexLine(in_file, line);
        } else {
            line = subString(line, "", "");
            line = this->trimChar(line, '\t');
            line = this->trimChar(line, ' ');
            this->lexLine(in_file, line);
            //commandsList.push_back(in);
        }
        getline(in_file, line);
    }
    commandsList.push_back("}");
}

string Lexer::trimChar(string source, const char c) {
    string output;
    for (int i = 0; i < source.size(); i++) {
        if (source[i] != c) {
            output += source[i];
        }
    }
    return output;
}