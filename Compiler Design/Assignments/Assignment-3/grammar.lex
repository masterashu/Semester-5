%{
#include "clr_table.hpp"
#include "clr_parser.hpp"
using namespace std;
%}

%option noyywrap


NUM [0-9]+
ADD \+
MUL \*
POW \^
MINUS \-
PARASTART \(
PARAEND \)
WS       [ \t]
%%

{NUM}			return NUM;
{ADD}			return ADD;
{MUL}			return MUL;
{POW}			return POW;
{MINUS}			return MINUS;
{PARASTART}		return PARASTART;
{PARAEND}		return PARAEND;
{WS}			;
[\$\r\n]		return 0;
.				return 0;
%%
int main(){
    FlexLexer* lexer = new yyFlexLexer;
    int x;
    CLRParser parser = CLRParser(false);
    parser.run(lexer);
    return 0;
}
