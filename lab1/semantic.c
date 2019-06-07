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
    printf("������  ����     �㼶   ƫ��   ��С   �βθ���\n");
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
            node->sem.size+=node->l->sem.size; //ȫ�ֱ�����Ҫ�Ŀռ�
            node->pcode=node->l->pcode;//finish pcode
            printsymt(node->sem.level);
            break;
        case EXTERN_VAR://TYPE var_init_list ';'
        case EXTERN_VAR_LIST://TYPE var_init_list ';' declarations;
            puts("-2");
            node->l->pcode=NULL;//initial pcode
            node->l->sem.kind=((dec*)node)->type;//ȷ�����ڵ������
            node->l->sem.level=0;
            node->l->sem.addr=node->sem.addr;
            semantic(node->l); //����һ������
            node->sem.size=node->l->sem.size;//���´�С
            if((node)->r){//������EXTERN_VAR_LIST
                node->r->pcode = NULL;//initial pcode
                node->r->sem.level=0;
                node->r->sem.addr=node->sem.addr+node->sem.size;
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
            }
            //���ڷ��㣬��ʱδʵ��ȫ�ֱ������м�������ɡ�
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
            node->sem.size=0;//������sizeĬ��Ϊ0
            node->pcode=node->l->pcode; //update node->pcode
            node->r->pcode=NULL; //initial declaration pcode
            node->r->sem.addr=node->sem.addr;//����declaration ��ƫ��
            node->r->sem.level=0;
            //kind ��ʱδ֪
            semantic(node->r);
            node->sem.size=node->r->sem.size;
            mergecode(node->pcode,node->r->pcode); //�ϲ�����
            printf("leave 0 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case VAR_NO: // ID  ����ID���������kind��size������ȷ����,addr �� level ȷ�������Ƿ��Ǻ����ڲ�����
            puts("1");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("���󣡱���%s�ظ�����\n",((var_init*)node)->id);
            //node->addr �ɸ��ڵ�ָ��
            //node->kind �ɸ��ڵ�ָ��
            //node->level�ɸ��ڵ�ָ��
            node->sem.size = getsize(node->sem.kind);
            insertsym(((var_init*)node)->id,node->sem);
            //���������������pcode���в���
            printf("leave 1 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case VAR_LIST: // ID ',' var_init_list
            puts("2");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("���󣡱���%s�ظ�����\n",((var_init*)node)->id);
            //node->addr �ɸ��ڵ�ָ��
            //node->kind �ɸ��ڵ�ָ��
            //node->level�ɸ��ڵ�ָ��
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
        case VAR_INIT_LIST: //ID '=' exp ',' var_init_list   exp���������ṩ������
            puts("3");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("���󣡱���%s�ظ�����\n",((var_init*)node)->id);
            //node->addr �ɸ��ڵ�ָ��
            //node->kind �ɸ��ڵ�ָ��
            //node->level�ɸ��ڵ�ָ��
            node->sem.size=getsize(node->sem.kind);
            insertsym(((var_init*)node)->id,node->sem);
            //exp kind�� ���ӽڵ����¶���ȷ��
            semantic(node->l); //����exp��semantic��ȷ����kind
            if(node->sem.kind!=node->l->sem.kind) printf("���󣡣�����%s�������������ʼ�����Ͳ�һ�¡�\n",((var_init*)node)->id);
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
            if(idx!=-1) printf("���󣡱���%s�ظ�����\n",((var_init*)node)->id);
            //node->addr �ɸ��ڵ�ָ��
            //node->kind �ɸ��ڵ�ָ��
            //node->level�ɸ��ڵ�ָ��
            node->sem.size=getsize(node->sem.kind);
            insertsym(((var_init*)node)->id,node->sem);
            node->l->pcode=NULL;
            semantic(node->l);
            if(node->sem.kind!=node->l->sem.kind) printf("���󣡣�����%s�������������ʼ�����Ͳ�һ�¡�\n",((var_init*)node)->id);
            printf("leave 4 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case ARRAY_NO: // ID '[' INT ']'
            puts("5");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("����������%s�Ѿ�����\n",((var_init*)node)->id);
            //node->addr �ɸ��ڵ�ָ��
            //node->kind �ɸ��ڵ�ָ��
            //node->level�ɸ��ڵ�ָ��
            node->sem.size=getsize(node->sem.kind)*((var_init*)node)->idx;
            insertsym(((var_init*)node)->id,node->sem);
            printf("leave 5 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case ARRAY_LIST: // ID '[ INT ']' ',' var_init_list
            puts("6");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("����������%s�Ѿ�����\n",((var_init*)node)->id);
            //node->addr �ɸ��ڵ�ָ��
            //node->kind �ɸ��ڵ�ָ��
            //node->level�ɸ��ڵ�ָ��
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
            if(idx!=-1) printf("����������%s�Ѿ�����\n",((var_init*)node)->id);
            //node->addr �ɸ��ڵ�ָ��
            //node->kind �ɸ��ڵ�ָ��
            //node->level�ɸ��ڵ�ָ��
            node->sem.size=getsize(node->sem.kind)* ((var_init*)node)->idx;
            insertsym(((var_init*)node)->id,node->sem);
            printf("leave 7 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case ARRAY_INIT_LIST: // ID '[' INT ']' = STRING , var_init_list
            puts("8");
            idx=lookup(((var_init*)node)->id);
            if(idx!=-1) printf("����������%s�Ѿ�����\n",((var_init*)node)->id);
            //node->addr �ɸ��ڵ�ָ��
            //node->kind �ɸ��ڵ�ָ��
            //node->level�ɸ��ڵ�ָ��
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
        case FUN_DEC: //TYPE ID '(' param_list ')' ';' || comp_stmt  ����ȷ���������¼��С
            puts("9");
            idx=lookup(((fun*)node)->id);
            if(idx!=-1) printf("����,������%s�Ѵ���!\n",((fun*)node)->id);
            node->sem.stmt_type=((fun*)node)->returntype;  //��������������Ҫȷ�����������Ƿ����
            //node->kind ���ɸ��ڵ�ָ��
            node->sem.addr=0;//������ƫ�Ƶ�ַ
            idx = insertsym(((fun*)node)->id,node->sem);   //������ű�
            node->sem.size=0; //��ʱ��ʼ���������¼��СΪ0
            if(node->l){      //�β��б�ǿ�
                node->l->sem.level=node->sem.level+1;
                node->l->sem.addr=node->sem.addr;
                semantic(node->l);  //��������β��б�
                node->sem.size+=node->l->sem.size;
                symtab[idx].paramnum=node->l->sem.paranum; //��¼�βθ���
                symtab[idx].paratype=(int*)malloc(sizeof(int)*symtab[idx].paramnum);
                for(int i=0;i<symtab[idx].paramnum;i++)
                    symtab[idx].paratype[i]=symtab[idx+1+i].kind;
            }
            if(node->r){  //��������
                /**********������code������************/
                node->pcode=(code*)malloc(sizeof(code));
                memset(node->pcode,0,sizeof(code));
                node->pcode->op=LABEL;
                sprintf(node->pcode->name,"%s:\n",((fun*)node)->id);
                node->r->pcode = NULL;
                node->r->sem.level=node->sem.level+1;
                node->r->sem.addr=node->sem.addr+node->sem.size; //Ҫ�����βα����Ĵ�С
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
                memcpy(&node->pcode->var,&node->sem,sizeof(struct seman_info)); /*���ƺ�������Ϣ*/
                mergecode(node->pcode,node->r->pcode); //���pcode��ƴ��
                symtab[idx].size=node->sem.size;
            }
            printf("leave 9 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            break;
        case PARAM: //TYPE ID ',' param_list || TYPE ID 
            puts("10");
            idx=lookup(((param*)node)->id);
            if(idx!=-1) printf("����, �����β�����!\n");
            //node->addr �Ѿ��ɸ��ڵ�����
            //node->level�Ѿ��ɸ��ڵ�����
            node->sem.kind=(((param*)node)->datatypeid);
            node->sem.size=getsize(node->sem.kind);
            //�����βθ���
            node->sem.paranum=1; 
            insertsym(((param*)node)->id,node->sem);
            if(node->l){ //�βλ�δ����
                //node->kind ����Ҫ
                node->l->sem.level=node->sem.level;
                node->l->sem.addr=node->sem.addr+node->sem.size;
                semantic(node->l);
                node->sem.size+=node->l->sem.size;
                node->sem.paranum+=node->l->sem.paranum;//�����βθ���
                // printf("this paranum is %d \n",node->sem.paranum);
            }
            printf("leave 10 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case COMPSTMT: // '{' var_declaration  stmt_list '}' 
            puts("11");
            node->sem.size=0;
            if(node->l){
                if(node->sem.stmt_type==LOOP||node->sem.stmt_type==SW_STMT){
                    printf("���󣡣�ѭ������SWITCH����в������������\n");
                    break;
                }
                //�˴���ʱ����Ҫnode->kind�������ӽڵ���������
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
                //�̳�lable_num
                node->r->sem.end_num = node->sem.end_num;
                node->r->sem.judge_num = node->sem.judge_num;
                node->r->sem.update_num = node->sem.update_num;
                semantic(node->r); //���������͵�����
                node->pcode=node->r->pcode; //��������б�
            }
            printf("leave 11 node addr is %d size is %d \n",node->sem.addr,node->sem.size);
            printsymt(node->sem.level);
            break;
        case INNER_VAR: //TYPE var_init_list ';' var_declaration
            puts("12");
            node->sem.kind=((dec*)node)->type; //��������
            //����var_init_list
            node->l->sem.level=node->sem.level;
            node->l->sem.addr=node->sem.addr;
            node->l->sem.kind=node->sem.kind;
            semantic(node->l);
            node->sem.size=node->l->sem.size;
            if(node->r){ //�����������
                //node->r->sem.kind���ӽڵ���������
                node->r->sem.level=node->sem.level;
                node->r->sem.addr=node->sem.addr+node->sem.size;
                semantic(node->r);
                node->sem.size+=node->r->sem.size;
            }
            printf("leave 12 node addr is %d size is %d \n",node->sem.addr,node->sem.size); 
            break;
        case STMTLIST: //stmt stmt_list ��䲿�ֲ�����Ҫ����addr��level,kind�ˡ�ֻ��Ҫ����stmt_type
            puts("13");
            //���ȸ�stmt����һ��label.
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
            printf("leave 13 node statement is %s \n",node->sem.stmt_type==LOOP?"ѭ��":node->sem.stmt_type==SW_STMT?"switch���":"δ֪");
            break;
        case RETURN_NO: //RETURN exp ';' ��Ҫȷ�����������Ƿ�ƥ��
            puts("14");
            idx=findfunc();
            if(idx==-1){
                printf("���󣡣�RETURN ���ֻ���ں�������ʹ��");
                break;
            }
            //������ʽexp
            node->l->pcode=NULL;
            semantic(node->l);
            //����RETURN node
            node->pcode = (code*)malloc(sizeof(code));
            memset(node->pcode,0,sizeof(code));
            node->pcode->op = RETURN_OP;
            mergecode(node->l->pcode,node->pcode);
            node->pcode=node->l->pcode;
            if(node->l->sem.kind!=symtab[idx].type)
                printf("����, ����%s���������뺯���������Ͳ�һ�¡�\n",symtab[idx].id);
            printf("leave 13 node statement is %s \n",node->sem.stmt_type==LOOP?"ѭ��":node->sem.stmt_type==SW_STMT?"switch���":"δ֪");
            break;
        case BREAK_NO: //BREAK ';'
            puts("15");
            if(node->sem.stmt_type!=LOOP&&node->sem.stmt_type!=SW_STMT)
                printf("����, BREAKֻ��ʹ����ѭ������switch�����!\n");
            node->pcode=(code*)malloc(sizeof(code));
            memset(node->pcode,0,sizeof(code));
            node->pcode->op = GOTO_BREAK;
            node->pcode->end_label_num = node->sem.end_num;
            //node->pcode->name�ɸ��ڵ�����
            printf("leave 15,a BREAK statement end!\n");
            break;
        case CONTINUE_NO: //CONTINUE ';'
            puts("16");
            if(node->sem.stmt_type!=LOOP)
                printf("����, CONTINUE ֻ��ʹ����ѭ����!\n");
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
            //����exp
            node->l->pcode=NULL;
            semantic(node->l);
            node->pcode = node->l->pcode;
            //����JUDGE node
            phead=(code*)malloc(sizeof(code));
            memset(phead,0,sizeof(code));
            phead->op=JUDGE;
            phead->end_label_num = end_label_num = newlabel();
            //����stmt�ĳ�ʼֵ�������̳�����
            node->r->pcode=NULL;
            node->r->sem.stmt_type=node->sem.stmt_type;
            node->r->sem.judge_num = node->sem.judge_num;
            node->r->sem.update_num = node->sem.update_num;
            node->r->sem.end_num = node->sem.end_num;
            semantic(node->r);
            //����endlabel
            ptail =(code*)malloc(sizeof(code));
            memset(ptail,0,sizeof(code));
            ptail->op = LABEL;
            sprintf(ptail->name,"LABEL%d:\n",end_label_num);
            //�ϲ�
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
            //����exp
            node->l->pcode=NULL;
            semantic(node->l);
            node->pcode = node->l->pcode;
            //����JUDGE node
            phead=(code*)malloc(sizeof(code));
            memset(phead,0,sizeof(code));
            phead->op=JUDGE;
            phead->end_label_num = newlabel(); //phead->end_label_num��else_label_num
            //����stmt1�ĳ�ʼֵ�������̳�����
            node->r->pcode=NULL;
            node->r->sem.stmt_type=node->sem.stmt_type;
            node->r->sem.judge_num = node->sem.judge_num;
            node->r->sem.update_num = node->sem.update_num;
            node->r->sem.end_num = node->sem.end_num;
            semantic(node->r);
            //����goto endlabel
            plabel = (code*)malloc(sizeof(code));
            memset(plabel,0,sizeof(code));
            plabel->op = GOTO_BREAK;
            plabel->end_label_num = end_label_num = newlabel();
            //���� else_label
            plabel->next=(code*)malloc(sizeof(code));
            memset(plabel->next,0,sizeof(code));
            plabel->next->op= LABEL;
            sprintf(plabel->next->name,"LABEL%d:\n",phead->end_label_num);
            //���ֺϲ�
            mergecode(node->pcode,phead);
            mergecode(node->r->pcode,plabel);
            mergecode(node->pcode,node->r->pcode);
            //����stmt2�ڵ�
            ((condition*)node)->c->pcode=NULL;
            ((condition*)node)->c->sem.stmt_type=node->sem.stmt_type;
            ((condition*)node)->c->sem.judge_num = node->sem.judge_num;
            ((condition*)node)->c->sem.update_num = node->sem.update_num;
            ((condition*)node)->c->sem.end_num = node->sem.end_num;
            semantic(((condition*)node)->c);
            mergecode(node->pcode,((condition*)node)->c->pcode);
            //����endlabel
            ptail =(code*)malloc(sizeof(code));
            memset(ptail,0,sizeof(code));
            ptail->op = LABEL;
            sprintf(ptail->name,"LABEL%d:\n",end_label_num);
            //�ϲ�
            mergecode(node->pcode,ptail);
            printf("leave 17_2,a IF_ELSE statement end!\n");
            break;
        case SWITCH_NO: //SWITCH '(' exp ')' '{' case_list  default '}'
            puts("18");
            ((condition*)node)->b->sem.stmt_type=SW_STMT;
            semantic(((condition*)node)->b);
            ((condition*)node)->c->sem.stmt_type=SW_STMT;
            semantic(((condition*)node)->c);
            //��������ݲ�ʵ��switch���м��������
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
            node->r->sem.judge_num = node->pcode->judge_label_num;  //continue ��ת�ĵط�
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
                printf("���󣡣�CASE���ֻ����switch��ʹ�ã�\n");
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
                printf("����,DEFAULTֻ����switch�����ʹ�ã�\n");
            printf("leave 22,a DEFAULT statement!\n");
            break;
       /***************������exp���֣���Ҫȷ�����ʽ���ͣ�kind��***************/
        case ASSIGN: //exp '=' exp
            puts("23");
            if(node->l->nodetype!=ID_NO&&node->l->nodetype!=ELE_NO)
                printf("����, ASSIGN �����Ҫ����ֵ!\n");
            node->r->pcode=NULL;
            semantic(node->r);
            node->l->pcode=NULL;
            semantic(node->l);
            node->sem.kind=node->l->sem.kind;
            node->pcode=node->r->pcode;
            mergecode(node->pcode,node->l->pcode);
            //������ֵ�ڵ�
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
            node->sem.kind=INT_TYPE;//��ϵ���ʽ����ȫ����ΪINT
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
                printf("����,����%sδ������\n",((num*)node)->numval.string);    
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
            if(idx==-1) printf("����,����%s��δ�������塣\n",((fun*)node)->id);
            else{
                node->sem.kind = symtab[idx].type;
                if(node->l) node->l->pcode=NULL;
                semantic(node->l);
                if(node->l==NULL && symtab[idx].paramnum)
                    printf("���󣡺���%s��ʵ�β���Ϊ�ա�\n");
                else if(node->l->sem.paranum > symtab[idx].paramnum)
                    printf("���󣡺���%s��ʵ�ι��ࡣ\n",((fun*)node)->id);
                else if(node->l->sem.paranum < symtab[idx].paramnum)
                    printf("���󣡺���%s��ʵ�ι��١�\n",((fun*)node)->id);
                else{
                    for(head=0,pnode=node->l;head<node->l->sem.paranum;head++){
                        if(symtab[idx].paratype[head]!=pnode->l->sem.kind)
                            printf("���󣡺���%s��ʵ�����β����Ͳ�ƥ�䡣\n",((fun*)node)->id);
                        pnode = pnode->r;
                    } 
                    //����FUN_PUBLIC�ڵ�
                    node->pcode=(code*)malloc(sizeof(code));
                    memset(node->pcode,0,sizeof(code));
                    node->pcode->op = FUN_PUBLIC;
                    //�ϲ�FUN_PUBLIC �� ʵ�νڵ�
                    mergecode(node->pcode,node->l->pcode);
                    //�����������ýڵ�
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
                printf("����,����%s������ֻ����������\n",((ele*)node)->id);
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
            // if(cnt>=symtab[head].paramnum) printf("���󣡣�����%s�ĵ��ò������ࡣ\n",symtab[head].id);
            // else {
            //     node->l->pcode=NULL;
            //     semantic(node->l);
            //     if(node->l->sem.kind!=symtab[head].paratype[cnt]){
            //         printf("����,����%s��ʵ�����ββ�ƥ�䡣\n",symtab[head].id);
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
            //         else if(cnt!=symtab[head].paramnum-1) printf("����,����%s��ʵ�ι��١�\n",symtab[head].id);
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