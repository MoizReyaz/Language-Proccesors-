#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"

int symb;

extern printSymb();
extern char* showSymb(int);
extern int yylex(void);
extern FILE* yyin;



fixedProc(char * name, int depth)
{  int i;
   for(i=0;i<depth;i++)
    printf(" ");
   printf("%s\n",name);
}




error(char * fixedProc,char * message)
{  printf("%s: found %s\n",fixedProc,showSymb(symb));
   printf("%s: %s\n",fixedProc,message);
   exit(0);
}




lex(){
  printSymb();
   symb = yylex();
}
program(int depth){
 	fixedProc("program",depth);
	methods(depth+1);
}
methods(int depth){
	fixedProc("methods",depth);
	method(depth+1);
	if(symb==METHOD){
			methods(depth+1);
	}

}



method(int depth)
{	fixedProc("method",depth);
	if(symb!=METHOD){
		error("method","METHOD expected\n");
}
	
	lex();
	if (symb!=ID && symb != MAIN){
		error("method","identifier expected\n");
}
	
	lex();
	if (symb!=LBRA){
		error("method","( expected\n");
	
}lex();
	if(symb==ID){
	args(depth+1);
}
	if (symb!=RBRA){
		error("method",") expected\n");
	

}lex();
	if (symb==VARS){
	lex();
	args(depth+1);
	}
	if (symb!=BEGIN){
		error("method","begin expected\n");
	
}lex();
	statements(depth+1);
	if (symb==RETURN){
	
	lex();
	if (symb==ID)
	lex();
	if (symb==SEMI)
	lex();
	}
	if (symb!=ENDMETHOD){
		error("method","endmethod expected\n");
	
	
}lex();
}
args(int depth){
	fixedProc("args",depth);
	
	if (symb!=ID){
		error("args","identifier expected\n");
	}lex();

		if (symb==COMMA){	
	lex();
	args(depth+1);
}
}

statements (int depth){
 	fixedProc("statements",depth);

	statement(depth+1);
	if(symb!=SEMI){	
		error("statements","; expected\n");
}lex();
	if(symb== ID || symb == IF|| symb == WHILE|| symb == READ|| symb == WRITE){

	statements(depth+1);	
}
}		
statement(int depth){
    fixedProc("statement",depth);
	switch(symb){
		case ID: 
			assign(depth+1);
		break;
		case IF: lex();
				ifComm(depth+1);
		break;
		case WHILE: lex();
				whileComm(depth+1);
		break;
		case READ: 
				rw(depth+1);
		break;
		case WRITE:
				rw(depth+1);
		break;
	default:
	 error("command","ID/if/while/rw/identifier expected\n");
}
}

rw(int depth){	
	fixedProc("rw",depth);
	switch(symb){ 
		case READ: lex();
				if (symb!=ID){
					 error("rw","identifier expected\n");
					
				}
				lex();
				break;
		case WRITE: lex();
	  			exprs(depth+1);
		
	}
	
}
assign (int depth){
	fixedProc("assign",depth);
	lex();
	if(symb!=ASSIGN){
		error("assign",":= expected\n");
	}
	lex();
	expr(depth+1);
}
ifComm(int depth){
	fixedProc("ifcomm",depth);
	cond(depth+1);
	if(symb!=THEN){
		error("ifcomm","THEN expected\n");
	}	
	lex();
	statements(depth+1);
	if(symb==ELSE){ 
	lex(); 
	  statements(depth+1);
	}
	if(symb!=ENDIF){
	error("ifcomm","endif expected\n");
	}
	lex();	
}
whileComm(int depth){
	fixedProc("whilecomm",depth);
	cond(depth+1);
	if(symb!=BEGIN)
		error("whilecomm","begin expected\n");
		lex();
	statements(depth+1);
	if(symb!=ENDWHILE){
		error("whilecomm","endwhile expected\n");
	}
	lex();
}
cond(int depth){
	fixedProc("cond", depth);
	bop(depth+1);
	if(symb!=LBRA){
		error("cond","( expected\n");
	}lex();
	exprs(depth+1);
	if(symb!=RBRA){
		error("cond",") expected\n");
	}
	lex();
}
bop(int depth){
	fixedProc("bop",depth);
	switch(symb){
		case LT: lex();
				break;
		case LTE: lex();
				break;
		case EQ: lex();
			break;
		case NEQ: lex();
			break;
		default: error("bop","less/lesseq/eq/neq expected\n");
	} 
	
	
}
exprs(int depth){

	fixedProc("exprs",depth);
	expr(depth+1);
	if(symb==COMMA){
	
	lex();
	exprs(depth+1);
}
}
expr(int depth){
	fixedProc("expr",depth);
	switch(symb){
		case PLUS:
		case TIMES:
		case MINUS:
		case DIVIDE:
		case ID: lex();
				if(symb==LBRA){
					lex();
					exprs(depth+1);
					if(symb!=RBRA){
						error("expr",") expected\n");
					}lex();
				}
				break;
		case INT : lex();
					break;
		default: error("expr","id/int expected\n");
		lex();
	}
}

main(int c,char ** argv)
{  
   if((yyin=fopen(argv[1],"r"))==NULL){  
      printf("can't open %s\n",argv[1]);
      exit(0);
   }
   symb = yylex();
   program(1);
   fclose(yyin);
}
