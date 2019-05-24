#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    EXTERN_VAR,EXTERN_FUN,EXTERN_VAR_LIST,EXTERN_FUN_LIST,
    VAR_NO,VAR_INIT,ARRAY_NO,ARRAY_INIT,VAR_LIST,VAR_INIT_LIST,ARRAY_LIST,ARRAY_INIT_LIST,
    FUN_DEC,PARAM,COMPSTMT,INNER_VAR,STMTLIST,RETURN_NO,BREAK_NO,CONTINUE_NO,IF_NO,
    SWITCH_NO,WHILE_NO,FOR_NO,CASE_NO,DEFAULT_NO,ASSIGN,AND_NO,OR_NO,RELOP_NO,ADD,MINUS,MUL,DIV,
    UMINUS_NO,NOT,FUN_CALL,ELE_NO,ID_NO,CHAR_NO,STRING_NO,INT_NO,FLOAT_NO,ARGS,
    CHAR_TYPE,INT_TYPE,FLOAT_TYPE
};

union val{
    char ch;
    int intval;
    double floatval;
    char string[30];
};
struct dec{
    int nodetype;
    int type;
    void* l,*r;
};

struct var_init{
    int nodetype;
    char id[30];
    int idx;
    char string[30];
    void *l;
    void *r;
};

struct fun{
    int nodetype;
    int returntype;
    char id[30];
    void *l,*r;
};

struct param{
    int nodetype;
    int datatypeid;
    char id[30];
    void *l;
};

struct ast{
    int nodetype;
    void*l;
    void*r;
};

struct condition{
    int nodetype;
    void *a,*b,*c,*d;
};

struct ele{
    int nodetype;
    char id[30];
    int idx;
};

struct num{
    int nodetype;
    union val numval;
};

int typetoint(char*type){
    if(strcmp(type,"char")==0)
        return CHAR_TYPE;
    else if(strcmp(type,"int")==0)
        return INT_TYPE;
    else return FLOAT_TYPE;
}
void* newdec(int nodetype,char*type,void *l,void *r){
    struct dec* dec=(struct dec*)malloc(sizeof(struct dec));
    dec->nodetype=nodetype;
    if(type) dec->type=typetoint(type);
    dec->l=l;
    dec->r=r;
    //debug
    puts("newdec finished!");
    return dec;
}

void* newvarinitlist(int nodetype,char*id,int idx,char*string,void*l,void*r){
    struct var_init* pvarinit=(struct var_init*)malloc(sizeof(struct var_init));
    pvarinit->nodetype=nodetype;
    //debug
    if(id)strcpy(pvarinit->id,id);
    pvarinit->idx=idx;
    if(string) strcpy(pvarinit->string,string);
    pvarinit->l=l;
    pvarinit->r=r;
    //
    puts("newvarinitlist finished!");
    return pvarinit;
}

void* newfundec(int nodetype,char*returnid,char*id,void*l,void*r){
    struct fun* pfun=(struct fun*)malloc(sizeof(struct fun));
    pfun->nodetype=nodetype;
    pfun->returntype=typetoint(returnid);
    if(id)strcpy(pfun->id,id);
    pfun->l=l;
    pfun->r=r;
    //
    puts("newfundec finished!");
    return pfun;
}

void* newparam(int nodetype,char*datatypeid,char*id,void*l){
    struct param* pparam=(struct param*)malloc(sizeof(struct param));
    pparam->nodetype=nodetype;
    pparam->datatypeid=typetoint(datatypeid);
    if(id) strcpy(pparam->id,id);
    pparam->l=l;
    //
    puts("newparam finished!");
    return pparam;
}

void* newast(int nodetype,void* l,void* r){
    struct ast*past=(struct ast*)malloc(sizeof(struct ast));
    past->nodetype=nodetype;
    past->l=l;
    past->r=r;
    //
    puts("newast finished!");
    return past;
}

void* newcondition(int nodetype,void*a,void*b,void*c,void*d){
    struct condition* pif=(struct condition*)malloc(sizeof(struct condition));
    pif->nodetype=nodetype;
    pif->a=a;
    pif->b=b;
    pif->c=c;
    pif->d=d;
    //
    puts("newcondition finished!");
    return pif;
}

void* newnum(int nodetype){
    struct num* pnum=(struct num*)malloc(sizeof(struct num));
    pnum->nodetype=nodetype;
    //
    puts("newnum finished!");
    return pnum;
}

void* newfun(int nodetype,char*id,void*l){
    struct fun*pfun=(struct fun*)malloc(sizeof(struct fun));
    pfun->nodetype=nodetype;
    if(id)strcpy(pfun->id,id);
    pfun->l=l;
    //
    puts("newfun finised!");
    return pfun;
}

void* newele(int nodetype,char*id,int idx){
    struct ele*pele=(struct ele*)malloc(sizeof(struct ele));
    pele->nodetype=nodetype;
    if(id)strcpy(pele->id,id);
    pele->idx=idx;
    //
    puts("newele finished!");
    return pele;
}