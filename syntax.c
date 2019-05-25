#include "mc.h"

int typetoint(char*type){
    if(strcmp(type,"char")==0)
        return CHAR_TYPE;
    else if(strcmp(type,"int")==0)
        return INT_TYPE;
    else return FLOAT_TYPE;
}
void printtype(int typenum){
    switch(typenum){
        case CHAR_TYPE:
            printf("char ");break;
        case INT_TYPE:
            printf("int ");break;
        case FLOAT_TYPE:
            printf("float ");break;
        default:printf("unknown type! %d",typenum);break;
    }
}
void* newdec(int nodetype,char*type,void *l,void *r){
    struct dec* dec=(struct dec*)malloc(sizeof(struct dec));
    dec->nodetype=nodetype;
    if(type) dec->type=typetoint(type);
    dec->l=l;
    dec->r=r;
    //debug
    //puts("newdec finished!");
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
    //puts("newvarinitlist finished!");
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
    //puts("newfundec finished!");
    return pfun;
}

void* newparam(int nodetype,char*datatypeid,char*id,void*l){
    struct param* pparam=(struct param*)malloc(sizeof(struct param));
    pparam->nodetype=nodetype;
    pparam->datatypeid=typetoint(datatypeid);
    if(id) strcpy(pparam->id,id);
    pparam->l=l;
    //
    //puts("newparam finished!");
    return pparam;
}

void* newast(int nodetype,void* l,void* r){
    struct ast*past=(struct ast*)malloc(sizeof(struct ast));
    past->nodetype=nodetype;
    past->l=l;
    past->r=r;
    //
    //puts("newast finished!");
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
    //puts("newcondition finished!");
    return pif;
}

void* newnum(int nodetype){
    struct num* pnum=(struct num*)malloc(sizeof(struct num));
    pnum->nodetype=nodetype;
    //
    //puts("newnum finished!");
    return pnum;
}

void* newfun(int nodetype,char*id,void*l){
    struct fun*pfun=(struct fun*)malloc(sizeof(struct fun));
    pfun->nodetype=nodetype;
    if(id)strcpy(pfun->id,id);
    pfun->l=l;
    //
    //puts("newfun finised!");
    return pfun;
}

void* newele(int nodetype,char*id,int idx){
    struct ele*pele=(struct ele*)malloc(sizeof(struct ele));
    pele->nodetype=nodetype;
    if(id)strcpy(pele->id,id);
    pele->idx=idx;
    //
    //puts("newele finished!");
    return pele;
}

void display(void* node,int pos){
    if(node==NULL) return ;
    switch(((struct ast*)node)->nodetype){
        case EXTERN_VAR_LIST:
        case EXTERN_VAR:
            //debug
            // puts("1");
            printf("%*c全局变量声明：\n%*c类型：",pos,' ',pos+3,' ');
            printtype(((struct dec*)node)->type);putchar('\n');
            printf("%*c变量列表：\n",pos+3,' ');
            display(((struct dec*)node)->l,pos+6);
            if(((struct dec*)node)->r) 
                display(((struct dec*)node)->r,pos);
            break;
        case EXTERN_FUN_LIST:
        case EXTERN_FUN:
            //debug
            // puts("2");
            printf("%*c函数声明或定义：\n",pos,' ');
            display(((struct dec*)node)->l,pos+3);
            if(((struct dec*)node)->r)
                display(((struct dec*)node)->r,pos);
            break;
        case VAR_LIST:
        case VAR_NO:
            // puts("3");
            printf("%*c%s\n",pos,' ',(((struct var_init*)node)->id));
            if(((struct var_init*)node)->l)
                display(((struct var_init*)node)->l,pos);
            break;
        case VAR_INIT_LIST:
        case VAR_INIT:
            //debug
            // puts("4");
            printf("%*c%s = \n",pos,' ',(((struct var_init*)node)->id));
            display(((struct var_init*)node)->l,pos+3);
            if(((struct var_init*)node)->r)
                display(((struct var_init*)node)->r,pos);
            break;
        case ARRAY_LIST:
        case ARRAY_NO:
            //debug
            // puts("5");
            printf("%*c%s [ %d ] \n",pos,' ',(((struct var_init*)node)->idx));
            if(((struct var_init*)node)->l)
                display(((struct var_init*)node)->l,pos);
            break;
        case ARRAY_INIT_LIST:
        case ARRAY_INIT:
            //debug
            // puts("6");
            printf("%*c%s [ %d ] = %s\n",pos,' ',(((var_init*)node)->idx),((var_init*)node)->string);
            if(((struct var_init*)node)->l)
                display(((struct var_init*)node)->l,pos);
            break;
        case FUN_DEC:
            //debug
            // puts("7");
            printf("%*c返回值 ",pos,' ');
            printtype(((struct fun*)node)->returntype);
            printf("函数名 %s 形参列表：\n",((struct fun*)node)->id);
            display(((struct fun*)node)->l,pos+3);
            if(((struct fun*)node)->r){
                printf("%*c函数体：\n",pos,' ');
                display(((struct fun*)node)->r,pos+3);  
            }
            break;
        case PARAM:
            //debug
            // puts("8");
            printf("%*c",pos,' ');
            printtype(((struct param*)node)->datatypeid);
            printf("%s\n",(((struct param*)node)->id));
            if(((struct param*)node)->l)
                display(((struct param*)node)->l,pos);
            break;
        case COMPSTMT:
            //debug
            // puts("9");
            display(((struct ast*)node)->l,pos);
            display(((struct ast*)node)->r,pos);
            break;
        case INNER_VAR:
            //debug
            // puts("10");
            printf("%*c",pos,' ');
            printtype(((struct dec*)node)->type);
            printf("变量列表：\n");
            display(((struct dec*)node)->l,pos+3);
            display(((struct dec*)node)->r,pos);
            break;
        case STMTLIST:
            //debug
            // puts("11");
            display(((struct ast*)node)->l,pos);
            display(((struct ast*)node)->r,pos);
            break;
        case RETURN_NO:
            //debug
            // puts("12");
            printf("%*cRETURN \n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            break;
        case BREAK_NO:
            //debug
            // puts("13");
            printf("%*cBREAK \n",pos,' ');
            break;
        case CONTINUE_NO:
            //debug
            // puts("14");
            printf("%*cCONTINUE\n",pos,' ');
            break;
        case IF_NO:
            //debug
            // puts("15");
            printf("%*cIF:\n",pos,' ');
            display(((struct condition*)node)->a,pos+3);
            printf("%*cTHEN:\n",pos,' ');
            display(((struct condition*)node)->b,pos+3);
            if(((struct condition*)node)->c){
                printf("%*cELSE:\n",pos,' ');
                display(((struct condition*)node)->c,pos+3);
            }
            break;
        case SWITCH_NO:
            //debug
            // puts("16");
            printf("%*cSWITCH:\n",pos,' ');
            display(((struct condition*)node)->a,pos+3);
            display(((struct condition*)node)->b,pos);
            display(((struct condition*)node)->c,pos);
            break;
        case WHILE_NO:
            //debug
            // puts("17");
            printf("%*cWHILE:\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            printf("%*cDO:\n",pos,' ');
            display(((struct ast*)node)->r,pos+3);
            break;
        case FOR_NO:
            //debug
            // puts("18");
            printf("%*cFOR:\n",pos,' ');
            display(((struct condition*)node)->a,pos+3);
            printf("%*cCONDITION:\n",pos,' ');
            display(((struct condition*)node)->b,pos+3);
            printf("%*cUPDATE:\n",pos,' ');
            display(((struct condition*)node)->c,pos+3);
            printf("%*cDO:\n",pos,' ');
            display(((struct condition*)node)->d,pos+3);
            break;
        case CASE_NO:
            //debug
            // puts("19");
            printf("%*cCASE:\n",pos,' ');
            display(((struct condition*)node)->a,pos+3);
            printf("%*cDO:\n",pos+3,' ');
            display(((struct condition*)node)->b,pos+6);
            if(((struct condition*)node)->c)
                display(((struct condition*)node)->c,pos);
            break;
        case DEFAULT_NO:
            //debug
            // puts("20");
            printf("%*cDEFAULT:\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            break;
        case ASSIGN:
            //debug
            // puts("21");
            printf("%*c赋值表达式=\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;
        case AND_NO:
            //debug
            // puts("22");
            printf("%*c与表达式&&\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;
        case OR_NO:
                //debug
            // puts("23");
            printf("%*c或表达式||\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break; 
        case GR_NO:
                    //debug
            // puts("24");
            printf("%*c关系表达式>\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;  
        case LS_NO:
                    //debug
            // puts("25");
            printf("%*c关系表达式<\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;
        case GE_NO:
                    //debug
            // puts("26");
            printf("%*c关系表达式>=\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;
        case LE_NO:
                    //debug
            // puts("27");
            printf("%*c关系表达式<=\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;
        case EQ_NO:
                    //debug
            // puts("28");
            printf("%*c关系表达式==\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;
        case NE_NO:
                    //debug
            // puts("29");
            printf("%*c关系表达式!=\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;
        case ADD:
                    //debug
            // puts("30");
            printf("%*c算术表达式+\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;
        case MINUS:
                    //debug
            // puts("31");
            printf("%*c算术表达式-\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;
        case MUL:
                    //debug
            // puts("32");
            printf("%*c算数表达式*\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;
        case DIV:
                    //debug
            // puts("33");
            printf("%*c算术表达式/\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            display(((struct ast*)node)->r,pos+3);
            break;
        case UMINUS_NO:
                    //debug
            // puts("34");
            printf("%*c单目-\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            break;
        case NOT:
                    //debug
            // puts("35");
            printf("%*c关系表达式!\n",pos,' ');
            display(((struct ast*)node)->l,pos+3);
            break;
        case FUN_CALL:
                    //debug
            // puts("36");
            printf("%*c函数名 ",pos,' ');
            printf("%s",((struct fun*)node)->id);
            printf("\n%*c实际参数：\n",pos,' ');
            display(((struct  fun*)node)->l,pos+3);
            break;
        case ELE_NO:
                    //debug
            // puts("37");
            printf("%*c%s %d\n",pos,' ',(((ele*)node)->id),(((ele*)node)->idx));
            break;
        case ID_NO:
                    //debug
            // puts("38");
            printf("%*c%s\n",pos,' ',(((num*)node)->numval.string));
            break;
        case CHAR_NO:
                    //debug
            // puts("39");
            printf("%*c字符常量%c\n",pos,' ',(((num*)node)->numval.ch));
            break;
        case STRING_NO:
                    //debug
            // puts("40");
            printf("%*c字符串常量%s\n",pos,' ',(((num*)node)->numval.string));
            break;
        case INT_NO:
                    //debug
            // puts("41");
            printf("%*c整数常量%d\n",pos,' ',(((num*)node)->numval.intval));
            break;
        case FLOAT_NO:
                    //debug
            // puts("42");
            printf("%*c浮点常量%f\n",pos,' ',(((num*)node)->numval.floatval));
            break;
        case ARGS:
                    //debug
            // puts("43");
            display(((ast*)node)->l,pos);
            if(((ast*)node)->r)
                display(((ast*)node)->r,pos);
            break;
        default:
                    //debug
            // puts("44");
            printf("%d syntex error!!!",(((ast*)node)->nodetype));
    }
}