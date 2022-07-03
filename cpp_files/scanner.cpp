#include "../header_files/scanner.h"

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
    std::regex str_expr("\\(|\\)|\\[|\\]|\\{|\\}|,|\\.|\\;");
    if (std::regex_match(ptr.c_str(), str_expr))
    {
        ptr.clear();
        return true;
    }
    ptr.clear();
    return false;
}

Scanner::Scanner()
{
    this->current_state = 0;
    this->buffer;
    this->tokenList = new TokenList();
}

TokenList *Scanner::getTokenList()
{
    return this->tokenList->use();
}

void Scanner::feed(string c)
{
    Token *tk;
    int pos = 0;
    int enum_type;
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
                enum_type = ID;

                if (buffer == "class")
                {
                    enum_type = CLASS;
                }

                else if (buffer == "extends")
                {
                    enum_type = EXTENDS;
                }

                else if (buffer == "int")
                {
                    enum_type = INT;
                }

                else if (buffer == "string")
                {
                    enum_type = STRING;
                }

                else if (buffer == "break")
                {
                    enum_type = BREAK;
                }

                else if (buffer == "print")
                {
                    enum_type = PRINT;
                }

                else if (buffer == "read")
                {
                    enum_type = READ;
                }

                else if (buffer == "return")
                {
                    enum_type = READ;
                }

                else if (buffer == "super")
                {
                    enum_type = SUPER;
                }

                else if (buffer == "if")
                {
                    enum_type = IF;
                }

                else if (buffer == "else")
                {
                    enum_type = ELSE;
                }

                else if (buffer == "for")
                {
                    enum_type = FOR;
                }

                else if (buffer == "new")
                {
                    enum_type = NEW;
                }

                else if (buffer == "constructor")
                {
                    enum_type = CONSTRUCTOR;
                }

                tk = new Token(enum_type, buffer);
                tokenList->append(tk);
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
                tk = new Token(INTEGER_LITERAL, buffer);
                tokenList->append(tk);
                buffer.clear();
                current_state = 0;
            }
            break;

        case 3:
            /* operator */
            buffer.push_back(c[pos]);

            /* >= */
            if (c[pos] == '>' and c[pos + 1] == '=')
            {
                pos++;
                buffer.push_back(c[pos]);
                enum_type = GREATER_EQUAL;
            }

            /* <= */
            else if (c[pos] == '<' and c[pos + 1] == '=')
            {
                pos++;
                buffer.push_back(c[pos]);
                enum_type = LESS_EQUAL;
            }

            /* != */
            else if (c[pos] == '!' and c[pos + 1] == '=')
            {
                pos++;
                buffer.push_back(c[pos]);
                enum_type = DIFFERENT;
            }

            /* == */
            else if (c[pos] == '=' and c[pos + 1] == '=')
            {
                pos++;
                buffer.push_back(c[pos]);
                enum_type = COMPARISON;
            }

            else if (c[pos] == '=')
            {
                enum_type = EQUAL;
            }

            else if (c[pos] == '+')
            {
                enum_type = SUM;
            }

            else if (c[pos] == '-')
            {
                enum_type = SUBTRACTION;
            }

            else if (c[pos] == '*')
            {
                enum_type = MULTIPLY;
            }

            else if (c[pos] == '/')
            {
                enum_type = DIVIDE;
            }

            else if (c[pos] == '%')
            {
                enum_type = MOD;
            }

            tk = new Token(enum_type, buffer);
            tokenList->append(tk);
            buffer.clear();
            pos++;

            current_state = 0;
            break;

        case 4:
            /* separator */

            buffer.push_back(c[pos]);

            if (c[pos] == '(')
            {
                enum_type = LEFT_PARENTHESES;
            }

            else if (c[pos] == ')')
            {
                enum_type = RIGHT_PARENTHESES;
            }

            else if (c[pos] == '[')
            {
                enum_type = LEFT_BRACES;
            }

            else if (c[pos] == ']')
            {
                enum_type = RIGHT_BRACES;
            }

            else if (c[pos] == '{')
            {
                enum_type = LEFT_BRACKETS;
            }

            else if (c[pos] == '}')
            {
                enum_type = RIGHT_BRACKETS;
            }

            else if (c[pos] == ',')
            {
                enum_type = COMMA;
            }

            else if (c[pos] == '.')
            {
                enum_type = PERIOD;
            }

            else if (c[pos] == ';')
            {
                enum_type = SEMI_COLON;
            }

            tk = new Token(enum_type, buffer);
            tokenList->append(tk);
            buffer.clear();
            pos++;
            current_state = 0;
            break;

        case 5:
            /* string literal */
            buffer.push_back(c[pos]);
            pos++;

            if (c[pos] != '"')
                current_state = 5;

            else
            {
                buffer.push_back(c[pos]);
                pos++;
                tk = new Token(STRING_LITERAL, buffer);
                tokenList->append(tk);
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
            /* Comment in section*/
            pos += 2;
            do
            {
                /* reached end of line, so stop */
                if (c[pos] == '\n')
                    return;

                /* imediate case */
                else if (c[pos] == '*' and c[pos + 1] == '/')
                    break;
                pos++;
            } while (c[pos] != '*' and c[pos + 1] != '/');
            pos += 2;
            current_state = 0;
            break;

        default:
            cout << "[ERROR] Unexpected character: " << c[pos] << endl;
            pos++;
            current_state = 0;
            break;
        }
    }
}