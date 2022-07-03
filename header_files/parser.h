#ifndef PARSER_H_
#define PARSER_H_

#include "token_list.h"

class Parser
{
private:
    TokenNode *_lookahead;
    TokenList *_token_list;

public:
    Parser(TokenList *);
    void advance();
    void match(int);
    void print();

    /* Grammar Definitions */
    void Program();
    void ClassList();
    void ClassDecl();
    void ClassBody();
    void VarDeclListOpt();
    void VarDeclList();
    void VarDeclList_();
    void VarDecl();
    void VarDeclOpt();
    void Type();
    void ConstructDeclListOpt();
    void ConstructDeclList();
    void ConstructDeclList_();
    void ConstructDecl();
    void MethodDeclListOpt();
    void MethodDeclList();
    void MethodDecl();
    void MethodDeclList_();
    void MethodBody();
    void ParamListOpt();
    void ParamList();
    void ParamList_();
    void Param();
    void StatementsOpt();
    void Statements();
    void Statements_();
    void Statement();
    void AtribStat();
    void PrintStat();
    void ReadStat();
    void ReturnStat();
    void SuperStat();
    void IfStat();
    void ForStat();
    void AtribStatOpt();
    void ExpressionOpt();
    void LValue();
    void LValueComp();
    void Expression();
    void AllocExpression();
    void NumExpression();
    void Term();
    void UnaryExpression();
    void Factor();
    void ArgListOpt();
    void ArgList();
    void ArgList_();
};

#endif