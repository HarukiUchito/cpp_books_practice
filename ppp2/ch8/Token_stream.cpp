#include "Token_stream.hpp"

#include <string>
#include <iostream>
using namespace std;

bool isalphaOrUnder(const char c)
{
    return (c == '_') or isalpha(c);
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
    case ',':
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
        if (isalphaOrUnder(ch))
        {
            string s;
            s += ch;
            while (cin.get(ch) and (isalphaOrUnder(ch) or isdigit(ch)))
                s += ch;
            cin.putback(ch);
            if (s == decl_key)
                return Token(type_let, decl_key);
            if (s == cons_key)
                return Token(type_const, cons_key);
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