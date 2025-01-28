#include "PrimaryExpression.h"

PrimaryExpression::PrimaryExpression(std::unique_ptr<Expression> e) : exp(std::move(e)) {
    if (!exp) {
        throw std::runtime_error("PrimaryExpression::[constructor] Cannot create a PrimaryExpression with null operand");
    }
}

VType PrimaryExpression::evaluate() const {
    return exp->evaluate();
}
