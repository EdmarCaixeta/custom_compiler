#include "token.h"

class TokenNode
{
private:
    Token *_current;
    TokenNode *_next;

public:
    TokenNode(Token *);
    TokenNode(Token *, TokenNode *);
    void setNext(TokenNode *);
    TokenNode *getNext() { return _next; };
    void print()
    {
        if (_current == nullptr)
        {
            std::cout << "JOCA";
        }
        else
        {

            _current->print();
        }
    }
    int getTokenValue() { return this->_current->getToken(); };
};
