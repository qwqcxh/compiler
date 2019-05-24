extern int yylineno;
void yyerror(char* s,...);

struct symbol {
    char * name; //变量名
    double value; //变量值
    struct ast *func; //函数体
    struct symlist *syms; //虚拟参数
};

#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(char*);

struct symlist{
    struct symbol *sym;
    struct symlist * next;
};

struct symlist *newsymlist(struct symbol*sym,struct symlist*next);
void symlistfree(struct symlist*s1);

/* 节点类型
 * + - * / |
 * 0-7 比较操作符，位编码：04 等于，02小于，01大于
 * M 单目负号
 * L 表达式或者语句列表
 * I IF 语句
 * W while 语句
 * N 符号引用
 * = 赋值
 * S 符号列表
 * F 内置函数调用
 * C 用户函数调用
 */
enum bifs{ //内置函数
    B_sqrt=1,
    B_exp,
    B_log,
    B_print
};

struct ast{
    int nodetype;
    struct ast*l;
    struct ast*r;
};

struct fncall{
    int nodetype; //类型F
    struct ast*l;
    enum bifs functype;
};

struct ufncall{
    int nodetype; //C
    struct ast* l;
    struct symbol*s;
};

struct flow{
    int nodetype; //I或者W
    struct ast* cond; //条件
    struct ast* tl; //then 或者 do 语句
    struct ast* el; //可选else分支
};

struct numval{
    int nodetype; //K
    double number;
};

struct symref{
    int nodetype; //N
    struct symbol *s;
};

struct symasgn{
    int nodetype; //=
    struct symbol *s;
    struct ast *v; //值
};

struct ast* newast(int nodetype,struct ast*l,struct ast*r);
struct ast* newcmp(int cmptype,struct ast *l,struct ast*r);
struct ast* newfunc(int functuype,struct ast*l);
struct ast* newcall(struct symbol*s,struct ast*l);
struct ast* newref(struct symbol*s);
struct ast* newasgn(struct symbol*s,struct ast*v);
struct ast* newnum(double d);
struct ast* newflow(int nodetype,struct ast* cond,struct ast*tl,struct ast* tr);

void dodef(struct symbol *name,struct symlist*syms,struct ast *stmts);
double  eval(struct ast*);

void treefree(struct ast*);
