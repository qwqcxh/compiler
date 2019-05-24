%{
#include <stdio.h>
#include <math.h>
void yyerror(char const*s);
int yylex();
%}

/*declare tokens*/
%token NUMBER ADD SUB MUL DIV ABS EOL OP CP
%%

calclist:
    |calclist exp EOL {printf("=%d\n",$2);}
    ;
exp:  factor {$$=$1;}
    | exp ADD factor{$$=$1+$3;}
    | exp SUB factor{$$=$1-$3;}
    ;
factor: term {$$=$1;}
    | factor MUL term {$$=$1*$3;}
    | factor DIV term {$$=$1/$3;}
    ;
term: NUMBER {$$=$1;}
    |ABS term {$$=$2>0?$2:-$2;}
    | OP exp CP {$$=$2;}
    ;
%%
int main(int argc,char**argv){
    yyparse();
    return 0;
}
void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
 }