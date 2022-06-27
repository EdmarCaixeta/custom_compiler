#include <iostream>

enum TOKENS
{
    ID,
    INTEGER_LITERAL,
    OP,
    SEP,
    STRING_LITERAL,
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
        std::cout << std::endl
                  << "<token: "
                  << this->_token << " lexeme: " << this->_lexeme << ">" << std::endl;
    }
};