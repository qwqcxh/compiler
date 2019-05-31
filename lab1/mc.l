%{
#include <string.h>
#include "mc.tab.h"
YYSTYPE yylval;
%}

%option yylineno
/*如下依次为注释、常量、关键字、标识符、界符、运算符的词法规则*/
%%
"/*".*"*/"   {/*printf("Comment\n");*/}
"//".*       {/*printf("Comment\n");*/}

0[0-7]+      {yylval.type_int=strtol(yytext,NULL,8);return INT;}
[0-9]+       {yylval.type_int=atoi(yytext);return INT;}
0[xX][0-9a-fA-F]+ {yylval.type_int=strtol(yytext,NULL,16);return INT;}
([0-9]*\.[0-9]+)|([0-9]+\.)  {yylval.type_float=atof(yytext); return FLOAT;}
"\"".*"\""   {strcpy(yylval.type_id,yytext);return STRING;}
"\'"[a-zA-Z]"\'"    {yylval.type_char=yytext[1];return CHAR;}

"char"       {strcpy(yylval.type_id,yytext);return TYPE;}
"int"        {strcpy(yylval.type_id,yytext);return TYPE;}
"float"      {strcpy(yylval.type_id,yytext);return TYPE;}
"if"         {return IF;}
"else"       {return ELSE;}
"switch"     {return SWITCH;}
"case"       {return CASE;}
"while"      {return WHILE;}
"for"        {return FOR;}
"break"      {return BREAK;}
"continue"   {return CONTINUE;}
"default"    {return DEFAULT;}
"return"     {return RETURN;}

[a-zA-Z][a-zA-Z0-9]*       {strcpy(yylval.type_id,  yytext);return ID;}


";" |
":" |
"," |
"(" |
")" |	
"{" |	
"}" |
"=" |
"+" |
"-" |
"*" |	
"/" |
"[" |
"]" |
"!" {return yytext[0];}
">" {strcpy(yylval.type_id, yytext);return GR;}
"<" {strcpy(yylval.type_id, yytext);return LS;}
">=" {strcpy(yylval.type_id, yytext);return GE;}
"<=" {strcpy(yylval.type_id, yytext);return LE;}
"==" {strcpy(yylval.type_id, yytext);return EQ;}
"!=" {strcpy(yylval.type_id, yytext);return NE;}
"&&"   {return AND;}
"||"   {return OR;}
 
[ \t\r\n]          {}   
.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}
%%
