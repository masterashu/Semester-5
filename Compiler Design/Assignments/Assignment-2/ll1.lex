%{
#include "l_r.hpp"
#include "ll1.hpp"
vector<left_factoring::Production> Grammar;
int productions = 0;
%}

%option noyywrap



VARIABLE	[A-Z]
TERMINAL	[a-z]
_WS		[ \t\r\n]*
WS		[ \t\r\n]+
OR		[|]
DEF		->
%%
{VARIABLE}{_WS}{DEF}{_WS}({VARIABLE}|{TERMINAL})+({OR}({VARIABLE}|{TERMINAL})+)*		{ left_recursion::AddProduction(yytext, yyleng); }
. ;
%%
int main(){
	cout << "Input Productions:" << endl;
	parser::Ready();
	FlexLexer* lexer = new yyFlexLexer;
	lexer->yylex();
	if(left_recursion::RemoveRecursion(Grammar) != 0) {
		cout << "Unable to remove Left Recursion\n";
		return -1;
	}
	left_factoring::Do_Left_Factoring(Grammar);
	// Adding left factored Productions to parser
	cout << "Productions after Left Factoring" << endl;
	for (int i = 0; i < Grammar.size(); i++){
		char* rule = (char*)malloc(sizeof(char)*(Grammar[i].rule.size() + 1));
		parser::AddProduction(Grammar[i].symbol, Grammar[i].rule.c_str());
		productions++;
		cout << Grammar[i].symbol << "->" << Grammar[i].rule << endl;
	}
	printf("Total Productions Found: %d.\n\n\n", productions);
	try{
		parser::Parse(productions);
	} catch(...){
		cout << "Given Grammar is not LL(1)";
		return -1;
	}
	cout << "Given Grammar is LL(1)";
	return 0;
}

