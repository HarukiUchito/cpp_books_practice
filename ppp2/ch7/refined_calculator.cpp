#include <bits/stdc++.h>
using namespace std;

class Token
{
public:
    char type;
    // '8' for numbers
    // '(', ')', '+', '-', '/', '%'
    double value;
    Token(char t)
        : type(t) {}
    Token(double v)
        : type('8'), value(v) {}
};

class Token_stream
{
public:
    Token_stream() {}

    Token get();

    void putback(Token t);

private:
    bool full{false};
    Token buffer{Token('(')};
};

Token_stream ts;

double expression();

// [Grammer]
// Number
//     FloatValue!
//     FloatValue
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
// Primary:
//     Primary!
//     Number
//     '('Expression')'
//     '{'Expression'}'
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
    case '8':
        ts.putback(t);
        return number();
    default:
        throw std::runtime_error("primary expected");
    }
}

// Term:
//     Primary
//     Term '*' Primary
//     Term '/' Primary
//     Term '%' Primary
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
        /* TODO add later
        case '%':
            left %= primary();
            t = get_token();
            break;
        */
        default:
            ts.putback(t);
            return left;
        }
    }
}

// Expression:
//     Term
//     Expression '+' Term
//     Expression '-' Term
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

int main()
{
    try
    {
        while (cin)
        {
            Token t = ts.get();
            while (t.type == ';')
                t = ts.get();
            if (t.type == 'q')
                return 0;
            ts.putback(t);
            std::cout << " = " << expression() << std::endl;
        }
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

    return 0;
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
    case ';':
    case 'q':
    case '(':
    case ')':
    case '{':
    case '}':
    case '+':
    case '-':
    case '*':
    case '/':
    case '!':
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
        throw std::runtime_error("Bad token!");
    }
}