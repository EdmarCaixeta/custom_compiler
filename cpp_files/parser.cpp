#include "../header_files/parser.h"

void Parser::advance()
{
    this->_lookahead = this->_lookahead->getNext();
}

Parser::Parser(TokenList *token_list)
{
    this->_lookahead = token_list->head();
    this->_token_list = token_list;
}

void Parser::print()
{
    _token_list->print();
}