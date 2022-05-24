%option noyywrap
%{
#include <stdio.h>
%}

/* Regular Definitions */
DIGIT [0-9]
CHARACTER [a-zA-Z]
ALPHANUM {CHARACTER}|{DIGIT}

ID (_|{CHARACTER})(_|{ALPHANUM})*
INT {DIGIT}+
OPERATOR ("<="|"<"|">"|">="|"+"|"-"|"*"|"/"|"%"|"="|"=="|"!=")
SEPARATOR ("("|")"|"["|"]"|"{"|"}"|";"|"."|",")
BLANK_SPACE [[:space:]]+

/* Match Routines*/
%%
{ID} { printf("Encontrei um identificador!\n");}
{INT} { printf("Encontrei um inteiro!\n");}
{OPERATOR} { printf("Encontrei um operador!\n");}
{SEPARATOR} { printf("Encontrei um separador!\n");}
{BLANK_SPACE};

%%

/* Code */
int main() {
    yylex();
    return 0;
}