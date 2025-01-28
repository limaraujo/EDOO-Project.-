#ifndef PRIMARYEXPRESSION_H
#define PRIMARYEXPRESSION_H

#include "Expression.h"
#include <memory>
#include <stdexcept>

class PrimaryExpression : public Expression {
private:
    std::unique_ptr<Expression> exp;

public:
    explicit PrimaryExpression(std::unique_ptr<Expression> e);
    VType evaluate() const override;
};

#endif // PRIMARYEXPRESSION_H
