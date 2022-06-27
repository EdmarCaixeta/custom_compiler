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
        _current->print();
    }
};
