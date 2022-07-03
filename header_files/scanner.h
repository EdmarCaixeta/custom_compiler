#include <regex>
#include <iostream>
#include "token_list.h"

using namespace std;

class Scanner
{
private:
    TokenList *tokenList;
    uint8_t current_state;
    string buffer;

public:
    Scanner();
    ~Scanner();
    void feed(string c);
    TokenList *getTokenList();
};
