//
// Created by sapir on 16/12/2019.
//

#include "Lexer.h"
#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

Lexer::Lexer(const string &path) : path(path) {
    this->path = path;
}

list<string> Lexer::splitString(string source, const string &delimiter) {
    list<string> tokensList;
    size_t pos = 0;
    string token;
    while ((pos = source.find(delimiter)) != std::string::npos) {
        token = source.substr(0, pos);
        tokensList.push_back(token);
        source.erase(0, pos + delimiter.length());
    }
    tokensList.push_back(source);
    return tokensList;
}

string Lexer::subString(string source, string del_1, string del_2) {
    size_t first, last;
    first = source.find(del_1);
    last = source.find(del_2);
    if (del_2 == "") {
        last = source.length() + 1;
    }
    if (del_1 == "") {
        return source.substr(0, last);
    }
    return source.substr(first + 1, last - (first + 1));
}

list<string> Lexer::lexering() {
    ifstream in_file{this->path, ios::in};
    if (!in_file) {
        cerr << "Error - file not found";
    }
    string line;
    while (getline(in_file, line)) {
        this->lexLine(in_file, line);
    }
    for (auto iter = commandsList.cbegin(); iter != commandsList.cend(); iter++) {
        cout << "-" + *iter + "-" << endl;
    }
    in_file.close();
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
        commandsList.push_back(subString(line, "(", ","));
        commandsList.push_back(subString(line, ",", ")"));
    } else if (line.find("var ") != string::npos) {
        commandsList.push_back("var");
        line = line.erase(0, 4);
        if (line.find("<-") != string::npos) {
            if (line.find("<-") > line.find(" ")) {
                commandsList.push_back(subString(line, "", " "));
            } else {
                commandsList.push_back(subString(line, "", "<-"));
            }
            commandsList.push_back("<-");
            commandsList.push_back("sim");
            commandsList.push_back(subString(line, "(", ")"));
        } else if (line.find("->") != string::npos) {
            if (line.find("->") > line.find(" ")) {
                commandsList.push_back(subString(line, "", " "));
            } else {
                commandsList.push_back(subString(line, "", "->"));
            }
            commandsList.push_back("->");
            commandsList.push_back("sim");
            commandsList.push_back(subString(line, "(", ")"));
        } else if (line.find('=') != string::npos) {
            if (line.find("=") > line.find(" ")) {
                commandsList.push_back(subString(line, "", " "));
            } else {
                commandsList.push_back(subString(line, "", "="));
            }
            commandsList.push_back("=");
            line.erase(0, line.find("="));
            if (line.find(" ") != string::npos) {
                commandsList.push_back(subString(line, " ", ""));
            } else {
                commandsList.push_back(subString(line, "=", ""));
            }
        } else {
            commandsList.push_back(subString(line, " ", ""));
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
        loop(in_file, line);
    } else if (line.find("if") != string::npos) {
        commandsList.push_back("if");
        line = line.erase(0, 3);
        loop(in_file, line);
    } else if (line.find("=") != string::npos) {
        if (line.find("=") > line.find(" ")) {
            commandsList.push_back(subString(line, "", " "));
        } else {
            commandsList.push_back(subString(line, "", "="));
        }
        commandsList.push_back("=");
        line.erase(0, line.find("="));
        if (line.find(" ") != string::npos) {
            commandsList.push_back(subString(line, " ", ""));
        } else {
            commandsList.push_back(subString(line, "=", ""));
        }
    } else {
        cerr << "Error" << endl;
    }
}

void Lexer::loop(ifstream &in_file, string line) {
    string in = subString(line, "", "{");
    in = this->trimChar(in, ' ');
    commandsList.push_back(in);
    commandsList.push_back("{");
    getline(in_file, line);
    while (line != "}") {
        if (line.find("if") != string::npos) {
            commandsList.push_back("if");
            line = line.erase(0, 3);
            this->loop(in_file, line);
        }
        if (line.find("while") != string::npos) {
            commandsList.push_back("while");
            line = line.erase(0, 6);
            this->loop(in_file, line);
        }

        in = subString(line, "", "");
        in = this->trimChar(in, '\t');
        this->lexLine(in_file, in);
        //commandsList.push_back(in);
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