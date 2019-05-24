%{
#include <string.h>
#include "mc.tab.h"
YYSTYPE yylval;
%}

%option yylineno
/*如下依次为注释、常量、关键字、标识符、界符、运算符的词法规则*/
%%
"/*".*"*/"   {}
"//".*$      {}

0[0-7]+      {yylval.type_int=strtol(yytext,NULL,8);printf("%d\n",yylval.type_int);return INT;}
[0-9]+       {yylval.type_int=atoi(yytext);printf("%d\n",yylval.type_int);return INT;}
0[xX][0-9a-fA-F]+ {yylval.type_int=strtol(yytext,NULL,16);printf("%d\n",yylval.type_int);return INT;}
([0-9]*\.[0-9]+)|([0-9]+\.)  {yylval.type_float=atof(yytext); return FLOAT;}
"\"".*"\""   {strcpy(yylval.type_id,yytext);printf("%s\n",yytext);return STRING;}
"\'"[a-zA-Z]"\'"    {yylval.type_char=yytext[1];printf("%c\n",yylval.type_char);return CHAR;}

"char"       {strcpy(yylval.type_id,yytext);printf("KEYWORD char\n");return TYPE;}
"int"        {strcpy(yylval.type_id,yytext);printf("KEYWORD int\n");return TYPE;}
"float"      {strcpy(yylval.type_id,yytext);printf("KEYWORD float\n");return TYPE;}
"if"         {printf("KEYWORD IF\n");return IF;}
"else"       {printf("KEYWORD ELSE\n");return ELSE;}
"switch"     {printf("KEYWORD SWITCH\n");return SWITCH;}
"case"       {printf("KEYWORD CASE\n");return CASE;}
"while"      {printf("KEYOWRD WHILE\n");return WHILE;}
"for"        {printf("KEYWORD FOR");return FOR;}
"break"      {printf("KEYWORD BREAK");return BREAK;}
"continue"   {printf("KEYWORD CONTINUE");return CONTINUE;}
"default"    {printf("KEYWORD default");return DEFAULT;}
"return"     {printf("KEYWORD RETURN");return RETURN;}

[a-zA-Z][a-zA-Z0-9]*       {strcpy(yylval.type_id,  yytext);printf("%s\n",yytext); return ID;}


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
"!" {printf("%c\n",yytext[0]);return yytext[0];}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);printf("%s\n",yylval.type_id);return RELOP;}
"&&"   {printf("AND\n");return AND;}
"||"   {printf("OR\n");return OR;}
 
[ \t\r\n]          {}   
.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}
%%
