#include <stdio.h>
#include <list>
#include "Lexer.h"

int main(int argc, char *args[]) {
    Lexer lex = Lexer("../fly.txt");
    lex.lexering();

}
