#include "Literal.h"

Literal::Literal(VType v) : value(v) {}

VType Literal::evaluate() const { return value; }
