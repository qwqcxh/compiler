#include "mc.h"

void genasm(ast* node){
    code* h=node->pcode;
    FILE* pf = fopen("fibo.asm","w");
    int num,end_num,size,i;
    fprintf(pf,".data\n");
    fprintf(pf,"_Prompt: .asciiz \"Enter an integer:  \"\n");
    fprintf(pf,"_ret: .asciiz \"\\n\"\n");
    fprintf(pf,".globl main\n");
    fprintf(pf,".text\n");
    fputs("#FUN_PUBLIC BEGIN\n",pf);
    fprintf(pf,"addi $sp,$sp,-12\n");
    fprintf(pf,"sw $ra,8($sp)\n");
    fprintf(pf,"lw $t1,($fp)\n");
    fprintf(pf,"sw $t1,4($sp)\n");
    fprintf(pf,"add $fp,$sp,$zero\n");
    fprintf(pf,"addi $sp,$sp,%d\n",-h->var.size);
    fputs("#FUN_PUBLIC END\n",pf);
    fprintf(pf,"  jal main\n");
    fprintf(pf,"  li $v0,10\nsyscall\n");
    fprintf(pf,"read:\n");
    fprintf(pf,"  li $v0,4\n");
    fprintf(pf,"  la $a0,_Prompt\n");
    fprintf(pf,"  syscall\n");
    fprintf(pf,"  li $v0,5\n");
    fprintf(pf,"  syscall\n");
    fprintf(pf,"  sw $v0,12($fp)\n");  //保存返回值
     fprintf(pf,"add $t0,$ra,$zero\n");
    fprintf(pf,"lw $ra,8($fp)\n");
    fprintf(pf,"addi $sp,$fp,8\n");
    fprintf(pf,"lw $fp,4($fp)\n");
    fprintf(pf,"jr $t0\n");
    fprintf(pf,"write:\n");
    fprintf(pf,"  lw $a0,4($sp)\n");
    fprintf(pf,"  addi $sp,$sp,4\n");
    fprintf(pf,"  li $v0,1\n");
    fprintf(pf,"  syscall\n");
    fprintf(pf,"  li $v0,4\n");
    fprintf(pf,"  la $a0,_ret\n");
    fprintf(pf,"  syscall\n");
    fprintf(pf,"add $t0,$ra,$zero\n");
    fprintf(pf,"lw $ra,8($fp)\n");
    fprintf(pf,"addi $sp,$fp,8\n");
    fprintf(pf,"lw $fp,4($fp)\n");
    fprintf(pf,"jr $t0\n");
    while(h){
        switch(h->op){
            case LABEL:
                fprintf(pf,"##LABEL\n");
                fprintf(pf,"%s",h->name);
                break;
            case RETURN_OP:
                fprintf(pf,"lw $t0,4($sp) #RETURN BEGIN\n");
                fprintf(pf,"sw $t0,12($fp)\n");  //保存返回值
                fprintf(pf,"add $t0,$ra,$zero\n");
                fprintf(pf,"lw $ra,8($fp)\n");
                fprintf(pf,"addi $sp,$fp,8\n");
                fprintf(pf,"lw $fp,4($fp)\n");
                fprintf(pf,"jr $t0 #RETURN FINISHED\n");
                break;
            case GOTO_BREAK:
                fprintf(pf,"#GOTO_BREAK BEGIN\n\n");
                fprintf(pf,"j LABEL%d\n",h->end_label_num);
                fprintf(pf,"#GOTO_BREAK END\n\n");
                break;
            case GOTO_UPDATE:
                fprintf(pf,"j LABEL%d #GOTO_UPDATE BEGIN\n",h->update_label_num);
                break;
            case JUDGE:
                fprintf(pf,"lw $t0,4($sp) #JUDGE BEGIN\n");
                fprintf(pf,"addi $sp,$sp,4\n");
                fprintf(pf,"beqz $t0,LABEL%d #JUDGE END\n",h->end_label_num);
                break;
            case GOTO_JUDGE:
                fprintf(pf,"j LABEL%d #GOTO_JUDGE BEGIN\n",h->judge_label_num);
                break;
            case ASSIGN_OP:
                fprintf(pf,"lw $t0,8($sp) #ASSIGN_OP BEGIN\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"sw $t0,-%d($fp) #ASSIGN_OP END\n",h->var.addr);
                //fprintf(pf,"addi $sp,$sp,-4\n");
                break;
            case AND_NO:
                fprintf(pf,"lw $t1,8($sp) #AND BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"and $t0,$t1,$t2\n");
                fprintf(pf,"sw $t0,($sp)\n");
                fprintf(pf,"addi $sp,$sp,-4 #AND END\n");
                break;
            case OR_NO:
                fprintf(pf,"lw $t1,8($sp) #OR BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"or $t0,$t1,$t2\n");
                fprintf(pf,"sw $t0,($sp)\n");
                fprintf(pf,"addi $sp,$sp,-4 #OR END\n");
                break;
            case GR_NO:
                fprintf(pf,"lw $t1,8($sp) #GR BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"addi $t3,$zero,0\n");
                fprintf(pf,"addi $t4,$zero,1\n");
                fprintf(pf,"sub $t0,$t1,$t2\n");
                fprintf(pf,"bgtz $t0,LABEL%d\n",num=newlabel());
                fprintf(pf,"sw $t3,($sp)\n");
                fprintf(pf,"j LABEL%d\n",end_num=newlabel());
                fprintf(pf,"LABEL%d:\n",num);
                fprintf(pf,"sw $t4,($sp)\n");
                fprintf(pf,"LABEL%d:\n",end_num);
                fprintf(pf,"addi $sp,$sp,-4 #GR END\n");
                break;
            case LS_NO:
                fprintf(pf,"lw $t1,8($sp) #LS BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"addi $t3,$zero,0\n");
                fprintf(pf,"addi $t4,$zero,1\n");
                fprintf(pf,"sub $t0,$t1,$t2\n");
                fprintf(pf,"bltz $t0,LABEL%d\n",num=newlabel());
                fprintf(pf,"sw $t3,($sp)\n");
                fprintf(pf,"j LABEL%d\n",end_num=newlabel());
                fprintf(pf,"LABEL%d:\n",num);
                fprintf(pf,"sw $t4,($sp)\n");
                fprintf(pf,"LABEL%d:\n",end_num);
                fprintf(pf,"addi $sp,$sp,-4 #LS END\n");
                break;
            case GE_NO:
                fprintf(pf,"lw $t1,8($sp) #GE BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"addi $t3,$zero,0\n");
                fprintf(pf,"addi $t4,$zero,1\n");
                fprintf(pf,"sub $t0,$t1,$t2\n");
                fprintf(pf,"bgez $t0,LABEL%d\n",num=newlabel());
                fprintf(pf,"sw $t3,($sp)\n");
                fprintf(pf,"j LABEL%d\n",end_num=newlabel());
                fprintf(pf,"LABEL%d:\n",num);
                fprintf(pf,"sw $t4,($sp)\n");
                fprintf(pf,"LABEL%d:\n",end_num);
                fprintf(pf,"addi $sp,$sp,-4 #GE END\n");
                break;
            case LE_NO:
                fprintf(pf,"lw $t1,8($sp) #LE BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"addi $t3,$zero,0\n");
                fprintf(pf,"addi $t4,$zero,1\n");
                fprintf(pf,"sub $t0,$t1,$t2\n");
                fprintf(pf,"blez $t0,LABEL%d\n",num=newlabel());
                fprintf(pf,"sw $t3,($sp)\n");
                fprintf(pf,"j LABEL%d\n",end_num=newlabel());
                fprintf(pf,"LABEL%d:\n",num);
                fprintf(pf,"sw $t4,($sp)\n");
                fprintf(pf,"LABEL%d:\n",end_num);
                fprintf(pf,"addi $sp,$sp,-4 #LE END\n");
                break;
            case EQ_NO:
                fprintf(pf,"lw $t1,8($sp) #EQ BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"addi $t3,$zero,0\n");
                fprintf(pf,"addi $t4,$zero,1\n");
                fprintf(pf,"beq $t1,$t2,LABEL%d\n",num=newlabel());
                fprintf(pf,"sw $t3,($sp)\n");
                fprintf(pf,"j LABEL%d\n",end_num=newlabel());
                fprintf(pf,"LABEL%d:\n",num);
                fprintf(pf,"sw $t4,($sp)\n");
                fprintf(pf,"LABEL%d:\n",end_num);
                fprintf(pf,"addi $sp,$sp,-4 #EQ END\n");
                break;
            case NE_NO:
                fprintf(pf,"lw $t1,8($sp) #NE BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"addi $t3,$zero,0\n");
                fprintf(pf,"addi $t4,$zero,1\n");
                fprintf(pf,"bne $t1,$t2,LABEL%d\n",num=newlabel());
                fprintf(pf,"sw $t3,($sp)\n");
                fprintf(pf,"j LABEL%d\n",end_num=newlabel());
                fprintf(pf,"LABEL%d:\n",num);
                fprintf(pf,"sw $t4,($sp)\n");
                fprintf(pf,"LABEL%d:\n",end_num);
                fprintf(pf,"addi $sp,$sp,-4 #NE END\n");
                break;
            case ADD:
                fprintf(pf,"lw $t1,8($sp) #ADD BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"add $t0,$t1,$t2\n");
                fprintf(pf,"sw $t0,($sp)\n");
                fprintf(pf,"addi $sp,$sp,-4 #ADD END\n");
                break;
            case MINUS:
                fprintf(pf,"lw $t1,8($sp) #MINUS BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"sub $t0,$t1,$t2\n");
                fprintf(pf,"sw $t0,($sp)\n");
                fprintf(pf,"addi $sp,$sp,-4 #MINUS END\n");
                break;
            case MUL:
                fprintf(pf,"lw $t1,8($sp) #MUL BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"mul $t0,$t1,$t2\n");
                fprintf(pf,"sw $t0,($sp)\n");
                fprintf(pf,"addi $sp,$sp,-4 #MUL END\n");
                break;
            case DIV:
                fprintf(pf,"lw $t1,8($sp) #DIV BEGIN\n");
                fprintf(pf,"lw $t2,4($sp)\n");
                fprintf(pf,"addi $sp,$sp,8\n");
                fprintf(pf,"div $t1,$t2\n");
                fprintf(pf,"mflo $t0\n");
                fprintf(pf,"sw $t0,($sp)\n");
                fprintf(pf,"addi $sp,$sp,-4 #DIV END\n");
                break;
            case UMINUS_NO:
                fprintf(pf,"lw $t1,4($sp) #UMINUS BEGIN\n");
                fprintf(pf,"addi $sp,$sp,4\n");
                fprintf(pf,"sub $t0,$zero,$t1\n");
                fprintf(pf,"sw $t0,($sp)\n");
                fprintf(pf,"addi $sp,$sp,-4 #UMINUS END\n");
                break;
            case NOT: 
                fprintf(pf,"lw $t1,4($sp) #NOT BEGIN\n");
                fprintf(pf,"addi $sp,$sp,4\n");
                fprintf(pf,"beq $t1,$zero,LABEL%d:\n",num=newlabel());
                fprintf(pf,"sw $zero,($sp)\n");
                fprintf(pf,"j LABEL%d\n",end_num=newlabel());
                fprintf(pf,"LABEL%d:\n",num);
                fprintf(pf,"addi $t1,$zero,1\n");
                fprintf(pf,"sw $t1,($sp)\n");
                fprintf(pf,"LABEL%d:\n");
                fprintf(pf,"addi $sp,$sp,-4 #NOT END\n");
                break;
            case CHAR_NO:
                fprintf(pf,"addi $t0,$zero,%d #CHAR BEGIN\n",h->var.size);
                fprintf(pf,"sw $t0,($sp)\n");
                fprintf(pf,"addi $sp,$sp,-4 #CHAR END\n");
                break;
            case INT_NO: 
                fprintf(pf,"addi $t0,$zero,%d #INT BEGIN\n",h->var.size);
                fprintf(pf,"sw $t0,($sp)\n");
                fprintf(pf,"addi $sp,$sp,-4 #INT END\n");
                break;
            case ID_NO:
                fprintf(pf,"lw $t0,-%d($fp) #ID_NO BEGIN\n",h->var.addr);
                fprintf(pf,"sw $t0,($sp)\n");
                fprintf(pf,"addi $sp,$sp,-4 #ID_NO END\n");
                break;
            case FUN_PUBLIC:
                fprintf(pf,"addi $sp,$sp,-12 #FUN_PUBLIC BEGIN\n");
                fprintf(pf,"sw $ra,8($sp)\n");
                // fprintf(pf,"lw $t1,($fp)\n");
                fprintf(pf,"sw $fp,4($sp) #FUN_PUBLIC END\n");
                break;
            case FUN_CALL:
                fprintf(pf,"addi $fp,$sp,%d #FUN_CALL BEGIN\n",h->var.paranum);
                size = symtab[lookup(h->name)].size;
                fprintf(pf,"addi $sp,$fp,-%d\n",size);
                fprintf(pf,"jal %s #FUN_CALL END\n",h->name);
                break;
            default:
                printf("UNKOWN NODE!%d\n",h->op);
        }
        h=h->next;
    }
}