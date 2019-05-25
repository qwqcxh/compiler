bison -d mc.y
flex  mc.l
gcc -o mc.exe mc.tab.c lex.yy.c syntax.c -lfl