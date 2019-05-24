%{
    #include "fb1-5.tab.h"
    extern void yyerror(char const* s);

    int yylval;
%}

%%
"+" {return ADD;}
"-" {return SUB;}
"*" {return MUL;}
"/" {return DIV;}
"|" {return ABS;}
"(" {return OP;}
")" {return CP;}
"//".* {}
"/*".*"*/" {}
[0-9]+ {yylval=atoi(yytext);return NUMBER;}
\n {return EOL;}
[ \t] {}
. {printf("Mystery character %c\n",yytext[0]);}
%%