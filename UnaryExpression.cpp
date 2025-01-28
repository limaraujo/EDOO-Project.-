#include "UnaryExpression.h"
#include <utility>
#include <stdexcept>

UnaryExpression::UnaryExpression(std::string operador, std::unique_ptr<Expression> expr)
    : operador(std::move(operador)), expression(std::move(expr)) {
    if (!expression) {
        throw std::runtime_error("Cannot create a UnaryExpression from a null expression");
    }
}

VType UnaryExpression::evaluate() const {
    auto value = expression->evaluate();

    return std::visit([this](auto&& arg) -> VType {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, int>) {
            if (operador == "-") return -arg;
            throw std::runtime_error("Invalid unary operator for integers: " + operador);
        }
        throw std::runtime_error("Unsupported unary operator");
    }, value);
}
