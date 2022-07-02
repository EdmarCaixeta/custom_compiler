#include <iostream>

enum TOKENS
{
    ID,
    INTEGER_LITERAL,
    STRING_LITERAL,
    /* OPERATORS */
    LESS_THAN,
    LESS_EQUAL,
    GREATER_THAN,
    GREATER_EQUAL,
    SUM,
    SUBTRACTION,
    MULTIPLY,
    DIVIDE,
    MOD,
    EQUAL,
    COMPARISON,
    DIFFERENT,
    /* SEPARATORS */
    LEFT_PARENTHESES,
    RIGHT_PARENTHESES,
    LEFT_BRACKETS,
    RIGHT_BRACKETS,
    LEFT_BRACES,
    RIGHT_BRACES,
    SEMI_COLON,
    PERIOD,
    COMMA,
    /* RESERVED WORDS */
    CLASS,
    EXTENDS,
    INT,
    STRING,
    BREAK,
    PRINT,
    READ,
    RETURN,
    SUPER,
    IF,
    ELSE,
    FOR,
    NEW,
    CONSTRUCTOR
};

class Token
{
private:
    int _token;
    std::string _lexeme;

public:
    Token(int token, std::string lexeme)
    {
        this->_lexeme = lexeme;
        this->_token = token;
    };
    void print()
    {
        std::cout
            << "<token: "
            << this->_token << " lexeme: " << this->_lexeme << ">" << std::endl;
    }
};