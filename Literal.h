#ifndef LITERAL_H
#define LITERAL_H

#include "Expression.h"

class Literal : public Expression {
private:
    VType value;

public:
    explicit Literal(VType v);
    VType evaluate() const override;
};

#endif // LITERAL_H
