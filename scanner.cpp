#include "scanner.h"

using namespace std;

bool isoperator(char c)
{
    string ptr;
    ptr += c;
    std::regex str_expr("<|>|-|\\/|\\+|\\*|%|=|!");
    if (std::regex_match(ptr.c_str(), str_expr))
    {
        ptr.clear();
        return true;
    }
    ptr.clear();
    return false;
}

bool isseparator(char c)
{
    string ptr;
    ptr += c;
    std::regex str_expr("\\(|\\)|\\[|\\]|\\{|\\}|,|.|;");
    if (std::regex_match(ptr.c_str(), str_expr))
    {
        return true;
    }
    return false;
}

Scanner::Scanner()
{
    this->current_state = 0;
    this->buffer;
}

void Scanner::feed(string c)
{
    int pos = 0;
    c.push_back('\n');

    /* Percorre a linha fornecida */
    while (c[pos] != '\n')
    {
        switch (this->current_state)
        {
        case 0:

            if (isspace(c[pos]))
            {
                pos++;
            }

            /* ID state */
            else if (isalpha(c[pos]) || c[pos] == '_')
            {
                current_state = 1;
            }

            /* Int state */
            else if (isdigit(c[pos]))
            {
                current_state = 2;
            }

            /* Coment state */
            else if (c[pos] == '/')
            {
                current_state = 6;
            }

            /* Operator state */
            else if (isoperator(c[pos]))
            {
                current_state = 3;
            }

            /* Literal state */
            else if (c[pos] == '"')
            {
                current_state = 5;
            }

            /* Separator state */
            else if (isseparator(c[pos]))
            {
                current_state = 4;
            }

            /* Invalid state*/
            else
            {
                current_state = -1;
            }
            break;

        case 1:
            /* id[0] */
            buffer.push_back(c[pos]);
            pos++;

            if (isalnum(c[pos]) || c[pos] == '_')
            {
                current_state = 1;
            }

            /* se outra coisa, então acaba id */
            else
            {
                cout << "< id, " << buffer << " >";
                buffer.clear();
                current_state = 0;
            }
            break;

        case 2:
            /* digit */
            buffer.push_back(c[pos]);
            pos++;

            if (isdigit(c[pos]))
            {
                current_state = 2;
            }

            else
            {
                cout << "< num, " << buffer << " >";
                buffer.clear();
                current_state = 0;
            }
            break;

        case 3:
            /* operator */
            cout << "< operator, " << c[pos] << " >";
            pos++;
            current_state = 0;
            break;

        case 4:
            /* operator */
            cout << "< separador, " << c[pos] << " >";
            pos++;
            current_state = 0;
            break;

        case 5:
            /* literal */
            buffer.push_back(c[pos]);
            pos++;

            if (c[pos] != '"')
                current_state = 5;

            else
            {
                buffer.push_back(c[pos]);
                pos++;
                cout << "< literal, " << buffer << " >";
                buffer.clear();
                current_state = 0;
            }
            break;

        case 6:
            /* comment in line, ignore the whole line*/
            if (c[pos + 1] == '/')
            {
                return;
            }

            /* comment in section, ignore until find closing statement */
            else if (c[pos + 1] == '*')
            {
                current_state = 7;
            }

            /* / is operator */
            else
            {
                current_state = 3;
            }
            break;

        case 7:
            pos += 2;
            do
            {
                /* end of line */
                if (c[pos] == '\n')
                    return;
                
                /* imediate case */
                else if(c[pos] == '*' and c[pos+1] == '/')
                    break;
                pos++;
            } while (c[pos] != '*' and c[pos + 1] != '/');
            pos += 2;
            current_state = 0;
            break;

        default:
            cout << "[ERROR] Incorrect word ";
            pos++;
            current_state = 0;
            break;
        }
    }
}