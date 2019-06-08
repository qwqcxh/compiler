#include "mc.h"

void printcode(ast* node){
    code* h=node->pcode;
    while(h){
        switch(h->op){
            case LABEL:
                printf("%s",h->name);break;
            case RETURN_OP:
                printf("RETURN\n");break;
            case GOTO_BREAK:
                printf("GOTO LABEL%d\n",h->end_label_num);break;
            case GOTO_UPDATE:
                printf("GOTO LABEL%d\n",h->update_label_num);break;
            case JUDGE:
                printf("IF BOOLEAN IS FALSE GOTO LABEL%d\n",h->end_label_num);break;
            case GOTO_JUDGE:
                printf("GOTO LABEL%d\n",h->judge_label_num);break;
            case ASSIGN_OP:
                printf("%s = VALUE_IN_STACK\n",h->name);break;
            case AND_NO:
                printf("var1 && var2 \n");break;
            case OR_NO:
                printf("var1 || var2 \n");break;
            case GR_NO:
                printf("var1 > var2 \n");break;
            case LS_NO:
                printf("var1 < var2 \n");break;
            case GE_NO:
                printf("var1 >= var2 \n");break;
            case LE_NO:
                printf("var1 <= var2 \n");break;
            case EQ_NO:
                printf("var1 == var2 \n"); break;
            case NE_NO:
                printf("var1 != var2 \n");break;
            case ADD:
                printf("var1 + var2 \n");break;
            case MINUS:
                printf("var1 - var2 \n");break;
            case MUL:
                printf("var1 * var2 \n");break;
            case DIV:
                printf("var1 / var2 \n");break;
            case UMINUS_NO:
                printf("-var1 \n");break;
            case NOT: 
                printf("!var1 \n");break;
            case CHAR_NO:
                printf("value is %c \n",h->var.size);break;
            case INT_NO: 
                printf("value is %d \n",h->var.size);break;
            case ID_NO:
                printf("value is %s\n",h->name);break;
            case FUN_PUBLIC:
                printf("PUBLIC OPERATION OF FUNCTIOIN CALL\n");break;
            case FUN_CALL:
                printf("call %s\n",h->name);break;
            default:
                printf("UNKOWN NODE!%d\n",h->op);
        }
        h=h->next;
    }
}