#include "token_node.h"

class TokenList
{
private:
    TokenNode *_head;
    TokenNode *_tail;

public:
    TokenList();
    TokenList(Token *);
    TokenNode *head() { return this->_head; };
    TokenNode *tail() { return this->_tail; };
    void append(Token *);
    void print();
};