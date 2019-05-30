#include "mc.h"

symbol symtab[MAXLEN];
int symidx = 0;

int lookup(char*name,int level){
    for(int i=0;i<symidx;i++)
        if(strcmp(name,symtab[symidx].id)==0&&symtab[symidx].level==level)
            return i;
    return -1;
}
int findfunc(int level){
    printf("FUN_TYPE is %d\n",FUN_TYPE);
    for(int i=symidx-1;i>=0;i--){
        printf("symtab[%d].kind is =%d  and level is %d \n",i,symtab[i].kind,symtab[i].level);
        if(symtab[i].kind==FUN_TYPE)
            return i;
    }
    return -1;
}
int findvar(char*name){
    for(int i=symidx-1;i>=0;i--)
        if(strcmp(name,symtab[symidx].id)==0)
            return i;
    return -1;
}
void insertsym(char*name,struct seman_info sem){
    puts(name);
    strcpy(symtab[symidx].id,name);
    symtab[symidx].kind=sem.kind;
    symtab[symidx].level=sem.level;
    symtab[symidx].addr=sem.addr;
    symtab[symidx].size=sem.size;
    symtab[symidx].type=sem.stmt_type;
    symidx++;
    printf("symidx now is %d\n",symidx);
}
void printsymt(int level){
    symidx--;
    printf("符号名  类型    层级    偏移    大小\n");
    while(symidx>=0&&symtab[symidx].level==level){
        printf("%-7s ",symtab[symidx].id);
        printtype(symtab[symidx].kind);
        printf("%-6d %-6d %-6d\n",symtab[symidx].level,
        symtab[symidx].addr,symtab[symidx].size);
        symidx--;
    }
    symidx++;
}
int getsize(int kind){
    if(kind==CHAR_TYPE)
        return 1;
    else if(kind==INT_TYPE)
        return 4;
    else return 8;
}

void semantic(ast* node){
    if(node==NULL) return ;
    int idx;
    switch(node->nodetype){
        case PROG: //declarations
            puts("-3");
            node->sem.addr=0;
            node->sem.level=0;
            node->sem.size=0;
            node->l->sem.addr=0;
            node->l->sem.level=0;
            semantic(node->l);
            node->sem.size+=node->l->sem.size; //全局变量需要的空间
            printsymt(node->sem.level);
            break;
        case EXTERN_VAR://TYPE var_init_list ';'
        case EXTERN_VAR_LIST://TYPE var_init_list ';' declarations;
            puts("-2");
            node->l->sem.kind=((dec*)node)->type;//确定本节点的类型
            node->l->sem.level=0;
            node->l->sem.addr=node->sem.addr;
            semantic(node->l); //计算一个声明
            node->sem.size=node->l->sem.size;//更新大小
            if((node)->r){//表明是EXTERN_VAR_LIST
                node->r->sem.level=0;
                node->r->sem.addr=node->sem.addr+node->sem.size;
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
            }
            printf("leave -2 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case EXTERN_FUN: //fun_declaration
            puts("-1");
            node->l->sem.kind=FUN_TYPE;
            node->l->sem.level=0;
            node->l->sem.addr=node->sem.addr;
            semantic(node->l);
            node->sem.size=node->l->sem.size;
            printf("leave -1 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case EXTERN_FUN_LIST: //fun_declaration declaration
            puts("0");
            node->l->sem.kind=FUN_TYPE;
            node->l->sem.level=0;
            node->l->sem.addr=node->sem.addr;
            semantic(node->l);
            node->sem.size=0;//函数的size默认为0
            node->r->sem.addr=node->sem.addr;//设置declaration 的偏移
            node->r->sem.level=0;
            //kind 此时未知
            semantic(node->r);
            node->sem.size=node->r->sem.size;
            printf("leave 0 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case VAR_NO: // ID  凡是ID，需计算其kind，size（类型确定）
            puts("1");
            idx=lookup(((var_init*)node)->id,node->sem.level);
            if(idx!=-1)
                printf("error,variable definition twice!\n");
            insertsym(((var_init*)node)->id,node->sem);
            node->sem.size=0;
            node->sem.size+=getsize(node->sem.kind);
            printtype(node->sem.kind);
            printf("leave 1 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case VAR_LIST: // ID ',' var_init_list
            puts("2");
            idx=lookup(((var_init*)node)->id,node->sem.level);
            if(idx!=-1)
                printf("error,variable definition twice!\n");
            insertsym(((var_init*)node)->id,node->sem);
            node->sem.size=0;
            node->sem.size+=getsize(node->sem.kind);
            node->l->sem.addr=node->sem.addr+node->sem.size;
            node->l->sem.kind=node->sem.kind;
            node->l->sem.level=node->sem.level;
            semantic(node->l);
            node->sem.size+=node->l->sem.size;
            printf("leave 2 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case VAR_INIT_LIST: //ID '=' exp ',' var_init_list
            puts("3");
            idx=lookup(((var_init*)node)->id,node->sem.level);
            if(idx!=-1){
                printf("error,variable definition twice!\n");
            }
            insertsym(((var_init*)node)->id,node->sem);
            node->sem.size=0;
            node->sem.size+=getsize(node->sem.kind);
            node->l->sem.level=node->sem.level;
            node->l->sem.addr=node->sem.addr+node->sem.size;
            semantic(node->l);
            node->sem.level=node->l->sem.level; //此处的level保存的是value
            if(node->sem.kind!=node->l->sem.kind){
                printf("errro,declared variable type mismatch!\n");
            }
            node->r->sem.level=node->sem.level;
            node->r->sem.addr=node->sem.addr+node->sem.size;
            node->r->sem.kind=node->sem.kind;
            semantic(node->r);
            node->sem.size+=node->r->sem.size;
            printf("leave 3 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case VAR_INIT: //ID '=' exp
            //debug
            puts("4");
            idx=lookup(((var_init*)node)->id,node->sem.level);
            if(idx!=-1){
                printf("error,%s definition twice!\n",((var_init*)node)->id);
            }
            insertsym(((var_init*)node)->id,node->sem);
            node->sem.size=0;
            node->sem.size+=getsize(node->sem.kind);
            node->l->sem.level=node->sem.level;
            node->l->sem.addr=node->sem.addr+node->sem.size;
            semantic(node->l);
            node->sem.level=node->l->sem.level; //此处的level保存的是value
            if(node->sem.kind!=node->l->sem.kind){
                printf("errro,declared variable type mismatch!\n");
            }
            printf("leave 4 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case ARRAY_NO: // ID '[' INT ']'
            puts("5");
            idx=lookup(((var_init*)node)->id,node->sem.level);
            if(idx!=-1)
                printf("error,variable definition twice!\n");
            insertsym(((var_init*)node)->id,node->sem);
            node->sem.level = ((var_init*)node)->idx;//level 保存数组元素个数
            node->sem.size=0;
            node->sem.size+=getsize(node->sem.kind)*node->sem.level;
            printf("leave 5 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case ARRAY_LIST: // ID '[ INT ']' ',' var_init_list
            puts("6");
            idx=lookup(((var_init*)node)->id,node->sem.level);
            if(idx!=-1)
                printf("error,variable definition twice!\n");
            insertsym(((var_init*)node)->id,node->sem);
            node->sem.level = ((var_init*)node)->idx;//level 保存数组元素个数
            node->sem.size=0;
            node->sem.size+=getsize(node->sem.kind)*node->sem.level;
            node->l->sem.kind=node->sem.kind;
            node->l->sem.level=node->sem.level;
            node->l->sem.addr=node->sem.addr+node->sem.size;
            printf("leave 6 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case ARRAY_INIT: //ID '[' INT ']' = STRING  
            puts("7");
            idx=lookup(((var_init*)node)->id,node->sem.level);
            if(idx!=-1)
                printf("error,variable definition twice!\n");
            insertsym(((var_init*)node)->id,node->sem);
            node->sem.level = ((var_init*)node)->idx;//level 保存数组元素个数
            node->sem.size=0;
            node->sem.size += getsize(node->sem.kind)*(node->sem.level);
            printf("leave 7 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case ARRAY_INIT_LIST: // ID '[' INT ']' = STRING , var_init_list
            puts("8");
            idx=lookup(((var_init*)node)->id,node->sem.level);
            if(idx!=-1)
                printf("error,variable definition twice!\n");
            insertsym(((var_init*)node)->id,node->sem);
            node->sem.level = ((var_init*)node)->idx;//level 保存数组元素个数
            node->sem.size=0;
            node->sem.size+=getsize(node->sem.kind)*node->sem.level;
            node->l->sem.kind=node->sem.kind;
            node->l->sem.level=node->sem.level;
            node->l->sem.addr=node->sem.addr+node->sem.size;
            semantic(node->l);
            node->sem.size+=node->l->sem.size;
            printf("leave 8 node addr is %d size is %d \n",node->sem.addr,node->sem.size);   
            break;
        case FUN_DEC: //TYPE ID '(' param_list ')' ';' || comp_stmt
            puts("9");
            idx=lookup(((fun*)node)->id,node->sem.level);
            if(idx!=-1)
                printf("error, function can't have the same name!\n");
            node->sem.stmt_type=((fun*)node)->returntype;
            insertsym(((fun*)node)->id,node->sem);
            node->sem.kind=((fun*)node)->returntype;
            node->sem.size=0;
            if(node->l){
                node->l->sem.level=node->sem.level+1;
                node->l->sem.addr=node->sem.addr;
                semantic(node->l);
                node->sem.size+=node->l->sem.size;
            }
            if(node->r){
                node->r->sem.level=node->sem.level+1;
                // node->r->sem.addr=node->sem.addr+node->sem.size;
                node->r->sem.addr=0;//函数内部
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
            }
            printf("leave 9 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case PARAM: //TYPE ID ',' param_list || TYPE ID 
            puts("10");
            idx=lookup(((param*)node)->id,node->sem.level);
            if(idx!=-1)
                printf("error, function parameters can't have the same name!\n");
            node->sem.kind=(((param*)node)->datatypeid);
            node->sem.size=0;
            insertsym(((param*)node)->id,node->sem);
            node->sem.size+=getsize(node->sem.kind);
            if(node->l){
                node->l->sem.level=node->sem.level;
                node->l->sem.addr=node->sem.addr+node->sem.size;
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
            }
            printf("leave 10 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case COMPSTMT: // '{' var_declaration  stmt_list '}' 
            puts("11");
            node->sem.size=0;
            if(node->l){
                node->l->sem.addr=node->sem.addr;
                node->l->sem.level=node->sem.level;
                semantic(node->l);
                node->sem.size+=node->l->sem.size;
            }
            if(node->r){
                node->r->sem.addr=node->sem.addr+node->sem.size;
                node->r->sem.level=node->sem.level;
                semantic(node->r);
                // node->sem.size+=node->r->sem.size;
            }
            //debug
            printf("leave 11 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            printsymt(node->sem.level);
            break;
        case INNER_VAR: //TYPE var_init_list ';' var_declaration
            puts("12");
            node->sem.kind=((dec*)node)->type;
            node->l->sem.level=node->sem.level;
            node->l->sem.addr=node->sem.addr;
            node->l->sem.kind=node->sem.kind;
            semantic(node->l);
            node->sem.size=0;
            node->sem.size+=node->l->sem.size;
            if(node->r){
                node->r->sem.level=node->sem.level;
                node->r->sem.addr=node->sem.addr+node->sem.size;
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
            }
            printf("leave 12 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case STMTLIST: //stmt stmt_list
            puts("13");
            node->l->sem.addr=node->sem.addr;
            node->l->sem.level=node->sem.level;
            semantic(node->l);
            node->sem.size=0;
            node->sem.size+=node->l->sem.size;
            if(node->r){
                node->r->sem.addr=node->sem.addr+node->sem.size;
                node->r->sem.level=node->sem.level;
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
            }
            printf("leave 13 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case RETURN_NO:
            puts("14");
            idx=findfunc(node->sem.level);
            if(idx==-1) printf("error, RETURN should be used in function!\n");
            semantic(node->l);
            if(node->l->sem.kind!=symtab[idx].type)
                printf("error, RETURN type mismatch function type");
            break;
        case BREAK_NO:
            puts("15");
            if(node->sem.stmt_type!=LOOP&&node->sem.stmt_type!=SW_STMT)
                printf("error, BREAK should be used in loop or switch statement!\n");
            break;
        case CONTINUE_NO:
            puts("16");
            if(node->sem.stmt_type!=LOOP)
                printf("error, CONTINUE should be used in loop!\n");
            break;
        case IF_NO: //IF '(' exp ')' stmt
            puts("17");
            node->r->sem.addr=node->sem.addr; //stmt 有可能声明变量
            semantic(node->r);
            node->sem.size=node->r->sem.size;
            break;
        case SWITCH_NO: //SWITCH '(' exp ')' '{' case_list  default '}'
            puts("18");
            ((condition*)node)->a->sem.stmt_type=SW_STMT;
            semantic(((condition*)node)->a);
            ((condition*)node)->b->sem.stmt_type=SW_STMT;
            semantic(((condition*)node)->b);
            ((condition*)node)->c->sem.stmt_type=SW_STMT;
            semantic(((condition*)node)->c);
            node->sem.stmt_type=SW_STMT;
            break;
        case WHILE_NO: //WHILE '(' exp ')' stmt     
            ((condition*)node)->b->sem.stmt_type=LOOP;
            semantic(((condition*)node)->b);
            break;
        case FOR_NO: //FOR '(' exp ';' exp ';' exp ')' for_body 
            ((condition*)node)->d->sem.stmt_type=LOOP;
            semantic(((condition*)node)->d);
            break;
        case CASE_NO: // CASE exp ':' stmt_list        
            ((condition*)node)->b->sem.stmt_type=LOOP;
            semantic(((condition*)node)->b);
            break;
        case DEFAULT_NO:
            if(node->sem.stmt_type!=SW_STMT)
                printf("error,DEFAULT can only be used in switch statement\n");
            break;

        case ASSIGN:
            if(node->l->nodetype==CHAR_NO||node->l->nodetype==STRING_NO||
               node->l->nodetype==INT_NO||node->l->nodetype==FLOAT_NO)
                printf("error, ASSIGN statement shouldn't be a constant!\n");
        case AND_NO:
        case OR_NO:
        case GR_NO:
        case LS_NO:
        case GE_NO:
        case LE_NO:
        case EQ_NO:
        case NE_NO:
        case ADD:
        case MINUS:
        case MUL:
        case DIV:
            
            semantic(node->l);
            semantic(node->r);
            node->sem.kind=INT_TYPE;
            break;
        case UMINUS_NO:
        case NOT: 
            semantic(node->l);
            node->sem.kind=INT_TYPE;
            break;
        case CHAR_NO: node->sem.kind=CHAR_TYPE;break;
        case INT_NO:  node->sem.kind=INT_TYPE; break;
        case FLOAT_NO: node->sem.kind=FLOAT_TYPE;break;
        case STRING_NO: node->sem.kind=STR_CONST;break;
        case ID_NO:
            if(findvar(((num*)node)->numval.string)==-1)
                printf("error,%s is undefined!\n",((num*)node)->numval.string);    
            break;
        case FUN_CALL:
            break;
        case ELE_NO:
            break;
        case ARGS:
            break;
        default: printf("unknown node");
            break;
    }
}