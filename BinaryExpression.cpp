#include "BinaryExpression.h"

OperandType BinaryExpression::mapStringToOperandType(const string& operador_str) {  
    static const unordered_map<string, OperandType> operator_map = {
        {"+", OperandType::Add},
        {"-", OperandType::Sub},
        {"*", OperandType::Mul},
        {"/", OperandType::Div},
        {"==", OperandType::Equal},
        {"!=", OperandType::NotEqual},
        {"<", OperandType::LessThan},
        {">", OperandType::GreaterThan},
        {"<=", OperandType::LessEqual},
        {">=", OperandType::GreaterEqual},
        {"&&", OperandType::LogicalAnd},
        {"||", OperandType::LogicalOr},
        {"(", OperandType::ParenthesisLeft},
        {")", OperandType::ParenthesisRight}
    };

    auto it = operator_map.find(operador_str);
    if (it != operator_map.end()) {
        return it->second;
    } else {
        throw runtime_error("BinaryExpression::mapStringToOperandType + Unknown operator: " + operador_str);
    }
}

BinaryExpression::BinaryExpression(unique_ptr<Expression> left, const string& operador_str, unique_ptr<Expression> right)  
    : left(move(left)), right(move(right)) {
    if (!this->left || !this->right) {
        throw runtime_error("BinaryExpression::[constructor operador_str] Cannot create a BinaryExpression with null operands");
    }

    operador = mapStringToOperandType(operador_str);
}

BinaryExpression::BinaryExpression(unique_ptr<Expression> left, OperandType operador, unique_ptr<Expression> right)  
    : left(move(left)), right(move(right)), operador(operador) {
    if (!this->left || !this->right) {
        throw runtime_error("BinaryExpression::[constructor OperandType] Cannot create a BinaryExpression with null operands");
    }
}

VType BinaryExpression::evaluate() const { 
    auto lValue = left->evaluate();
    auto rValue = right->evaluate();

    return visit([this](auto&& l, auto&& r) -> VType {
        using T1 = decay_t<decltype(l)>;
        using T2 = decay_t<decltype(r)>;

        if constexpr (is_same_v<T1, int> && is_same_v<T2, int>) {
            switch (operador) {
                case OperandType::Add: return l + r;
                case OperandType::Sub: return l - r;
                case OperandType::Mul: return l * r;
                case OperandType::Div:
                    if (r != 0) {
                        return l / r;
                    } else {
                        throw runtime_error("BinaryExpression::[evaluate] Division by zero");
                    }
                case OperandType::LessThan: return l < r;
                case OperandType::GreaterThan: return l > r;
                case OperandType::LessEqual: return l <= r;
                case OperandType::GreaterEqual: return l >= r;
                case OperandType::Equal: return l == r;
                case OperandType::NotEqual: return l != r;
                default: throw runtime_error("BinaryExpression::[evaluate] Unknown arithmetic operator");
            }
        } else if constexpr (is_same_v<T1, bool> && is_same_v<T2, bool>) {
            switch (operador) {
                case OperandType::LogicalAnd: return l && r;
                case OperandType::LogicalOr: return l || r;
                case OperandType::Equal: return l == r;
                case OperandType::NotEqual: return l != r;
                default: throw runtime_error("BinaryExpression::[evaluate]  Unknown logical operator");
            }
        }
        throw runtime_error("BinaryExpression::[evaluate] Incompatible operand types");
    }, lValue, rValue);
}
