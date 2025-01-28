#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <iostream>
#include <variant>
#include <unordered_map>
#include <memory>
using namespace std;

typedef variant<int, bool> VType;

class Expression {
public:
    Expression() = default;
    virtual ~Expression() = default;
    virtual VType evaluate() const = 0;
};

#endif // EXPRESSIONS_H