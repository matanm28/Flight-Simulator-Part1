#include <stdio.h>
#include <list>
#include "Lexer.h"
#include "InitializeCommands.h"

int main(int argc, char *args[]) {
    Lexer lex = Lexer("../fly.txt");
    list<string> commandsList = lex.lexering();
    InitializeCommands init;
    init.CreateMap();
    init.Parser(commandsList);
}
