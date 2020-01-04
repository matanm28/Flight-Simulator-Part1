//
// Created by sapir on 16/12/2019.
//

#ifndef EX1_LEXER_H
#define EX1_LEXER_H

#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

class Lexer {
    string path;
    vector<string> commandsList;
public:
    Lexer(const string &path);

    string subString(string source, string del_1, string del_2);

    vector<string> lexering();

    string getString(char x);

    void loop(ifstream &in_file, string line);

    void lexLine(ifstream &in_file, string line);

    void func(ifstream &in_file, string line);

    string lStrip(string source);

private:
    string trimChar(string source, const char c);
};


#endif //EX1_LEXER_H
