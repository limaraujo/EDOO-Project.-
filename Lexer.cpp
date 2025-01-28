#include "Lexer.h"

using namespace std;

Lexer::Lexer(string input) : text(input), pos(0) {
    currChar = (text.empty()) ? '\0' : text[0];
    if (text.empty()) {
        throw runtime_error("Lexer::[constructor] Empty input");
    }
}

void Lexer::move() {
    if (pos < text.length()) {
        pos++;
        currChar = (pos < text.length()) ? text[pos] : '\0';
    }
}

void Lexer::strip() {
    while (currChar != '\0' && isspace(currChar)) {
        move();
    }
}

Token Lexer::getLiteral() {
    string result;
    while (currChar != '\0' && (isdigit(currChar) || isalpha(currChar))) {
        result += currChar;
        move();
    }

    if (isdigit(result[0])) {
        return Token("INT", stoi(result));
    } else if (result == "true" || result == "false") {
        return Token("BOOL", result == "true");
    }

    throw runtime_error("Lexer::[getLiteral] Invalid literal");
}

Token Lexer::getNextToken() {
    while (currChar != '\0') {
        strip();

        if (isdigit(currChar) || isalpha(currChar)) {
            return getLiteral();
        }

        if (currChar == '-') {
            move();
            if (isspace(currChar)) {
                return Token("Sub", "-");
            }
            string result = "-";
            while (currChar != '\0' && isdigit(currChar)) {
                result += currChar;
                move();
            }
            return Token("INT", stoi(result));
        }

        string subString = "";
        while (!isspace(currChar) && currChar !='\0') {
            subString += currChar;
            move();
        }

        if (subString == "+") return Token("Add", "+");
        if (subString == "*") return Token("Mul", "*");
        if (subString == "/") return Token("Div", "/");
        if (subString == "==") return Token("Equal", "==");
        if (subString == "!=") return Token("NotEqual", "!=");
        if (subString == "<") return Token("LessThan", "<");
        if (subString == ">") return Token("GreaterThan", ">");
        if (subString == "<=") return Token("LessEqual", "<=");
        if (subString == ">=") return Token("GreaterEqual", ">=");
        if (subString == "&&") return Token("LogicalAnd", "&&");
        if (subString == "||") return Token("LogicalOr", "||");
        if (subString == "(") return Token("ParenthesisLeft", "(");
        if (subString == ")") return Token("ParenthesisRight", ")");

        throw runtime_error("Lexer::[getNextToken] Unknown token");
    }
    return Token("EOF", "");
}
