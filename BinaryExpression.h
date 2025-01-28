#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include "Expression.h"
#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>

using namespace std;

enum class OperandType {
    Add, Sub, Mul, Div,
    Equal, NotEqual,
    LessThan, GreaterThan, LessEqual, GreaterEqual,
    LogicalAnd, LogicalOr,
    ParenthesisLeft, ParenthesisRight
};

class BinaryExpression : public Expression {
private:
    OperandType operador;
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;

    OperandType mapStringToOperandType(const string& operador_str);

public:
    explicit BinaryExpression(unique_ptr<Expression> left, const string& operador_str, unique_ptr<Expression> right);

    explicit BinaryExpression(unique_ptr<Expression> left, OperandType operador, unique_ptr<Expression> right);

    VType evaluate() const override;
};

#endif // BINARYEXPRESSION_H
