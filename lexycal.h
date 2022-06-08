#include <regex>

using namespace std;

bool isoperator(char *c)
{
    std::regex str_expr("<|>|-|/|\\+|\\*|%");
    if (std::regex_match(c, str_expr))
    {
        return true;
    }
    return false;
}

bool isseparator(char *c)
{
    std::regex str_expr("\\(|\\)|\\[|\\]|\\{|\\}|,|.|;");
    if (std::regex_match(c, str_expr))
    {
        return true;
    }
    return false;
}

class Scanner
{
private:
    uint8_t current_state;
    string buffer;

public:
    Scanner();
    ~Scanner();
    void feed(char *c);
};

Scanner::Scanner()
{
    this->current_state = 0;
    this->buffer = "";
}

void Scanner::feed(char *c)
{
    cout << "feed:"<< c << " ";
    switch (this->current_state)
    {
    /*Estado 0, checa o ínicio da palavra e direciona para estados tratadores*/
    case 0:
        /*Se for um id direciona para o estado 1*/
        if ((isalpha(*c) || *c == '_') && !isspace(*c))
        {
            this->current_state = 1;
        }

        /*Se for um inteiro direciona para o estado 2*/
        if (isdigit(*c))
        {
            this->current_state = 2;
        }

        /*Se for operador direciona para o estado 3*/
        /*if (isoperator(c))
        {
            this->current_state = 3;
        }
        /*Se for separador direciona para o estado 4*/
        /*
        if (isseparator(c))
        {
            this->current_state = 4;
        }

        /*Se for literal direciona para o estado  5*/

        /*Se for comentário direciona para o estado 6*/
    // Estado 1: identificadores
    case 1:
        if (isalnum(*c) || *c == '_')
        {
            cout << "adicionado:" << c << " ";
            this->buffer.append(c);
            this->current_state = 1;
        }

        else
        {
            cout << "<id, " << this->buffer << "> ";
            this->buffer.clear();
            this->current_state = 0;
        }
        break;

    /*Se encontrar caractere não válido*/
    default:
        this->current_state = 0;
        std::cout << "[ERROR] Not valid" << std::endl;
        break;
    }
}
