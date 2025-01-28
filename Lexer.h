#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <iostream>
#include <stdexcept>
#include <string>

class Lexer {
private:
    const std::string text;
    size_t pos;
    char currChar;

    void move();
    void strip();
    Token getLiteral();

public:
    explicit Lexer(std::string input);
    Token getNextToken();
};

#endif // LEXER_H
