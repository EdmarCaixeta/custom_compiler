#ifndef TOKENLIST_H_
#define TOKENLIST_H_
#include "token_node.h"

class TokenList
{
private:
    TokenNode *_head;
    TokenNode *_tail;
    int _reference_counter = 0;

public:
    TokenList();
    TokenList(Token *);
    TokenNode *head() { return this->_head; };
    TokenNode *tail() { return this->_tail; };
    void append(Token *);
    TokenList *use();
    void dismiss();
    void print();
};
#endif