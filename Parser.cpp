#include "Parser.h"

Parser::Parser(const Lexer& l) : lexer(l), currToken(lexer.getNextToken()) {}

void Parser::match(const std::string& expType) {
    if (currToken.getType() == expType) {
        currToken = lexer.getNextToken(); 
    } else {
        throw std::runtime_error(
            "Parser::[match]expected '" + expType + "', but found '" + currToken.getType());
    }
}

std::variant<int, bool> Parser::evaluate() {
    auto expr = parse_exp();
    return expr->evaluate();
}

std::unique_ptr<Expression> Parser::parse_exp() {
    return parse_or_exp();
}

std::unique_ptr<Expression> Parser::parse_or_exp() {
    auto e1 = parse_and_exp();

    if (currToken.getType() == "LogicalOr") {
        match("LogicalOr");
        auto e2 = parse_and_exp();
        return std::make_unique<BinaryExpression>(std::move(e1), OperandType::LogicalOr, std::move(e2));
    }
    return e1;
}

std::unique_ptr<Expression> Parser::parse_and_exp() {
    auto e1 = parse_eq_exp();

    if (currToken.getType() == "LogicalAnd") {
        match("LogicalAnd");
        auto e2 = parse_eq_exp();
        return std::make_unique<BinaryExpression>(std::move(e1), OperandType::LogicalAnd, std::move(e2));
    }
    return e1;
}

std::unique_ptr<Expression> Parser::parse_eq_exp() {
    auto e1 = parse_rel_exp();

    if (currToken.getType() == "Equal" || currToken.getType() == "NotEqual") {
        std::string operador = (currToken.getType() == "Equal") ? "==" : "!=";
        match(currToken.getType());
        auto e2 = parse_rel_exp();
        return std::make_unique<BinaryExpression>(std::move(e1), operador, std::move(e2));
    }
    return e1;
}

std::unique_ptr<Expression> Parser::parse_rel_exp() {
    auto e1 = parse_add_exp();

    if (currToken.getType() == "LessThan" || currToken.getType() == "GreaterThan" || 
        currToken.getType() == "LessEqual" || currToken.getType() == "GreaterEqual") {

        std::string operador = (currToken.getType() == "LessThan") ? "<" :
                              (currToken.getType() == "GreaterThan") ? ">" :
                              (currToken.getType() == "LessEqual") ? "<=" : ">=";
        match(currToken.getType());
        auto e2 = parse_add_exp();
        return std::make_unique<BinaryExpression>(std::move(e1), operador, std::move(e2));
    }
    return e1;
}

std::unique_ptr<Expression> Parser::parse_add_exp() {
    auto e1 = parse_mul_exp();

    if (currToken.getType() == "Add" || currToken.getType() == "Sub") {
        std::string operador = (currToken.getType() == "Add") ? "+" : "-";
        match(currToken.getType());
        auto e2 = parse_mul_exp();
        return std::make_unique<BinaryExpression>(std::move(e1), operador, std::move(e2));
    }
    return e1;
}

std::unique_ptr<Expression> Parser::parse_mul_exp() {
    auto e1 = parse_unary_exp();

    if (currToken.getType() == "Mul" || currToken.getType() == "Div") {
        std::string operador = (currToken.getType() == "Mul") ? "*" : "/";
        match(currToken.getType());
        auto e2 = parse_unary_exp();
        return std::make_unique<BinaryExpression>(std::move(e1), operador, std::move(e2));
    }
    return e1;
}

std::unique_ptr<Expression> Parser::parse_unary_exp() {
    if (currToken.getType() == "Sub") {
        match("Sub");
        auto e1 = parse_primary_exp();
        return std::make_unique<UnaryExpression>("-", std::move(e1));
    }
    return parse_primary_exp();
}

std::unique_ptr<Expression> Parser::parse_primary_exp() {
    Token token = currToken;

    if (token.getType() == "INT" || token.getType() == "BOOL") {
        match(token.getType());

        auto value = token.getValue();

        return std::visit([](const auto& arg) -> std::unique_ptr<Expression> {
            if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, int> || 
                        std::is_same_v<std::decay_t<decltype(arg)>, bool>) {
                return std::make_unique<PrimaryExpression>(std::make_unique<Literal>(arg));
            }
            throw std::runtime_error("Parser::[parse_primary_exp] Unsupported literal type.");
        }, value);

    }
    if (token.getType() == "ParenthesisLeft") {
        match("ParenthesisLeft");
        auto e1 = parse_exp();
        match("ParenthesisRight");
        return std::make_unique<PrimaryExpression>(std::move(e1));
    }
    throw std::runtime_error("Parser::[parse_primary_exp] Invalid literal or unclosed parentheses -> " + token.to_string());
}

