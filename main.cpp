#include <stdio.h>
#include <list>
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char *args[]) {
    if (argc < 2) {
        cerr << "missing file name" << endl;
    } else {
        Lexer lex = Lexer(args[1]);
        vector<string> commandsList = lex.lexering();
        Parser init;
        init.Parse(commandsList);
    }
}
