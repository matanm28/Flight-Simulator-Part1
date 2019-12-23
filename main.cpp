#include <stdio.h>
#include <list>
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char *args[]) {
    Lexer lex = Lexer("../fly.txt");
    vector<string> commandsList = lex.lexering();
    Parser init;
    init.Parse(commandsList);
}
