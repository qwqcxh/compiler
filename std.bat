flex lex.l
bison -d parser.y
gcc lex.yy.c parser.tab.c ast.c -o std.exe -lfl