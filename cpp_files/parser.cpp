#include "../header_files/parser.h"

void Parser::advance()
{
    this->_lookahead = this->_lookahead->getNext();
}

Parser::Parser(TokenList *token_list)
{
    Token *end = new Token(END_OF_FILE, "?");
    token_list->append(end);
    this->_lookahead = token_list->head();
    this->_token_list = token_list;
}

void Parser::print()
{
    _lookahead->print();
}

void Parser::match(int t)
{
    if (this->_lookahead->getTokenValue() == t)
        advance();
    else
    {
        std::cout << "[ERROR] Unmatched token" << std::endl;
        exit(1);
    }
}

void Parser::Program()
{
    if (_lookahead->getTokenValue() == CLASS)
    {
        ClassList();
    }
    match(END_OF_FILE);
    std::cout << "[SUCCESS] Lexical and Syntax analysis completed!" << std::endl;
}

void Parser::ClassList()
{
    ClassDecl();
    if (_lookahead->getTokenValue() == CLASS)
    {
        ClassList();
    }
}

void Parser::AtribStatOpt()
{
    if (_lookahead->getTokenValue() == ID)
    {
        AtribStat();
    }
}

void Parser::Statement()
{
    if (_lookahead->getTokenValue() == ID)
    {
        if (_lookahead->getNext()->getTokenValue() == EQUAL)
            AtribStat();
        else
            VarDeclList();
    }
    else if (_lookahead->getTokenValue() == SEMI_COLON)
    {
        match(SEMI_COLON);
    }

    else if (_lookahead->getTokenValue() == BREAK)
    {
        match(BREAK);
        match(SEMI_COLON);
    }

    else if (_lookahead->getTokenValue() == FOR)
    {
        ForStat();
    }

    else if (_lookahead->getTokenValue() == IF)
    {
        IfStat();
    }

    else if (_lookahead->getTokenValue() == SUPER)
    {
        SuperStat();
        match(SEMI_COLON);
    }

    else if (_lookahead->getTokenValue() == RETURN)
    {
        ReturnStat();
        match(SEMI_COLON);
    }

    else if (_lookahead->getTokenValue() == READ)
    {
        ReadStat();
        match(SEMI_COLON);
    }

    else if (_lookahead->getTokenValue() == PRINT)
    {
        PrintStat();
        match(SEMI_COLON);
    }
}

void Parser::ClassDecl()
{
    match(CLASS);
    match(ID);
    if (_lookahead->getTokenValue() == EXTENDS)
    {
        match(EXTENDS);
        match(ID);
    }
    ClassBody();
}

void Parser::ClassBody()
{
    match(LEFT_BRACKETS);
    VarDeclListOpt();
    ConstructDeclListOpt();
    MethodDeclListOpt();
    match(RIGHT_BRACKETS);
}

void Parser::Type()
{
    if (_lookahead->getTokenValue() == INT)
        match(INT);
    else if (_lookahead->getTokenValue() == STRING)
        match(STRING);
    else if (_lookahead->getTokenValue() == ID)
        match(ID);
}

void Parser::Factor()
{
    if (_lookahead->getTokenValue() == INTEGER_LITERAL)
        match(INTEGER_LITERAL);
    else if (_lookahead->getTokenValue() == STRING_LITERAL)
        match(STRING_LITERAL);
    else if (_lookahead->getTokenValue() == LEFT_PARENTHESES)
    {
        match(LEFT_PARENTHESES);
        Expression();
        match(RIGHT_PARENTHESES);
    }
    else if (_lookahead->getTokenValue() == ID)
        LValue();
}

void Parser::UnaryExpression()
{
    if (_lookahead->getTokenValue() == SUM)
    {
        match(SUM);
        Factor();
    }
    else if (_lookahead->getTokenValue() == SUBTRACTION)
    {
        match(SUBTRACTION);
        Factor();
    }
}

void Parser::Term()
{
    UnaryExpression();
    if (_lookahead->getTokenValue() == MULTIPLY)
    {
        match(MULTIPLY);
        UnaryExpression();
    }
    else if (_lookahead->getTokenValue() == DIVIDE)
    {
        match(DIVIDE);
        UnaryExpression();
    }
    else if (_lookahead->getTokenValue() == MOD)
    {
        match(MOD);
        UnaryExpression();
    }
}

void Parser::NumExpression()
{
    Term();
    if (_lookahead->getTokenValue() == SUM)
    {
        match(SUM);
        Term();
    }
    else if (_lookahead->getTokenValue() == SUBTRACTION)
    {
        match(SUBTRACTION);
        Term();
    }
}

void Parser::LValueComp()
{
    if (_lookahead->getTokenValue() == PERIOD)
    {
        match(PERIOD);
        match(ID);
        if (_lookahead->getTokenValue() == LEFT_BRACES)
        {
            Expression();
            match(RIGHT_BRACES);
            LValueComp();
        }
        else if (_lookahead->getTokenValue() == PERIOD)
        {
            LValueComp();
        }
    }
}

void Parser::LValue()
{
    match(ID);
    if (_lookahead->getTokenValue() == LEFT_BRACES)
    {
        Expression();
        match(RIGHT_BRACES);
        LValueComp();
    }
    else if (_lookahead->getTokenValue() == PERIOD)
    {
        LValueComp();
    }
}

void Parser::ExpressionOpt()
{
    if (_lookahead->getTokenValue() == SUM || _lookahead->getTokenValue() == SUBTRACTION)
        Expression();
}

void Parser::Expression()
{
    NumExpression();
    if (_lookahead->getTokenValue() == GREATER_EQUAL)
    {
        match(GREATER_EQUAL);
        NumExpression();
    }
    else if (_lookahead->getTokenValue() == GREATER_THAN)
    {
        match(GREATER_THAN);
        NumExpression();
    }
    else if (_lookahead->getTokenValue() == LESS_EQUAL)
    {
        match(LESS_EQUAL);
        NumExpression();
    }
    else if (_lookahead->getTokenValue() == LESS_THAN)
    {
        match(LESS_THAN);
        NumExpression();
    }
    else if (_lookahead->getTokenValue() == DIFFERENT)
    {
        match(DIFFERENT);
        NumExpression();
    }
    else if (_lookahead->getTokenValue() == EQUAL)
    {
        match(EQUAL);
        NumExpression();
    }
}

void Parser::AllocExpression()
{
    if (_lookahead->getTokenValue() == NEW)
    {
        match(NEW);
        match(ID);
        match(LEFT_PARENTHESES);
        ArgListOpt();
        match(RIGHT_PARENTHESES);
    }

    else if (_lookahead->getTokenValue() == INT || _lookahead->getTokenValue() == STRING || _lookahead->getTokenValue() == ID)
    {
        Type();
        match(LEFT_BRACES);
        Expression();
        match(RIGHT_BRACES);
    }
}

void Parser::Statements()
{
    Statement();
    Statements_();
}

void Parser::StatementsOpt()
{
    if (_lookahead->getTokenValue() == ID || _lookahead->getTokenValue() == SEMI_COLON ||
        _lookahead->getTokenValue() == BREAK ||
        _lookahead->getTokenValue() == FOR ||
        _lookahead->getTokenValue() == IF ||
        _lookahead->getTokenValue() == SUPER ||
        _lookahead->getTokenValue() == RETURN ||
        _lookahead->getTokenValue() == READ ||
        _lookahead->getTokenValue() == PRINT)
    {
        Statements();
    }
}

void Parser::Statements_()
{
    if (_lookahead->getTokenValue() == ID || _lookahead->getTokenValue() == SEMI_COLON ||
        _lookahead->getTokenValue() == BREAK ||
        _lookahead->getTokenValue() == FOR ||
        _lookahead->getTokenValue() == IF ||
        _lookahead->getTokenValue() == SUPER ||
        _lookahead->getTokenValue() == RETURN ||
        _lookahead->getTokenValue() == READ ||
        _lookahead->getTokenValue() == PRINT)
    {
        Statement();
        Statements_();
    }
}

void Parser::IfStat()
{
    match(IF);
    match(LEFT_PARENTHESES);
    Expression();
    match(RIGHT_PARENTHESES);
    match(LEFT_BRACKETS);
    Statements();
    match(RIGHT_BRACKETS);
    if (_lookahead->getTokenValue() == ELSE)
    {
        match(ELSE);
        match(LEFT_BRACKETS);
        Statements();
        match(RIGHT_BRACKETS);
    }
}

void Parser::SuperStat()
{
    match(SUPER);
    match(LEFT_PARENTHESES);
    ArgListOpt();
    match(RIGHT_PARENTHESES);
}

void Parser::ReturnStat()
{
    match(RETURN);
    Expression();
}

void Parser::ReadStat()
{
    match(READ);
    LValue();
}

void Parser::PrintStat()
{
    match(PRINT);
    Expression();
}

void Parser::ConstructDecl()
{
    match(CONSTRUCTOR);
    MethodBody();
}

void Parser::MethodDecl()
{
    Type();
    if (_lookahead->getTokenValue() == LEFT_BRACES)
    {
        match(LEFT_BRACES);
        match(RIGHT_BRACES);
    }
    match(ID);
    MethodBody();
}

void Parser::MethodBody()
{
    match(LEFT_PARENTHESES);
    ParamListOpt();
    match(RIGHT_PARENTHESES);
    match(LEFT_BRACKETS);
    StatementsOpt();
    match(RIGHT_BRACKETS);
}

void Parser::ParamListOpt()
{
    if (_lookahead->getTokenValue() == ID || _lookahead->getTokenValue() == STRING || _lookahead->getTokenValue() == INT)
    {
        ParamList();
    }
}

void Parser::Param()
{
    Type();
    if (_lookahead->getTokenValue() == LEFT_BRACES)
    {
        match(LEFT_BRACES);
        match(RIGHT_BRACES);
    }
    match(ID);
}

void Parser::VarDecl()
{
    Type();
    if (_lookahead->getTokenValue() == LEFT_BRACES)
    {
        match(LEFT_BRACES);
        match(RIGHT_BRACES);
    }
    match(ID);
    VarDeclOpt();
    match(SEMI_COLON);
}

void Parser::VarDeclOpt()
{
    if (_lookahead->getTokenValue() == COMMA)
    {
        match(COMMA);
        match(ID);
        VarDeclOpt();
    }
}

void Parser::AtribStat()
{
    LValue();
    match(EQUAL);

    if (_lookahead->getTokenValue() == SUM || _lookahead->getTokenValue() == SUBTRACTION)
    {
        Expression();
    }

    else if (_lookahead->getTokenValue() == NEW || _lookahead->getTokenValue() == INT || _lookahead->getTokenValue() == STRING || _lookahead->getTokenValue() == ID)
    {
        AllocExpression();
    }
}

void Parser::ForStat()
{
    match(FOR);
    match(RIGHT_PARENTHESES);
    AtribStatOpt();
    match(SEMI_COLON);
    ExpressionOpt();
    match(SEMI_COLON);
    AtribStatOpt();
    match(LEFT_PARENTHESES);
    match(LEFT_BRACKETS);
    Statements();
    match(RIGHT_BRACKETS);
}

void Parser::ArgList_()
{
    if (_lookahead->getTokenValue() == COMMA)
    {
        Expression();
        ArgList_();
    }
}

void Parser::ArgList()
{
    Expression();
    ArgList_();
}

void Parser::ArgListOpt()
{
    if (_lookahead->getTokenValue() == SUM || _lookahead->getTokenValue() == SUBTRACTION)
    {
        ArgList();
    }
}

void Parser::VarDeclList_()
{
    if (_lookahead->getTokenValue() == STRING || _lookahead->getTokenValue() == INT || _lookahead->getTokenValue() == ID)
    {
        VarDecl();
        VarDeclList_();
    }
}

void Parser::VarDeclList()
{
    VarDecl();
    VarDeclList_();
}

void Parser::VarDeclListOpt()
{
    if (_lookahead->getTokenValue() == STRING || _lookahead->getTokenValue() == INT || _lookahead->getTokenValue() == ID)
    {
        VarDeclList();
    }
}

void Parser::ConstructDeclList()
{
    ConstructDecl();
    ConstructDeclList_();
}

void Parser::ConstructDeclList_()
{
    if (_lookahead->getTokenValue() == CONSTRUCTOR)
    {
        ConstructDecl();
        ConstructDeclList_();
    }
}

void Parser::ConstructDeclListOpt()
{
    if (_lookahead->getTokenValue() == CONSTRUCTOR)
    {
        ConstructDeclList();
    }
}

void Parser::MethodDeclList()
{
    MethodDecl();
    MethodDeclList_();
}

void Parser::MethodDeclList_()
{
    if (_lookahead->getTokenValue() == INT || _lookahead->getTokenValue() == ID || _lookahead->getTokenValue() == STRING)
    {
        MethodDecl();
        MethodDeclList_();
    }
}

void Parser::MethodDeclListOpt()
{
    if (_lookahead->getTokenValue() == INT || _lookahead->getTokenValue() == ID || _lookahead->getTokenValue() == STRING)
    {
        MethodDeclList();
    }
}

void Parser::ParamList()
{
    Param();
    ParamList_();
}

void Parser::ParamList_()
{
    if (_lookahead->getTokenValue() == COMMA)
    {
        match(COMMA);
        Param();
        ParamList_();
    }
}