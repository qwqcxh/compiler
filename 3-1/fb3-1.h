extern int yylineno; //from lex file
void yyerror(char*s,...);

struct ast{ //ast node
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct numval{
    int nodetype;
    double number;
};

//construct ast 
struct ast *newast(int nodetype,struct ast*l,struct ast*r);
struct ast *newnum(double d);

//calculate ast
double eval(struct ast* s);

//delete ast
void treefree(struct ast* s);