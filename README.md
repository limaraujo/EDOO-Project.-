# Estrutura do Projeto

Este repositório contém a implementação de um analisador sintático baseado em recursive descent parsing. A seguir, detalhamos a estrutura do projeto e suas principais componentes.

## Estrutura de Diretórios e Arquivos

```
├── BinaryExpression.cpp   -> Implementação das classes de expressões binárias
├── BinaryExpression.h     -> Declaração das classes de expressões binárias
├── comandos/              -> Instruções sobre como utilizar o código
├── Expression.h           -> Classe base para todas as expressões
├── out/                   -> Diretório de saída
├── in/                    -> Diretório de entrada
├── Lexer.cpp              -> Implementação do analisador léxico
├── Lexer.h                -> Declaração do analisador léxico
├── LICENSE                -> Licença do projeto
├── Literal.cpp            -> Implementação da classe para literais
├── Literal.h              -> Declaração da classe para literais
├── main.cpp               -> Ponto de entrada do programa
├── Parser.cpp             -> Implementação do analisador sintático recursive descent
├── Parser.h               -> Declaração do analisador sintático
├── PrimaryExpression.cpp  -> Implementação das expressões primárias (ex: parênteses e unárias)
├── PrimaryExpression.h    -> Declaração das expressões primárias
├── Token.h                -> Definição e extração de tokens
├── UnaryExpression.cpp    -> Implementação das expressões unárias
└── UnaryExpression.h      -> Declaração das expressões unárias
```

## Como Utilizar o Código

1. **Compilação e excursão do código:**

g++ -std=c++17 -Wall -Wextra -g3 -o main  *.cpp && ./main < in > out





