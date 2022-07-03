#include "../header_files/token_list.h"

TokenList::TokenList(Token *head)
{
    this->_head = new TokenNode(head);
    this->_tail = this->_head;
}

TokenList *TokenList::use()
{
    this->_reference_counter++;
    return this;
}

void TokenList::dismiss()
{
    this->_reference_counter--;
}

TokenList::TokenList()
{
    this->_head = nullptr;
    this->_tail = nullptr;
    this->_reference_counter++;
}

void TokenList::append(Token *t)
{
    if (this->_tail != nullptr)
    {
        TokenNode *node = new TokenNode(t);
        this->_tail->setNext(node);
        this->_tail = node;
    }

    else
    {
        this->_head = new TokenNode(t);
        this->_tail = this->_head;
    }
}

void TokenList::print()
{
    TokenNode *ptr = this->_head;
    for (ptr; ptr != nullptr; ptr = ptr->getNext())
    {
        ptr->print();
    }
    std::cout << "REFERENCE COUNTER: " << this->_reference_counter << std::endl;
}
