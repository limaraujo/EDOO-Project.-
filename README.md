# Project Structure

This repository contains the implementation of an analytical parser for processing arithmetic expressions, with support for integer and boolean literals. The project uses a Context-Free Grammar (CFG) to define and interpret the format of the expressions, enabling analysis and validation according to the specification.

## Directory and File Structure

```
├── BinaryExpression.cpp   -> Implementation of binary expression classes
├── BinaryExpression.h     -> Declaration of binary expression classes
├── commands/              -> Instructions on how to use the code
├── Expression.h           -> Base class for all expressions
├── out/                   -> Output directory
├── in/                    -> Input directory
├── Lexer.cpp              -> Implementation of the lexical analyzer
├── Lexer.h                -> Declaration of the lexical analyzer
├── LICENSE                -> Project license
├── Literal.cpp            -> Implementation of the literal class
├── Literal.h              -> Declaration of the literal class
├── main.cpp               -> Program entry point
├── Parser.cpp             -> Implementation of the recursive descent parser
├── Parser.h               -> Declaration of the recursive descent parser
├── PrimaryExpression.cpp  -> Implementation of primary expressions (e.g., parentheses and unary)
├── PrimaryExpression.h    -> Declaration of primary expressions
├── Token.h                -> Token definition and extraction
├── UnaryExpression.cpp    -> Implementation of unary expressions
└── UnaryExpression.h      -> Declaration of unary expressions
```

## How to Use the Code

1. **Compile and run the code:**

```bash
g++ -std=c++17 -Wall -Wextra -g3 -o main *.cpp && ./main < in > out
```

