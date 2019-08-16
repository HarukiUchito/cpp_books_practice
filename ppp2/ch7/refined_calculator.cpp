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
            Number
        Name:
            "sqrt("Expression')'
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

constexpr char type_number = '8';
constexpr char type_quit = 'q';
constexpr char type_print = ';';
constexpr char type_name = 'N';
constexpr char type_let = 'L';
constexpr char decl_key[] = "let";
constexpr char func_sqrt[] = "sqrt";

class Token
{
public:
    char type;
    // '(', ')', '+', '-', '/', '%'
    double value;
    std::string name;
    Token(char t)
        : type(t) {}
    Token(double v)
        : type(type_number), value(v) {}
    Token(std::string v)
        : type(type_name), name(v) {}
};

class Token_stream
{
public:
    Token_stream() {}

    Token get();
    void putback(Token t);
    
    // ignore tokens until a token of type 't' is found
    void ignore(char t);
private:
    bool full{false};
    Token buffer{Token('(')};
};

Token_stream ts;

std::map<std::string, double> varialbes;

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

double name()
{
    Token t = ts.get();
    std::string tname = t.name;
    Token left = ts.get();
    if (left.type != '(') // just an variable
    {
        ts.putback(left);
        if (varialbes.count(t.name) == 0)
            throw std::runtime_error("no such variable");
        return varialbes[t.name];
    }
    else // special function
    {
        Token arg = expression();
        Token right = ts.get();
        if (right.type != ')')
            throw std::runtime_error("')' expected for closing function");
        if (t.name == func_sqrt)
            if (arg.value < 0.0)
                throw std::runtime_error("sqrt: negative argument");
            else
                return sqrt(arg.value);
        else
            throw std::runtime_error("called function is not implemented");
    }
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

double declaration()
{
    Token t = ts.get();
    if (t.type != type_name)
        throw std::runtime_error("variable name expected");
    std::string var_name = t.name;

    Token t2 = ts.get();
    if (t2.type != '=')
        throw std::runtime_error("= missing in decralation");
    
    double d = expression();

    if (varialbes.count(var_name))
        throw std::runtime_error("the variable is already declared");
    return varialbes[var_name] = d;
}

double statement()
{
    Token t = ts.get();
    switch (t.type)
    {
    case type_let:
        return declaration();
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

int main()
try
{
    varialbes["pi"] = 3.1415926535;
    varialbes["e"] = 2.7182818284;
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

void Token_stream::putback(Token t)
{
    if (full)
        throw std::runtime_error("putbacked twice!");
    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }
    char ch;
    cin >> ch;

    switch (ch)
    {
    case type_print:
    case type_quit:
    case '(':
    case ')':
    case '{':
    case '}':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '!':
    case '=':
        return Token(ch);
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        cin.putback(ch);
        double val;
        cin >> val;
        return Token{val};
    }
    default:
        if (isalpha(ch)) {
            string s;
            s += ch;
            while (cin.get(ch) and (isalpha(ch) or isdigit(ch)))
                s += ch;
            cin.putback(ch);
            if (s == decl_key)
                return Token(type_let);
            return Token(s); // name Token
        }
        throw std::runtime_error("Bad token!");
    }
}

void Token_stream::ignore(char t)
{
    // At first, look in the buffer
    if (full and t == buffer.type)
    {
        full = false;
        return;
    }
    full = false;

    char ch = 0;
    while (cin >> ch)
        if (ch == t)
            return;
}