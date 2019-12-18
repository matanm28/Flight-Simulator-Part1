#include <stdio.h>
#include <list>
#include "Lexer.h"
#include "InitializeCommands.h"

int main(int argc, char *args[]) {
    Lexer lex = Lexer("../fly.txt");
    vector<string> commandsList = lex.lexering();
    InitializeCommands init;
    init.Parser(commandsList);
}
