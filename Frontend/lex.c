#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

int symb;

extern int yylex(void);
extern FILE *   yyin;
extern voidprintSymb(void);


main(int argc,char ** arg2)
{  
   if((yyin=fopen(arg2[1],"r"))==NULL)
   {  printf("can't open %s\n",arg2[1]);
      exit(0);
   }

   symb = yylex();
   printSymb();

   while(symb != EOF)
   {  
   	   symb = yylex();
   	   printSymb();
   }

   fclose(yyin);
}
