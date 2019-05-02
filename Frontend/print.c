
#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

extern int symb;
extern char * yytext;

char * showSymb(int symb)
{  switch(symb)
{  case  BEGIN: return "begin";
   case  METHOD: return "method";
   case  IF: return "if";
   case  ENDMETHOD: return "endmethod";
   case  VARS: return "vars";
   case  WHILE: return "while";
   case  ELSE: return "else";
   case  ENDIF: return "endif";
   case  ENDWHILE: return "endwhile";   
   case  PLUS: return "plus";
   case  MINUS: return "minus";
   case 	TIMES: return "times";
   case 	DIVIDE: return "divide";
   case  LBRA: return "(";
   case  RBRA: return ")";
   case  LT: return "less";
   case  LTE: return "lessEq";
   case  EQ: return "eq";
   case  NEQ: return "nEq";
   case  MAIN: return "main";
   case  THEN: return "then";
   case  READ: return "read";
   case  WRITE: return "write";
   case  ASSIGN: return ":="; 
   case  RETURN: return "return"; 
   case  INT: return "INT"; 
   case  ID: return "ID"; 
   case  COMMA: return ","; 
   case SEMI: return ";";
   case EOF: return "EOF";
   
   default: printf("bad symbol: %d",symb);
}
}

printSymb()
{  char * s;
printf("%s ",showSymb(symb));
if(symb==ID || symb==INT){
 if(yytext == NULL)
   printf("Error: yytext is null");
 else
   printf("%s\n",yytext);
} else
 printf("\n");
}
