#ifndef TOKEN_STREAM
#define TOKEN_STREAM

#include <exception>
#include <stdexcept>

constexpr char type_number = '8';
constexpr char type_quit = 'q';
constexpr char type_print = ';';
constexpr char type_name = 'N';
constexpr char type_let = 'L';
constexpr char type_const = 'C';
constexpr char decl_key[] = "let";
constexpr char cons_key[] = "const";
constexpr char func_sqrt[] = "sqrt";
constexpr char func_pow[] = "pow";

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