#include "mc.h"

symbol symtab[MAXLEN];
int symidx = 0;
int head=0,cnt = 0;

int lookup(char*name){
    for(int i=symidx-1;i>=0;i--)
        if(strcmp(name,symtab[i].id)==0)//&&symtab[symidx].level==level)
            return i;
    return -1;
}
int findfunc(){
    for(int i=symidx-1;i>=0;i--){
        if(symtab[i].kind==FUN_TYPE)
            return i;
    }
    return -1;
}
int insertsym(char*name,struct seman_info sem){
    puts(name);
    strcpy(symtab[symidx].id,name);
    symtab[symidx].kind=sem.kind;
    symtab[symidx].level=sem.level;
    symtab[symidx].addr=sem.addr;
    symtab[symidx].size=sem.size;
    symtab[symidx].type=sem.stmt_type;
    symtab[symidx].paramnum=0;
    symidx++;
    printf("symidx now is %d\n",symidx);
    return symidx-1;
}
void printsymt(int level){
    symidx--;
    printf("符号名  类型     层级   偏移   大小   形参个数\n");
    while(symidx>=0&&symtab[symidx].level==level){
        printf("%-7s ",symtab[symidx].id);
        printtype(symtab[symidx].kind);
        printf("%-6d %-6d %-6d %-6d\n",symtab[symidx].level,
        symtab[symidx].addr,symtab[symidx].size,symtab[symidx].paramnum);
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
        case VAR_NO: // ID  凡是ID，需计算其kind，size（类型确定）,addr 与 level 确定变量是否是函数内部变量
            puts("1");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("错误！变量%s重复定义\n",((var_init*)node)->id);
            //node->addr 由父节点指定
            //node->kind 由父节点指定
            //node->level由父节点指定
            node->sem.size = getsize(node->sem.kind);
            insertsym(((var_init*)node)->id,node->sem);
            printf("leave 1 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case VAR_LIST: // ID ',' var_init_list
            puts("2");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("错误！变量%s重复定义\n",((var_init*)node)->id);
            //node->addr 由父节点指定
            //node->kind 由父节点指定
            //node->level由父节点指定
            node->sem.size = getsize(node->sem.kind);
            insertsym(((var_init*)node)->id,node->sem);
            node->l->sem.addr=node->sem.addr+node->sem.size;
            node->l->sem.kind=node->sem.kind;
            node->l->sem.level=node->sem.level;
            semantic(node->l);
            node->sem.size+=node->l->sem.size;
            printf("leave 2 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case VAR_INIT_LIST: //ID '=' exp ',' var_init_list   exp必须向上提供其类型
            puts("3");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("错误！变量%s重复定义\n",((var_init*)node)->id);
            //node->addr 由父节点指定
            //node->kind 由父节点指定
            //node->level由父节点指定
            node->sem.size=getsize(node->sem.kind);
            insertsym(((var_init*)node)->id,node->sem);
            //exp kind域 由子节点自下而上确定
            semantic(node->l); //对于exp，semantic将确定其kind
            if(node->sem.kind!=node->l->sem.kind) printf("错误！，变量%s的声明类型与初始化类型不一致。\n",((var_init*)node)->id);
            node->r->sem.kind=node->sem.kind;
            node->r->sem.level=node->sem.level;
            node->r->sem.addr=node->sem.addr+node->sem.size;
            semantic(node->r);
            node->sem.size+=node->r->sem.size;
            printf("leave 3 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case VAR_INIT: //ID '=' exp
            puts("4");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("错误！变量%s重复定义\n",((var_init*)node)->id);
            //node->addr 由父节点指定
            //node->kind 由父节点指定
            //node->level由父节点指定
            node->sem.size=getsize(node->sem.kind);
            insertsym(((var_init*)node)->id,node->sem);
            semantic(node->l);
            if(node->sem.kind!=node->l->sem.kind) printf("错误！，变量%s的声明类型与初始化类型不一致。\n",((var_init*)node)->id);
            printf("leave 4 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case ARRAY_NO: // ID '[' INT ']'
            puts("5");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("错误！数组名%s已经存在\n",((var_init*)node)->id);
            //node->addr 由父节点指定
            //node->kind 由父节点指定
            //node->level由父节点指定
            node->sem.size=getsize(node->sem.kind)*((var_init*)node)->idx;
            insertsym(((var_init*)node)->id,node->sem);
            printf("leave 5 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case ARRAY_LIST: // ID '[ INT ']' ',' var_init_list
            puts("6");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("错误！数组名%s已经存在\n",((var_init*)node)->id);
            //node->addr 由父节点指定
            //node->kind 由父节点指定
            //node->level由父节点指定
            node->sem.size=getsize(node->sem.kind)* ((var_init*)node)->idx;
            insertsym(((var_init*)node)->id,node->sem);
            node->l->sem.kind=node->sem.kind;
            node->l->sem.level=node->sem.level;
            node->l->sem.addr=node->sem.addr+node->sem.size;
            printf("leave 6 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case ARRAY_INIT: //ID '[' INT ']' = STRING  
            puts("7");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("错误！数组名%s已经存在\n",((var_init*)node)->id);
            //node->addr 由父节点指定
            //node->kind 由父节点指定
            //node->level由父节点指定
            node->sem.size=getsize(node->sem.kind)* ((var_init*)node)->idx;
            insertsym(((var_init*)node)->id,node->sem);
            printf("leave 7 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case ARRAY_INIT_LIST: // ID '[' INT ']' = STRING , var_init_list
            puts("8");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("错误！数组名%s已经存在\n",((var_init*)node)->id);
            //node->addr 由父节点指定
            //node->kind 由父节点指定
            //node->level由父节点指定
            node->sem.size=getsize(node->sem.kind)* ((var_init*)node)->idx;
            insertsym(((var_init*)node)->id,node->sem);
            node->l->sem.kind=node->sem.kind;
            node->l->sem.level=node->sem.level;
            node->l->sem.addr=node->sem.addr+node->sem.size;
            semantic(node->l);
            node->sem.size+=node->l->sem.size;
            printf("leave 8 node addr is %d size is %d \n",node->sem.addr,node->sem.size);   
            break;
        case FUN_DEC: //TYPE ID '(' param_list ')' ';' || comp_stmt  必须确定函数活动记录大小
            puts("9");
            idx=lookup(((fun*)node)->id);
            if(idx!=-1) printf("错误！,函数名%s已存在!\n",((fun*)node)->id);
            node->sem.stmt_type=((fun*)node)->returntype;  //函数返回类型主要确定函数调用是否合理
            //node->kind 已由父节点指定
            node->sem.addr=0;//函数无偏移地址
            idx = insertsym(((fun*)node)->id,node->sem);   //插入符号表
            node->sem.size=0; //此时初始化函数活动记录大小为0
            if(node->l){      //形参列表非空
                node->l->sem.level=node->sem.level+1;
                node->l->sem.addr=node->sem.addr;
                semantic(node->l);  //语义分析形参列表
                node->sem.size+=node->l->sem.size;
                symtab[idx].paramnum=node->l->sem.paranum; //记录形参个数
                symtab[idx].paratype=(int*)malloc(sizeof(int)*symtab[idx].paramnum);
                for(int i=0;i<symtab[idx].paramnum;i++)
                    symtab[idx].paratype[i]=symtab[idx+1+i].kind;
            }
            if(node->r){  //函数定义
                node->r->sem.level=node->sem.level+1;
                node->r->sem.addr=node->sem.addr+node->sem.size; //要加上形参变量的大小
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
                symtab[idx].size=node->sem.size;
            }
            printf("leave 9 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case PARAM: //TYPE ID ',' param_list || TYPE ID 
            puts("10");
            idx=lookup(((param*)node)->id);
            if(idx!=-1) printf("错误！, 函数形参重名!\n");
            //node->addr 已经由父节点设置
            //node->level已经由父节点设置
            node->sem.kind=(((param*)node)->datatypeid);
            node->sem.size=getsize(node->sem.kind);
            //设置形参个数
            node->sem.paranum=1; 
            insertsym(((param*)node)->id,node->sem);
            if(node->l){ //形参还未结束
                //node->kind 不需要
                node->l->sem.level=node->sem.level;
                node->l->sem.addr=node->sem.addr+node->sem.size;
                semantic(node->l);
                node->sem.size+=node->l->sem.size;
                node->sem.paranum+=node->l->sem.paranum;//设置形参个数
                //debug 
                printf("this paranum is %d \n",node->sem.paranum);
            }
            printf("leave 10 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case COMPSTMT: // '{' var_declaration  stmt_list '}' 
            puts("11");
            node->sem.size=0;
            if(node->l){
                if(node->sem.stmt_type==LOOP||node->sem.stmt_type==SW_STMT){
                    printf("错误！，循环或者SWITCH语句中不允许定义变量。\n");
                    break;
                }
                //此处暂时不需要node->kind，由其子节点自行设置
                node->l->sem.addr=node->sem.addr;
                node->l->sem.level=node->sem.level;
                semantic(node->l);
                node->sem.size+=node->l->sem.size;
            }
            if(node->r){
                node->r->sem.addr=node->sem.addr+node->sem.size;
                node->r->sem.level=node->sem.level;
                node->r->sem.stmt_type=UNKNOWN_TYPE;
                semantic(node->r); //完成语句类型的设置
            }
            printf("leave 11 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            printsymt(node->sem.level);
            break;
        case INNER_VAR: //TYPE var_init_list ';' var_declaration
            puts("12");
            node->sem.kind=((dec*)node)->type; //自行设置
            //遍历var_init_list
            node->l->sem.level=node->sem.level;
            node->l->sem.addr=node->sem.addr;
            node->l->sem.kind=node->sem.kind;
            semantic(node->l);
            node->sem.size=node->l->sem.size;
            if(node->r){ //声明多个变量
                //node->r->sem.kind由子节点自行设置
                node->r->sem.level=node->sem.level;
                node->r->sem.addr=node->sem.addr+node->sem.size;
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
            }
            printf("leave 12 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case STMTLIST: //stmt stmt_list 语句部分不再需要属性addr，level,kind了。只需要设置stmt_type
            puts("13");
            node->l->sem.stmt_type=node->sem.stmt_type;
            semantic(node->l);
            if(node->r){
                node->r->sem.stmt_type=node->sem.stmt_type;
                semantic(node->r);
            }
            printf("leave 13 node statement is %s \n",node->sem.stmt_type==LOOP?"循环":node->sem.stmt_type==SW_STMT?"switch语句":"未知");
            break;
        case RETURN_NO: //RETURN exp ';' 需要确定返回类型是否匹配
            puts("14");
            idx=findfunc();
            semantic(node->l);
            if(node->l->sem.kind!=symtab[idx].type)
                printf("错误！, 函数%s返回类型与函数定义类型不一致。\n",symtab[idx].id);
            printf("leave 13 node statement is %s \n",node->sem.stmt_type==LOOP?"循环":node->sem.stmt_type==SW_STMT?"switch语句":"未知");
            break;
        case BREAK_NO: //BREAK ';'
            puts("15");
            if(node->sem.stmt_type!=LOOP&&node->sem.stmt_type!=SW_STMT)
                printf("错误, BREAK只能使用在循环或者switch语句中!\n");
            printf("leave 15,a BREAK statement end!\n");
            break;
        case CONTINUE_NO: //CONTINUE ';'
            puts("16");
            if(node->sem.stmt_type!=LOOP)
                printf("错误, CONTINUE 只能使用在循环中!\n");
            printf("leave 16,a CONTINUE statement end!\n");
            break;
        case IF_NO: //IF '(' exp ')' stmt
            puts("17");
            node->r->sem.stmt_type=UNKNOWN_TYPE;
            semantic(node->r);
            printf("leave 17,a IF THEN statement end!\n");
            break;
        case SWITCH_NO: //SWITCH '(' exp ')' '{' case_list  default '}'
            puts("18");
            ((condition*)node)->b->sem.stmt_type=SW_STMT;
            semantic(((condition*)node)->b);
            ((condition*)node)->c->sem.stmt_type=SW_STMT;
            semantic(((condition*)node)->c);
            printf("leave 18,a SWITCH statement end!\n");
            break;
        case WHILE_NO: //WHILE '(' exp ')' stmt  
            puts("19");   
            ((condition*)node)->b->sem.stmt_type=LOOP;
            semantic(((condition*)node)->b);
            printf("leave 19,a WHILE statement end!\n");
            break;
        case FOR_NO: //FOR '(' exp ';' exp ';' exp ')' for_body 
            puts("20");
            if(((condition*)node)->d){
                ((condition*)node)->d->sem.stmt_type=LOOP;
                semantic(((condition*)node)->d);
            }
            printf("leave 20,a FOR statement end!\n");
            break;
        case CASE_NO: // CASE exp ':' stmt_list     
            puts("21");
            if(node->sem.stmt_type!=SW_STMT){
                printf("错误！，CASE语句只能在switch中使用！\n");
                break;
            }
            if(node->r){
                node->r->sem.stmt_type=node->sem.stmt_type;
                semantic(node->r);
            }   
            printf("leave 21,a CASE statement end!\n");
            break;
        case DEFAULT_NO:
            puts("22");
            if(node->sem.stmt_type!=SW_STMT)
                printf("错误！,DEFAULT只能在switch语句中使用！\n");
            printf("leave 22,a DEFAULT statement!\n");
            break;
       /***************以下是exp部分，主要确定表达式类型（kind）***************/
        case ASSIGN: //exp '=' exp
            if(node->l->nodetype!=ID_NO&&node->l->nodetype!=ELE_NO)
                printf("错误！, ASSIGN 语句需要是左值!\n");
            semantic(node->l);
            semantic(node->r);
            node->sem.kind=node->l->sem.kind;
            break;
        case AND_NO:
        case OR_NO:
        case GR_NO:
        case LS_NO:
        case GE_NO:
        case LE_NO:
        case EQ_NO:
        case NE_NO:
            semantic(node->l);
            semantic(node->r);
            node->sem.kind=INT_TYPE;//关系表达式类型全设置为INT
            break;
        case ADD:
        case MINUS:
        case MUL:
        case DIV:
            semantic(node->l);
            semantic(node->r);
            if(node->l->sem.kind==FLOAT_TYPE||node->r->sem.kind==FLOAT_TYPE)
                node->sem.kind=FLOAT_TYPE;
            else node->sem.kind=INT_TYPE;
            break;
        case UMINUS_NO:
            semantic(node->l);
            node->sem.kind=node->l->sem.kind;
            break;
        case NOT: 
            semantic(node->l);
            node->sem.kind=INT_TYPE;
            break;
        case CHAR_NO: node->sem.kind=CHAR_TYPE;break;
        case INT_NO:  node->sem.kind=INT_TYPE; break;
        case FLOAT_NO: node->sem.kind=FLOAT_TYPE;break;
        case STRING_NO: node->sem.kind=STR_CONST;break;
        case ID_NO:
            idx=lookup(((num*)node)->numval.string);
            if(idx==-1)
                printf("错误！,变量%s未声明！\n",((num*)node)->numval.string);    
            else node->sem.kind=symtab[idx].kind;
            break;
        case FUN_CALL: //ID '(' args_list ')'
            idx=lookup(((fun*)node)->id);
            if(idx==-1) printf("错误！,函数%s尚未声明或定义。\n",((fun*)node)->id);
            else{
                if(node->l==NULL&&symtab[idx].paramnum)
                    printf("错误！函数%s的实参不能为空。\n",((fun*)node)->id);
                else { head=idx;cnt=0;semantic(node->l);}
            }
            break;
        case ELE_NO: //ID '[' exp ']'
            semantic(node->l);
            if(node->l->sem.kind!=INT_TYPE)
                printf("错误！,数组%s的索引只能是整数。\n",((ele*)node)->id);
            else node->sem.kind=node->l->sem.kind;
            break;
        case ARGS: // exp || exp ',' args_list
            //debug
            printf("ARGS DEBUG, cnt now is %d\n",cnt);
            if(cnt>=symtab[head].paramnum) printf("错误！，数组%s的调用参数过多。\n",symtab[head].id);
            else {
                semantic(node->l);
                if(node->l->sem.kind!=symtab[head].paratype[cnt])
                    printf("错误！,函数%s的实参与形参不匹配。\n",symtab[head].id);
                else if(node->r){ cnt++;semantic(node->r);}
                else if(cnt!=symtab[head].paramnum-1) printf("错误！,函数%s的实参过少。\n",symtab[head].id);
            }
            break;
        default: printf("UNKNOWN NODE!!!");
            break;
    }
}