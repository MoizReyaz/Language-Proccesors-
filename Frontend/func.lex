%{
#include "tokens.h"
%}

DIGIT    [0-9]
IDENT    [a-zA-Z][A-Za-z0-9]*        
%%

";" 		{ return SEMI;}
","			{ return COMMA; }
":="		{ return ASSIGN; }
"("			{ return LBRA; }
")"			{ return RBRA; }
"begin"		{ return BEGIN; }
"method"	{ return METHOD; }
"if"		{ return IF; }
"endmethod"	{ return ENDMETHOD; }
"vars"		{ return VARS; }
"while"		{ return WHILE; }
"else"		{ return ELSE; }
"endif"		{ return ENDIF; }
"endwhile"	{ return ENDWHILE; }
"plus"		{ return PLUS; }
"minus"		{ return MINUS; }
"times"		{ return TIMES; }
"divide"	{ return DIVIDE; }
"less"		{ return LT; }
"lessEq"	{ return LTE; }
"eq"		{ return EQ; }
"nEq"		{ return NEQ; }
"main"		{ return MAIN; }
"then"		{ return THEN; }
"read"		{ return READ; }
"write"		{ return WRITE; }
"return"	{ return RETURN; }
{DIGIT}+ 	{ return INT; }
{IDENT}		{ return ID; }
<<EOF>>		{ return EOF; }

[ \t\n]+     /* eat up whitespace */

%%

int yywrap() { return EOF; }

