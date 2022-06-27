#include "../header_files/token_node.h"

TokenNode::TokenNode(Token *current)
{
    this->_current = current;
    this->_next = nullptr;
};

void TokenNode::setNext(TokenNode *ptr)
{
    this->_next = ptr;
}