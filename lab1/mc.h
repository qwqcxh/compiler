#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    FLOAT_TYPE
};

union val{
    char ch;
    int intval;
    double floatval;
    char string[30];
};
typedef struct dec{
    int nodetype;
    int type;
    void* l,*r;
}dec;

typedef struct var_init{
    int nodetype;
    char id[30];
    int idx;
    char string[30];
    void *l;
    void *r;
} var_init;

typedef struct fun{
    int nodetype;
    int returntype;
    char id[30];
    void *l,*r;
}fun;

typedef struct param{
    int nodetype;
    int datatypeid;
    char id[30];
    void *l;
}param;

typedef struct ast{
    int nodetype;
    void*l;
    void*r;
}ast;

typedef struct condition{
    int nodetype;
    void *a,*b,*c,*d;
}condition;

typedef struct ele{
    int nodetype;
    char id[30];
    int idx;
}ele;

typedef struct num{
    int nodetype;
    union val numval;
}num;

int typetoint(char*type);
void* newdec(int nodetyp,char*type,void*l,void*r);
void* newvarinitlist(int nodetype,char*id,int idx,char*string,void*l,void*r);
void* newfundec(int nodetype,char*returnid,char*id,void*l,void*r);
void* newparam(int nodetype,char*datatypeid,char*id,void*l);
void* newast(int nodetype,void* l,void* r);
void* newcondition(int nodetype,void*a,void*b,void*c,void*d);
void* newnum(int nodetype);
void* newfun(int nodetype,char*id,void*l);
void* newele(int nodetype,char*id,int idx);
void  display(void* node,int pos);