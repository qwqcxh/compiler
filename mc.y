%error-verbose
%locations
%{
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "mc.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
int yylex();
void yyerror(const char* fmt, ...);
%}

%union {
    char   type_char;
	int    type_int;
	float  type_float;
	char   type_id[32];
    void * node;
};

%token '=' ':' ';' ',' '(' ')' 
%token <type_char> CHAR
%token <type_float> FLOAT
%token <type_id> STRING ELE ID TYPE RELOP
%token <type_int> INT
%token IF ELSE WHILE FOR AND OR RETURN SWITCH CASE BREAK CONTINUE DEFAULT GR LS GE LE EQ NE
%type <node> program declarations var_init_list func_declaration 
%type <node> param_list compound_stmt var_declaration stmt_list stmt case_list 
%type <node> default for_body args_list exp

%left '='
%left OR
%left AND
%left GR LS GE LE EQ NE
%left '+' '-'
%left '*' '/'
%right UMINUS '!'

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%

program:
    declarations                                 {puts("reduce1");$$=$1;display($1,0);}
    ;

declarations:
    TYPE var_init_list ';'                       {puts("reduce2");$$=newdec(EXTERN_VAR,$1,$2,NULL);puts($1);}
    |func_declaration                            {puts("reduce3");$$=newdec(EXTERN_FUN,NULL,$1,NULL);}
    |TYPE var_init_list ';' declarations         {puts("reduce4");$$=newdec(EXTERN_VAR_LIST,$1,$2,$4);}
    |func_declaration declarations               {puts("reduce5");$$=newdec(EXTERN_FUN_LIST,NULL,$1,$2);}
    ;


var_init_list:
    ID                                           {puts("reduce6");$$=newvarinitlist(VAR_NO,$1,-1,NULL,NULL,NULL);}
    |ID '=' exp                                  {puts("reduce7");$$=newvarinitlist(VAR_INIT,$1,-1,NULL,$3,NULL);}
    |ID '[' INT ']'                              {puts("reduce8");$$=newvarinitlist(ARRAY_NO,$1,$3,NULL,NULL,NULL);}
    |ID '[' INT ']' '=' STRING                   {puts("reduce9");$$=newvarinitlist(ARRAY_INIT,$1,$3,$6,NULL,NULL);}
    |ID ',' var_init_list                        {puts("reduce10");$$=newvarinitlist(VAR_LIST,$1,-1,NULL,$3,NULL);}
    |ID '=' exp ',' var_init_list                {puts("reduce11");$$=newvarinitlist(VAR_INIT_LIST,$1,-1,NULL,$3,$5);}
    |ID '[' INT ']' ',' var_init_list            {puts("reduce12");$$=newvarinitlist(ARRAY_LIST,$1,$3,NULL,$6,NULL);}
    |ID '[' INT ']' '=' STRING ',' var_init_list {puts("reduce13");$$=newvarinitlist(ARRAY_INIT_LIST,$1,$3,$6,$8,NULL);}
    ;

func_declaration:                           
    TYPE ID '(' param_list ')' ';'               {puts("reduce14");$$=newfundec(FUN_DEC,$1,$2,$4,NULL);}
    |TYPE ID '(' param_list ')' compound_stmt    {puts("reduce15");$$=newfundec(FUN_DEC,$1,$2,$4,$6);}
    ;

param_list:                                      {puts("reduce16");$$=NULL;}
    |TYPE ID                                     {puts("reduce17");$$=newparam(PARAM,$1,$2,NULL);}
    |TYPE ID ',' param_list                      {puts("reduce18");$$=newparam(PARAM,$1,$2,$4);}
    ;

compound_stmt:                              
    '{' var_declaration  stmt_list '}'           {puts("reduce19");$$=newast(COMPSTMT,$2,$3);}
    ;

var_declaration:                                 {puts("reduce20");$$=NULL;}
    |TYPE var_init_list ';' var_declaration      {puts("reduce21");$$=newdec(INNER_VAR,$1,$2,$4);}
    ;

stmt_list:                                       {puts("reduce22");$$=NULL;}
    |stmt stmt_list                              {puts("reduce23");$$=newast(STMTLIST,$1,$2);}
    ;

stmt: exp ';'                                    {puts("reduce24");$$=$1;} 
    | compound_stmt                              {puts("reduce25");$$=$1;}
    | RETURN exp ';'                             {puts("reduce26");$$=newast(RETURN_NO,$2,NULL);}
    | BREAK ';'                                  {puts("reduce27");$$=newast(BREAK_NO,NULL,NULL);}
    | CONTINUE ';'                               {puts("reduce28");$$=newast(CONTINUE_NO,NULL,NULL);}
    | IF '(' exp ')' stmt %prec LOWER_THEN_ELSE  {puts("reduce29");$$=newcondition(IF_NO,$3,$5,NULL,NULL);}
    | IF '(' exp ')' stmt ELSE stmt              {puts("reduce30");$$=newcondition(IF_NO,$3,$5,$7,NULL);}
    | SWITCH '(' exp ')' '{' case_list  default '}' {puts("reduce31");$$=newcondition(SWITCH_NO,$3,$6,$7,NULL);}
    | WHILE '(' exp ')' stmt                     {puts("reduce32");$$=newast(WHILE_NO,$3,$5);}
    | FOR '(' exp ';' exp ';' exp ')' for_body   {puts("reduce33");$$=newcondition(FOR_NO,$3,$5,$7,$9);}
    ;

case_list:  
    CASE exp ':' stmt_list                      {puts("reduce34");$$=newcondition(CASE_NO,$2,$4,NULL,NULL);}
    | CASE exp ':' stmt_list case_list          {puts("reduce35");$$=newcondition(CASE_NO,$2,$4,$5,NULL);}
    ;
default:                                        {puts("reduce36");$$=NULL;}
    | DEFAULT ':' stmt_list                     {puts("reduce37");$$=newast(DEFAULT_NO,$3,NULL);}
    ;

for_body: ';'                                   {puts("reduce38");$$=NULL;}
    | stmt                                      {puts("reduce39");$$=$1;}
    ;

exp: exp '=' exp                                {puts("reduce40");$$=newast(ASSIGN,$1,$3);}
    | exp AND exp                               {puts("reduce41");$$=newast(AND_NO,$1,$3);}
    | exp OR exp                                {puts("reduce42");$$=newast(OR_NO,$1,$3);}
    | exp GR exp                                {puts("reduce43");$$=newast(GR_NO,$1,$3);}
    | exp LS exp                                {puts("reduce43");$$=newast(LS_NO,$1,$3);}    
    | exp GE exp                                {puts("reduce43");$$=newast(GE_NO,$1,$3);}
    | exp LE exp                                {puts("reduce43");$$=newast(LE_NO,$1,$3);}
    | exp EQ exp                                {puts("reduce43");$$=newast(EQ_NO,$1,$3);}
    | exp NE exp                                {puts("reduce43");$$=newast(NE_NO,$1,$3);}
    | exp '+' exp                               {puts("reduce44");$$=newast(ADD,$1,$3);}
    | exp '-' exp                               {puts("reduce45");$$=newast(MINUS,$1,$3);}
    | exp '*' exp                               {puts("reduce46");$$=newast(MUL,$1,$3);}
    | exp '/' exp                               {puts("reduce47");$$=newast(DIV,$1,$3);}
    | '(' exp ')'                               {puts("reduce48");$$=$2;}
    | '-' exp %prec UMINUS                      {puts("reduce49");$$=newast(UMINUS_NO,$2,NULL);}
    | '!' exp                                   {puts("reduce50");$$=newast(NOT,$2,NULL);}
    | ID '(' args_list ')'                      {puts("reduce51");$$=newfun(FUN_CALL,$1,$3);}
    | ID '[' INT ']'                            {puts("reduce52");$$=newele(ELE_NO,$1,$3);}
    | ID                                        {puts("reduce53");$$=newnum(ID_NO);strcpy(((struct num*)$$)->numval.string,$1);}
    | CHAR                                      {puts("reduce54");$$=newnum(CHAR_NO);((struct num*)$$)->numval.ch=$1;}
    | STRING                                    {puts("reduce55");$$=newnum(STRING_NO);strcpy(((struct num*)$$)->numval.string,$1);}          
    | INT                                       {puts("reduce56");$$=newnum(INT_NO);((struct num*)$$)->numval.intval=$1;printf(" %d\n",((ast*)$$)->nodetype);}
    | FLOAT                                     {puts("reduce57");$$=newnum(FLOAT_NO);((struct num*)$$)->numval.floatval=$1;}      
    ;

args_list: {$$=NULL}
    |exp                                        {puts("reduce58");$$=newast(ARGS,$1,NULL);}
    |exp ',' args_list                          {puts("reduce59");$$=newast(ARGS,$1,$3);}
    ;
%%

int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return 0;
	yylineno=1;
	yyparse();
	return 0;
	}

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}	
