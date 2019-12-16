#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>

using namespace std;

list<string> splitString(string source, const string &delimiter) {
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

string subString(string source, string del_1, string del_2) {
    size_t first, last;
    first = source.find(del_1);
    last = source.find(del_2);
    return source.substr(first + 1, last - (first + 1));
}

string strip(string in) {
    in.erase(remove_if(in.begin(), in.end(), [](string::value_type ch) { return !isalpha(ch); }), in.end());
    return in;
}


list<string> lexer(string filePath) {
    ifstream in_file{filePath, ios::in};
    list<string> varNames, commandsList;

    if (!in_file) {
        cerr << "Error - file not found";
    }
    string line;
    while (getline(in_file, line)) {
        string command, command2;
        size_t first, last;
        if (line.find("openDataServer") != string::npos) {
            commandsList.push_back("openDataServer");
            first = line.find("(");
            last = line.find(")");
            command = line.substr(first + 1, last - (first + 1));
            commandsList.push_back(command);
        } else if (line.find("connectControlClient") != string::npos) {
            commandsList.push_back("connectControlClient");
            first = line.find("(");
            last = line.find(",");
            command = line.substr(first + 1, last - (first + 1));
            commandsList.push_back(command);
            first = line.find(",");
            last = line.find(")");
            command = line.substr(first + 1, last - (first + 1));
            commandsList.push_back(command);

        } else if (line.find("var ") != string::npos) {
            commandsList.push_back("var");
            command = line.erase(0, 3);
            command = strip(command);
            command2.append(command, 0, 1);

            if (command.find("<-") != string::npos) {
                command2 = subString(command, command2, "<-");
                commandsList.push_back(command2);
                commandsList.push_back("<-");
                commandsList.push_back("sim");
                commandsList.push_back(subString(command, "(", ")"));
            } else if (command.find("->") != string::npos) {
                command2 = subString(command, command2, "->");
                commandsList.push_back(command2);
                commandsList.push_back("->");
                commandsList.push_back("sim");
                commandsList.push_back(subString(command, "(", ")"));
            } else if (command.find('=') != string::npos) {
                first = command.find('=');
                command2 = subString(command, command2, "=");
                commandsList.push_back(command2);
                commandsList.push_back("=");
                commandsList.push_back(command2.substr(first + 1));
            } else {
                commandsList.push_back(command.substr(0));
            }
            list<string> tempVar = splitString(line, " ");
            commandsList.insert(commandsList.cend(), tempVar.cbegin(), tempVar.cend());
            if (commandsList.back().find("sim") != string::npos) {
                auto iter = commandsList.end();
                iter--;
                first = iter->find("(");
                last = iter->find(")");
                command2 = iter->substr(first + 1, last - (first + 1));
                iter->erase(first, last);
                commandsList.push_back(command2);
            }


        } else if (line.find("Print") != string::npos) {
            first = line.find("Print");


        } else if (line.find("Sleep") != string::npos) {
            first = line.find("Sleep");


        } else if (line.find("while") != string::npos) {
            first = line.find("while");


        } else if (line.find("if") != string::npos) {
            first = line.find("if");


        } else if (line.find("=") != string::npos) {

        } else {
            cerr << "Error" << endl;
        }
    }
    return commandsList;
}

int main(int argc, char *args[]) {
    list<string> commandList = lexer("../fly.txt");

}
