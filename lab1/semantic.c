#include "mc.h"

symbol symtab[MAXLEN];
int symidx = 0;
// int head=0,cnt = 0;

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
    symtab[symidx].paramnum= 0;
    symidx++;
    printf("symidx now is %d\n",symidx);
    return symidx-1;
}
void initsymtab(){
    struct seman_info sem;
    memset(&sem,0,sizeof(struct seman_info));
    sem.kind=FUN_TYPE;
    int idx = insertsym("read",sem);
    symtab[idx].paratype = (int*)malloc(sizeof(int));
    symtab[idx].paratype[0]=INT_TYPE;
    symtab[idx].paramnum = 1;
    idx = insertsym("write",sem);
    symtab[idx].paratype = (int*)malloc(sizeof(int));
    symtab[idx].paratype[0]=INT_TYPE;
    symtab[idx].paramnum = 1;
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
void mergecode(code*h,code*t){
    code* pcode=h;
    while(h&&h->next) h=h->next;
    if(h) h->next=t;
    else h=t;
}
int newlabel(){
    static int num=1;
    return num++;
}
void semantic(ast* node){
    if(node==NULL) return ;
    int idx,head,judge_label_num,end_label_num,update_label_num;
    code* phead,*ptail,*plabel;
    ast* pnode;
    switch(node->nodetype){
        case PROG: //declarations
            puts("-3");
            node->sem.addr=0;
            node->sem.level=0;
            node->sem.size=0;
            node->l->pcode=NULL; //initail pcode
            node->l->sem.addr=0;
            node->l->sem.level=0;
            semantic(node->l);
            node->sem.size+=node->l->sem.size; //全局变量需要的空间
            node->pcode=node->l->pcode;//finish pcode
            printsymt(node->sem.level);
            break;
        case EXTERN_VAR://TYPE var_init_list ';'
        case EXTERN_VAR_LIST://TYPE var_init_list ';' declarations;
            puts("-2");
            node->l->pcode=NULL;//initial pcode
            node->l->sem.kind=((dec*)node)->type;//确定本节点的类型
            node->l->sem.level=0;
            node->l->sem.addr=node->sem.addr;
            semantic(node->l); //计算一个声明
            node->sem.size=node->l->sem.size;//更新大小
            if((node)->r){//表明是EXTERN_VAR_LIST
                node->r->pcode = NULL;//initial pcode
                node->r->sem.level=0;
                node->r->sem.addr=node->sem.addr+node->sem.size;
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
            }
            //基于方便，暂时未实现全局变量的中间代码生成。
            printf("leave -2 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case EXTERN_FUN: //fun_declaration
            puts("-1");
            node->l->pcode=NULL; //initialize pcode
            node->l->sem.kind=FUN_TYPE;
            node->l->sem.level=0;
            node->l->sem.addr=node->sem.addr;
            semantic(node->l);
            node->sem.size=node->l->sem.size;
            node->pcode=node->l->pcode;//finish pcode
            printf("leave -1 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case EXTERN_FUN_LIST: //fun_declaration declaration
            puts("0");
            node->l->pcode=NULL;//initial pcode
            node->l->sem.kind=FUN_TYPE;
            node->l->sem.level=0;
            node->l->sem.addr=node->sem.addr;
            semantic(node->l);
            node->sem.size=0;//函数的size默认为0
            node->pcode=node->l->pcode; //update node->pcode
            node->r->pcode=NULL; //initial declaration pcode
            node->r->sem.addr=node->sem.addr;//设置declaration 的偏移
            node->r->sem.level=0;
            //kind 此时未知
            semantic(node->r);
            node->sem.size=node->r->sem.size;
            mergecode(node->pcode,node->r->pcode); //合并链表
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
            //变量声明，无需对pcode进行操作
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
            node->l->pcode=NULL; 
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
            node->r->pcode=NULL;
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
            node->l->pcode=NULL;
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
            node->l->pcode=NULL;
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
            node->l->pcode=NULL;
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
                /**********函数体code的生成************/
                node->pcode=(code*)malloc(sizeof(code));
                memset(node->pcode,0,sizeof(code));
                node->pcode->op=LABEL;
                sprintf(node->pcode->name,"%s:\n",((fun*)node)->id);
                node->r->pcode = NULL;
                node->r->sem.level=node->sem.level+1;
                node->r->sem.addr=node->sem.addr+node->sem.size; //要加上形参变量的大小
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
                memcpy(&node->pcode->var,&node->sem,sizeof(struct seman_info)); /*复制函数的信息*/
                mergecode(node->pcode,node->r->pcode); //完成pcode的拼接
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
                // printf("this paranum is %d \n",node->sem.paranum);
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
                node->r->pcode=NULL; //initial statement list
                node->r->sem.addr=node->sem.addr+node->sem.size;
                node->r->sem.level=node->sem.level;
                node->r->sem.stmt_type=node->sem.stmt_type;
                //继承lable_num
                node->r->sem.end_num = node->sem.end_num;
                node->r->sem.judge_num = node->sem.judge_num;
                node->r->sem.update_num = node->sem.update_num;
                semantic(node->r); //完成语句类型的设置
                node->pcode=node->r->pcode; //生成语句列表
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
            //首先给stmt都起一个label.
            // node->pcode = (code*)malloc(sizeof(code));
            // memset(node->pcode,0,sizeof(code));
            // node->pcode->op=LABEL;
            // sprintf(node->pcode->name,"LABEL %d",newlabel());
            node->l->pcode=NULL;
            node->l->sem.stmt_type=node->sem.stmt_type;
            node->l->sem.end_num = node->sem.end_num;
            node->l->sem.update_num = node->sem.update_num;
            node->l->sem.judge_num = node->sem.judge_num;
            semantic(node->l);
            node->pcode=node->l->pcode;
            // mergecode(node->pcode,node->l->pcode);
            if(node->r){
                node->r->pcode=NULL;
                node->r->sem.stmt_type=node->sem.stmt_type;
                node->r->sem.judge_num = node->sem.judge_num;
                node->r->sem.end_num = node->sem.end_num;
                node->r->sem.update_num = node->sem.update_num;
                semantic(node->r);
                mergecode(node->pcode,node->r->pcode);
            }
            printf("leave 13 node statement is %s \n",node->sem.stmt_type==LOOP?"循环":node->sem.stmt_type==SW_STMT?"switch语句":"未知");
            break;
        case RETURN_NO: //RETURN exp ';' 需要确定返回类型是否匹配
            puts("14");
            idx=findfunc();
            if(idx==-1){
                printf("错误！，RETURN 语句只能在函数体中使用");
                break;
            }
            //计算表达式exp
            node->l->pcode=NULL;
            semantic(node->l);
            //创建RETURN node
            node->pcode = (code*)malloc(sizeof(code));
            memset(node->pcode,0,sizeof(code));
            node->pcode->op = RETURN_OP;
            mergecode(node->l->pcode,node->pcode);
            node->pcode=node->l->pcode;
            if(node->l->sem.kind!=symtab[idx].type)
                printf("错误！, 函数%s返回类型与函数定义类型不一致。\n",symtab[idx].id);
            printf("leave 13 node statement is %s \n",node->sem.stmt_type==LOOP?"循环":node->sem.stmt_type==SW_STMT?"switch语句":"未知");
            break;
        case BREAK_NO: //BREAK ';'
            puts("15");
            if(node->sem.stmt_type!=LOOP&&node->sem.stmt_type!=SW_STMT)
                printf("错误, BREAK只能使用在循环或者switch语句中!\n");
            node->pcode=(code*)malloc(sizeof(code));
            memset(node->pcode,0,sizeof(code));
            node->pcode->op = GOTO_BREAK;
            node->pcode->end_label_num = node->sem.end_num;
            //node->pcode->name由父节点设置
            printf("leave 15,a BREAK statement end!\n");
            break;
        case CONTINUE_NO: //CONTINUE ';'
            puts("16");
            if(node->sem.stmt_type!=LOOP)
                printf("错误, CONTINUE 只能使用在循环中!\n");
            node->pcode=(code*)malloc(sizeof(code));
            memset(node->pcode,0,sizeof(code));
            node->pcode->op = GOTO_UPDATE;
            // node->pcode->judge_label_num = node->sem.judge_num;
            // node->pcode->end_label_num = node->sem.end_num;
            node->pcode->update_label_num = node->sem.update_num;
            printf("leave 16,a CONTINUE statement end!\n");
            break;
        case IF_NO: //IF '(' exp ')' stmt1 || IF '(' exp ')' stmt1 else stmt2
            puts("17");
            /*exp
              judge
              stmt1
              endlabel:
            */ 
            //计算exp
            node->l->pcode=NULL;
            semantic(node->l);
            node->pcode = node->l->pcode;
            //生成JUDGE node
            phead=(code*)malloc(sizeof(code));
            memset(phead,0,sizeof(code));
            phead->op=JUDGE;
            phead->end_label_num = end_label_num = newlabel();
            //设置stmt的初始值，包括继承属性
            node->r->pcode=NULL;
            node->r->sem.stmt_type=node->sem.stmt_type;
            node->r->sem.judge_num = node->sem.judge_num;
            node->r->sem.update_num = node->sem.update_num;
            node->r->sem.end_num = node->sem.end_num;
            semantic(node->r);
            //生成endlabel
            ptail =(code*)malloc(sizeof(code));
            memset(ptail,0,sizeof(code));
            ptail->op = LABEL;
            sprintf(ptail->name,"LABEL%d:\n",end_label_num);
            //合并
            node->pcode=node->l->pcode;
            mergecode(node->pcode,phead);
            mergecode(node->pcode,node->r->pcode);
            mergecode(node->pcode,ptail);
            printf("leave 17,a IF THEN statement end!\n");
            break;
        case IF_ELSE:
            puts("17_2");
             /*exp 
              judge
              stmt1
              goto endlabel
              else_label:
              stmt2
              endlabel:
            */ 
            //计算exp
            node->l->pcode=NULL;
            semantic(node->l);
            node->pcode = node->l->pcode;
            //生成JUDGE node
            phead=(code*)malloc(sizeof(code));
            memset(phead,0,sizeof(code));
            phead->op=JUDGE;
            phead->end_label_num = newlabel(); //phead->end_label_num是else_label_num
            //设置stmt1的初始值，包括继承属性
            node->r->pcode=NULL;
            node->r->sem.stmt_type=node->sem.stmt_type;
            node->r->sem.judge_num = node->sem.judge_num;
            node->r->sem.update_num = node->sem.update_num;
            node->r->sem.end_num = node->sem.end_num;
            semantic(node->r);
            //生成goto endlabel
            plabel = (code*)malloc(sizeof(code));
            memset(plabel,0,sizeof(code));
            plabel->op = GOTO_BREAK;
            plabel->end_label_num = end_label_num = newlabel();
            //生成 else_label
            plabel->next=(code*)malloc(sizeof(code));
            memset(plabel->next,0,sizeof(code));
            plabel->next->op= LABEL;
            sprintf(plabel->next->name,"LABEL%d:\n",phead->end_label_num);
            //部分合并
            mergecode(node->pcode,phead);
            mergecode(node->r->pcode,plabel);
            mergecode(node->pcode,node->r->pcode);
            //并入stmt2节点
            ((condition*)node)->c->pcode=NULL;
            ((condition*)node)->c->sem.stmt_type=node->sem.stmt_type;
            ((condition*)node)->c->sem.judge_num = node->sem.judge_num;
            ((condition*)node)->c->sem.update_num = node->sem.update_num;
            ((condition*)node)->c->sem.end_num = node->sem.end_num;
            semantic(((condition*)node)->c);
            mergecode(node->pcode,((condition*)node)->c->pcode);
            //生成endlabel
            ptail =(code*)malloc(sizeof(code));
            memset(ptail,0,sizeof(code));
            ptail->op = LABEL;
            sprintf(ptail->name,"LABEL%d:\n",end_label_num);
            //合并
            mergecode(node->pcode,ptail);
            printf("leave 17_2,a IF_ELSE statement end!\n");
            break;
        case SWITCH_NO: //SWITCH '(' exp ')' '{' case_list  default '}'
            puts("18");
            ((condition*)node)->b->sem.stmt_type=SW_STMT;
            semantic(((condition*)node)->b);
            ((condition*)node)->c->sem.stmt_type=SW_STMT;
            semantic(((condition*)node)->c);
            //简单起见，暂不实现switch的中间代码生成
            node->pcode=NULL;
            printf("leave 18,a SWITCH statement end!\n");
            break;
        case WHILE_NO: //WHILE '(' exp ')' stmt  
            puts("19");
            /*judge_label :
              exp
              judge
              stmt
              goto judge_label
              endlabel*/
            //judge_label
            node->pcode=(code*)malloc(sizeof(code));
            memset(node->pcode,0,sizeof(code));
            node->pcode->op=LABEL;
            node->pcode->judge_label_num = newlabel();
            sprintf(node->pcode->name,"LABEL%d:\n",node->pcode->judge_label_num); 
            //exp
            node->l->pcode=NULL;
            semantic(node->l);
            mergecode(node->pcode,node->l->pcode);
            //judge
            phead = (code*)malloc(sizeof(code));
            memset(phead,0,sizeof(phead));
            phead->op =JUDGE;
            phead->end_label_num = newlabel();
            //stmt
            node->r->pcode=NULL;
            node->r->sem.stmt_type=LOOP;
            node->r->sem.judge_num = node->pcode->judge_label_num;  //continue 跳转的地方
            node->r->sem.end_num = phead->end_label_num;
            semantic(((condition*)node)->b);
            mergecode(phead,node->r->pcode);//judge + stmt
            //init_label+exp+judge+stmt
            mergecode(node->pcode,phead);
            //goto_label
            phead=(code*)malloc(sizeof(code));
            memset(phead,0,sizeof(phead));
            phead->op=GOTO_JUDGE;
            phead->judge_label_num = node->pcode->judge_label_num;
            mergecode(node->pcode,phead);  
            //end_label
            phead = (code*)malloc(sizeof(code));
            phead->op=LABEL;
            sprintf(phead->name,"LABEL %d",node->r->sem.end_num);
            mergecode(node->pcode,phead);
            printf("leave 19,a WHILE statement end!\n");
            break;
        case FOR_NO: //FOR '(' init_exp ';' judge_exp ';' update_exp ')' for_body 
            puts("20");
            /*  init_exp
                judge_label:
                judge_exp
                judge
                for_body
                update_label:
                update_exp
                goto judge_label
                endlabel:
            */
            //init_exp
            node->l->pcode=NULL;
            semantic(((condition*)node)->a);
            node->pcode=node->l->pcode;
            //judge_label
            plabel=(code*)malloc(sizeof(code));
            memset(plabel,0,sizeof(plabel));
            plabel->op=LABEL;
            judge_label_num = newlabel();
            sprintf(plabel->name,"LABEL%d:\n",judge_label_num);
            //judge_exp
            ((condition*)node)->b->pcode=NULL;
            semantic(((condition*)node)->b);
            phead = ((condition*)node)->b->pcode;
            //judge
            ptail=(code*)malloc(sizeof(code));
            memset(ptail,0,sizeof(ptail));
            ptail->op=JUDGE;
            ptail->end_label_num = end_label_num = newlabel();
            //init_exp+judge_label+judge_exp+judge
            mergecode(phead,ptail);
            mergecode(node->pcode,plabel);
            mergecode(node->pcode,phead);
            //for_body
            (((condition*)node)->d->pcode)=NULL;
            update_label_num = newlabel();
            if(((condition*)node)->d){
                ((condition*)node)->d->sem.judge_num = judge_label_num;
                ((condition*)node)->d->sem.end_num = end_label_num;
                ((condition*)node)->d->sem.update_num = update_label_num;
                ((condition*)node)->d->sem.stmt_type=LOOP;
                semantic(((condition*)node)->d);
            }
            //update_label:
            phead = (code*)malloc(sizeof(code));
            memset(phead,0,sizeof(code));
            phead->op=LABEL;
            sprintf(phead->name,"LABEL%d:\n",update_label_num);
            //update_exp
            ((condition*)node)->c->pcode=NULL;
            semantic(((condition*)node)->c);
            //merge for_body and update_exp
            mergecode(phead,((condition*)node)->c->pcode);
            mergecode(((condition*)node)->d->pcode,phead);
            mergecode(node->pcode,((condition*)node)->d->pcode);
            //goto judge
            phead = (code*)malloc(sizeof(code));
            memset(phead,0,sizeof(code));
            phead->op=GOTO_JUDGE;
            phead->judge_label_num = judge_label_num;
            //endlabel
            ptail = (code*)malloc(sizeof(code));
            memset(ptail,0,sizeof(code));
            ptail->op=LABEL;
            sprintf(ptail->name,"LABEL%d:\n",end_label_num);
            //merge 
            mergecode(phead,ptail);
            mergecode(node->pcode,phead);
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
            puts("23");
            if(node->l->nodetype!=ID_NO&&node->l->nodetype!=ELE_NO)
                printf("错误！, ASSIGN 语句需要是左值!\n");
            node->r->pcode=NULL;
            semantic(node->r);
            node->l->pcode=NULL;
            semantic(node->l);
            node->sem.kind=node->l->sem.kind;
            node->pcode=node->r->pcode;
            mergecode(node->pcode,node->l->pcode);
            //创建赋值节点
            phead = (code*)malloc(sizeof(code));
            memset(phead,0,sizeof(code));
            phead->op=ASSIGN_OP;
            memcpy(&phead->var,&node->l->sem,sizeof(struct seman_info));
            strcpy(phead->name,((num*)(node->l))->numval.string);
            mergecode(node->pcode,phead);
            printf("leave 23,a ASSIGN exp!\n");
            break;
        case AND_NO: //exp RELOP exp
        case OR_NO:
        case GR_NO:
        case LS_NO:
        case GE_NO:
        case LE_NO:
        case EQ_NO:
        case NE_NO:
            puts("24");
            node->l->pcode=node->r->pcode=NULL;
            semantic(node->l);
            semantic(node->r);
            node->sem.kind=INT_TYPE;//关系表达式类型全设置为INT
            node->pcode=node->l->pcode;
            mergecode(node->pcode,node->r->pcode);
            phead =(code*)malloc(sizeof(code));
            memset(phead,0,sizeof(code));
            phead->op=node->nodetype;
            mergecode(node->pcode,phead);
            printf("leave 24,relatoin op!\n");
            break;
        case ADD:   //exp OP exp
        case MINUS:
        case MUL:
        case DIV:
            puts("25");
            node->l->pcode=node->r->pcode=NULL;
            semantic(node->l);
            semantic(node->r);
            if(node->l->sem.kind==FLOAT_TYPE||node->r->sem.kind==FLOAT_TYPE)
                node->sem.kind=FLOAT_TYPE;
            else node->sem.kind=INT_TYPE;
            node->pcode=node->l->pcode;
            mergecode(node->pcode,node->r->pcode);
            phead=(code*)malloc(sizeof(code));
            memset(phead,0,sizeof(code));
            phead->op=node->nodetype;
            mergecode(node->pcode,phead);
            printf("leave 25!\n");
            break;
        case UMINUS_NO:  //- exp 
            puts("26");
            node->l->pcode=NULL;
            semantic(node->l);
            node->sem.kind=node->l->sem.kind;
            node->pcode=(code*)malloc(sizeof(code));
            memset(node->pcode,0,sizeof(code));
            node->pcode->op = UMINUS_NO;
            printf("leave 26!\n");
            break;
        case NOT: 
            puts("27");
            node->l->pcode=NULL;
            semantic(node->l);
            node->sem.kind=INT_TYPE;
            node->pcode=(code*)malloc(sizeof(code));
            memset(node->pcode,0,sizeof(code));
            node->pcode->op=NOT;
            printf("leave 27\n");
            break;
        case CHAR_NO: 
            puts("28");
            node->sem.kind=CHAR_TYPE;
            node->pcode=(code*)malloc(sizeof(code));
            memset(node->pcode,0,sizeof(code));
            node->pcode->op=CHAR_NO;
            node->pcode->var.size = ((num*)node)->numval.ch;
            printf("leave 28\n");
            break;
        case INT_NO: 
            puts("29");
            node->sem.kind=INT_TYPE;
            node->pcode=(code*)malloc(sizeof(code));
            memset(node->pcode,0,sizeof(code));
            node->pcode->op=INT_NO;
            node->pcode->var.size = ((num*)node)->numval.intval;
            printf("leave 29!\n");
            break;
        case FLOAT_NO:
            puts("30");
            node->sem.kind=FLOAT_TYPE;
            printf("leave 30!\n");
            break;
        case STRING_NO:
            puts("31");
            node->sem.kind=STR_CONST;
            printf("leave 31!\n");
            break;
        case ID_NO: //ID
            puts("32");
            idx=lookup(((num*)node)->numval.string);
            if(idx==-1)
                printf("错误！,变量%s未声明！\n",((num*)node)->numval.string);    
            else {
                node->sem.kind=symtab[idx].kind;
                ((num*)node)->pcode=(code*)malloc(sizeof(code));
                printf("idx is %d\n",idx);
                memset(node->pcode,0,sizeof(code));
                node->pcode->op=ID_NO;
                node->pcode->var.addr=symtab[idx].addr;
                strcpy(node->pcode->name,symtab[idx].id);
                //debug
                // printf("deubging %s\n",((num*)node)->numval.string);
            }
            printf("leave 32!\n");
            break;
        case FUN_CALL: //ID '(' args_list ')'
            puts("33");
            idx=lookup(((fun*)node)->id);
            if(idx==-1) printf("错误！,函数%s尚未声明或定义。\n",((fun*)node)->id);
            else{
                node->sem.kind = symtab[idx].type;
                if(node->l) node->l->pcode=NULL;
                semantic(node->l);
                if(node->l==NULL && symtab[idx].paramnum)
                    printf("错误！函数%s的实参不能为空。\n");
                else if(node->l->sem.paranum > symtab[idx].paramnum)
                    printf("错误！函数%s的实参过多。\n",((fun*)node)->id);
                else if(node->l->sem.paranum < symtab[idx].paramnum)
                    printf("错误！函数%s的实参过少。\n",((fun*)node)->id);
                else{
                    for(head=0,pnode=node->l;head<node->l->sem.paranum;head++){
                        if(symtab[idx].paratype[head]!=pnode->l->sem.kind)
                            printf("错误！函数%s的实参与形参类型不匹配。\n",((fun*)node)->id);
                        pnode = pnode->r;
                    } 
                    //创建FUN_PUBLIC节点
                    node->pcode=(code*)malloc(sizeof(code));
                    memset(node->pcode,0,sizeof(code));
                    node->pcode->op = FUN_PUBLIC;
                    //合并FUN_PUBLIC 和 实参节点
                    mergecode(node->pcode,node->l->pcode);
                    //创建函数调用节点
                    phead=(code*)malloc(sizeof(code));
                    memset(phead,0,sizeof(code));
                    phead->op=FUN_CALL;
                    strcpy(phead->name,((fun*)node)->id);
                    mergecode(node->pcode,phead);
                }
            }
            printf("leave 33!\n");
            break;
        case ELE_NO: //ID '[' exp ']'
            puts("34");
            semantic(node->l);
            if(node->l->sem.kind!=INT_TYPE)
                printf("错误！,数组%s的索引只能是整数。\n",((ele*)node)->id);
            else node->sem.kind=node->l->sem.kind;
            printf("leave 34!\n");
            break;
        case ARGS: // exp || exp ',' args_list || empty
            puts("35");
            node->sem.paranum = 0;
            if(node->l){
                node->l->pcode = NULL;
                semantic(node->l);
                node->pcode = node->l->pcode;
                node->sem.paranum++;
            }
            if(node->r){
                node->r->pcode = NULL;
                semantic(node->r);
                if(node->pcode==NULL) node->pcode=node->r->pcode;
                else mergecode(node->pcode,node->r->pcode);
                node->sem.paranum += node->r->sem.paranum;
            }
            // if(cnt>=symtab[head].paramnum) printf("错误！，数组%s的调用参数过多。\n",symtab[head].id);
            // else {
            //     node->l->pcode=NULL;
            //     semantic(node->l);
            //     if(node->l->sem.kind!=symtab[head].paratype[cnt]){
            //         printf("错误！,函数%s的实参与形参不匹配。\n",symtab[head].id);
            //         break;
            //     }
            //     else {
            //         node->pcode=node->l->pcode;
            //         if(node->r){ 
            //             cnt++;
            //             node->r->pcode=NULL;
            //             semantic(node->r);
            //             mergecode(node->pcode,node->r->pcode);
            //         }
            //         else if(cnt!=symtab[head].paramnum-1) printf("错误！,函数%s的实参过少。\n",symtab[head].id);
                    //TEST
                    printf("!!!TEST ARGS begin\n");
                    printcode(node);
                    printf("!!!TEST ARGS finished\n");
            //     }                    
            // }
            printf("leave 35!\n");
            break;
        default: printf("UNKNOWN NODE!!! ");
            break;
    }
}