#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

/*
    [Grammer]
        Calculation:
            Statement
            Print
            Quit
            Calculation Statement
        Statement:
            Declaration
            Expression
        Declaration:
            "let" Name '=' Expression
            "const" Name '=' Expression
        Expression:
            Term
            Expression '+' Term
            Expression '-' Term
        Term:
            Primary
            Term '*' Primary
            Term '/' Primary
            Term '%' Primary
        Primary:
            '('Expression')'
            '{'Expression'}'
            '-'Primary
            '+'Primary
            Primary'!'
            Name
            Name = Expression
            Number
        Name:
            "sqrt("Expression')'
            "pow("Expression, Expression')'
            VariableName
        Number:
            FloatValue'!'
            FloatValue
        Print:
            ';'
        Quit:
            'q'
*/

#include "Token_stream.hpp"
#include "Variables.hpp"

class Calculator {
public:
    Calculator();
    void calculate();
private:
    Token_stream ts;
    Variables vs;

    double number();
    double math_function(const std::string name);
    double name();
    double primary();
    double term();
    double expression();
    double declaration(const std::string type);
    double statement();
};

#endif