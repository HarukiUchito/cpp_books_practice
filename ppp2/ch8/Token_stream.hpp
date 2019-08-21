#ifndef TOKEN_STREAM
#define TOKEN_STREAM

#include "Constants.hpp"

#include <exception>
#include <stdexcept>

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
    Token(char t, std::string v)
        : type(t), name(v) {}
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

#endif