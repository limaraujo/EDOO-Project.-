#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Expression.h"
#include "UnaryExpression.h"
#include "PrimaryExpression.h"
#include "BinaryExpression.h"
#include "Literal.h"
#include "Token.h"

#include <stdexcept>
#include <memory>
#include <variant>
#include <string>

class Parser {
private:
    Lexer lexer;
    Token currToken;

    void match(const std::string& expType);

public:
    explicit Parser(const Lexer& l);
    ~Parser() = default;

    std::variant<int, bool> evaluate();
    std::unique_ptr<Expression> parse_exp();
    std::unique_ptr<Expression> parse_or_exp();
    std::unique_ptr<Expression> parse_and_exp();
    std::unique_ptr<Expression> parse_eq_exp();
    std::unique_ptr<Expression> parse_rel_exp();
    std::unique_ptr<Expression> parse_add_exp();
    std::unique_ptr<Expression> parse_mul_exp();
    std::unique_ptr<Expression> parse_unary_exp();
    std::unique_ptr<Expression> parse_primary_exp();
};

#endif
