/*
    Simple Calculator
    
    input from cin
    output to cout

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

#include <bits/stdc++.h>
using namespace std;

#include "Token_stream.hpp"

Token_stream ts;

// run-time checked narrowing cast (type conversion). See ???.
template <class R, class A>
R narrow_cast(const A &a)
{
    R r = R(a);
    if (A(r) != a)
        throw std::runtime_error("info loss");
    return r;
}

class Variables {
public:
    double get_value(const std::string name);
    double change_value(const std::string name, const double value);
    double store_value(const std::string name, const double value, const std::string type);
private:
    std::map<std::string, double> variables;
    std::map<std::string, double> constants;
};

Variables vs;

double Variables::get_value(const std::string name)
{
    if (variables.count(name))
        return variables[name];
    if (constants.count(name))
        return constants[name];
    throw std::runtime_error("the variable is not defined");
}

double Variables::change_value(const std::string name, const double value)
{
    if (constants.count(name))
        throw std::runtime_error("constant value cannot be changed");
    if (variables.count(name) == 0)
        throw std::runtime_error("change value: the variable is not defined");
    return variables[name] = value;
}

double Variables::store_value(const std::string name, const double value, const std::string type)
{
    if (variables.count(name) or constants.count(name))
        throw std::runtime_error("store value: the variable is already defined");
    if (type == decl_key)
        return variables[name] = value;
    else if (type == cons_key)
        return constants[name] = value;
    else
        throw std::runtime_error("store value: unknown type");
}

double expression();

double number()
{
    Token t = ts.get(), e = ts.get();
    double v = t.value;
    if (e.type == '!')
    {
        int num = int(v);
        v = 1;
        for (int i = 1; i <= num; ++i)
            v *= i;
    }
    else
        ts.putback(e);
    return v;
}

double math_function(const std::string name)
{
    if (name == func_sqrt)
    {
        double arg = expression();
        Token right = ts.get();
        if (right.type != ')')
            throw std::runtime_error("')' expected for closing function");
        if (arg < 0.0)
            throw std::runtime_error("sqrt: negative argument");
        else
            return sqrt(arg);
    }
    else if (name == func_pow)
    {
        double v = expression();
        Token comma = ts.get();
        if (comma.type != ',')
            throw std::runtime_error("pow: ',' expected between arg1 and arg2");
        try {
            double i = narrow_cast<int, double>(expression());
            Token right = ts.get();
            return pow(v, i);
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("pow: second argument must be integer");
        }
    }
    else
        throw std::runtime_error("called function is not implemented");
}

double name()
{
    Token t = ts.get();
    std::string tname = t.name;
    Token next = ts.get();
    if (next.type == '(') // some kind of function
        return math_function(t.name);
    if (next.type == '=') // assignment
    {
        double value = expression();
        return vs.change_value(tname, value);
    }
    // just an variable
    ts.putback(next);
    return vs.get_value(tname);
}

double primary()
{
    Token t = ts.get();
    switch (t.type)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.type != ')')
            throw std::runtime_error("')' expected");
        return d;
    }
    case '{':
    {
        double d = expression();
        t = ts.get();
        if (t.type != '}')
            throw std::runtime_error("'}' expected");
        return d;
    }
    case type_name:
        ts.putback(t);
        return name();
    case type_number:
        ts.putback(t);
        return number();
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
        throw std::runtime_error("primary expected");
    }
}

double term()
{
    double left = primary();
    Token t = ts.get();
    while (true)
    {
        switch (t.type)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0)
                throw std::runtime_error("0 division");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0)
                throw std::runtime_error("0 division");
            left = fmod(left, d);
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double expression()
{
    double left = term();
    Token t = ts.get();
    while (true)
    {
        switch (t.type)
        {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

double declaration(const std::string type)
{
    Token t = ts.get();
    if (t.type != type_name)
        throw std::runtime_error("variable name expected");
    std::string var_name = t.name;

    Token t2 = ts.get();
    if (t2.type != '=')
        throw std::runtime_error("= missing in decralation");

    double d = expression();
    return vs.store_value(var_name, d, type);
}

double statement()
{
    Token t = ts.get();
    switch (t.type)
    {
    case type_let:
    case type_const:
        return declaration(t.name);
    default:
        ts.putback(t);
        return expression();
    }
}

void calculate()
{
    while (cin)
        try
        {
            Token t = ts.get();
            while (t.type == type_print)
                t = ts.get();
            if (t.type == type_quit)
                return;
            ts.putback(t);
            std::cout << " = " << statement() << std::endl;
        }
        catch (exception &e)
        {
            std::cerr << e.what() << std::endl;
            ts.ignore(type_print);
        }
}

int main() try
{
    vs.store_value("pi", 3.1415926535, cons_key);
    vs.store_value("e", 2.7182818284, cons_key);
    calculate();
    return 0;
}
catch (const exception &e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "something went wrong" << std::endl;
    return 2;
}
