#ifndef UNARYEXPRESSION_H
#define UNARYEXPRESSION_H

#include "Expression.h"
#include <memory>
#include <string>
#include <stdexcept>

class UnaryExpression : public Expression {
private:
    std::unique_ptr<Expression> expression;
    std::string operador;

public:
    explicit UnaryExpression(std::string operador, std::unique_ptr<Expression> expr);
    VType evaluate() const override;
};

#endif // UNARYEXPRESSION_H
