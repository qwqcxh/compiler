#ifndef MC_H
#define MC_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 1000
enum {
    EXTERN_VAR=1,EXTERN_FUN,EXTERN_VAR_LIST,EXTERN_FUN_LIST,VAR_NO,
    VAR_INIT,ARRAY_NO,ARRAY_INIT,VAR_LIST,VAR_INIT_LIST,
    ARRAY_LIST,ARRAY_INIT_LIST,FUN_DEC,PARAM,COMPSTMT,INNER_VAR,
    STMTLIST,RETURN_NO,BREAK_NO,CONTINUE_NO,IF_NO,
    SWITCH_NO,WHILE_NO,FOR_NO,CASE_NO,DEFAULT_NO,
    ASSIGN,AND_NO,OR_NO,GR_NO,LS_NO,
    GE_NO,LE_NO,EQ_NO,NE_NO,ADD,
    MINUS,MUL,DIV,UMINUS_NO,NOT,
    FUN_CALL,ELE_NO,ID_NO,CHAR_NO,STRING_NO,
    INT_NO,FLOAT_NO,ARGS,CHAR_TYPE,INT_TYPE,
    FLOAT_TYPE,PROG
};

union val{
    char ch;
    int intval;
    double floatval;
    char string[30];
};

struct seman_info{
    int kind;//'V'->variable 'F'->function 'P'->parameter 'A' args
    int level;
    int addr;
    int size;
};

typedef struct ast{
    int nodetype;
    struct seman_info sem;
    struct ast*l;
    struct ast*r;
}ast;

typedef struct dec{
    int nodetype;
    struct seman_info sem;
    int type;
    ast* l,*r;
}dec;

typedef struct var_init{
    int nodetype;
    struct seman_info sem;
    char id[30];
    int idx;
    char string[30];
    ast *l;
    ast *r;
} var_init;

typedef struct fun{
    int nodetype;
    struct seman_info sem;
    ast *l,*r;
    int returntype;
    char id[30];
}fun;

typedef struct param{
    int nodetype;
    struct seman_info sem;
    ast *l;
    int datatypeid;
    char id[30];
}param;


typedef struct condition{
    int nodetype;
    struct seman_info sem;
    ast *a,*b,*c,*d;
}condition;

typedef struct ele{
    int nodetype;
    struct seman_info sem;
    char id[30];
    int idx;
}ele;

typedef struct num{
    struct seman_info sem;
    int nodetype;
    union val numval;
}num;

//symbol table
typedef struct symbol{
    char id[10];
    int kind;
    int level;
    int addr;
    int size;
} symbol;
extern symbol symtab[MAXLEN];
extern int symidx;

int lookup(char*name,int level);
int typetoint(char*type);
ast* newdec(int nodetyp,char*type,void*l,void*r);
ast* newvarinitlist(int nodetype,char*id,int idx,char*string,void*l,void*r);
ast* newfundec(int nodetype,char*returnid,char*id,void*l,void*r);
ast* newparam(int nodetype,char*datatypeid,char*id,void*l);
ast* newast(int nodetype,void* l,void* r);
ast* newcondition(int nodetype,void*a,void*b,void*c,void*d);
ast* newnum(int nodetype);
ast* newfun(int nodetype,char*id,void*l);
ast* newele(int nodetype,char*id,int idx);
void  display(void* node,int pos);
void semantic(ast* node);


#endif