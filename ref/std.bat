flex lex.l
bison -d parser.y
gcc lex.yy.c parser.tab.c ast.c seman.c -o std.exe -lfl