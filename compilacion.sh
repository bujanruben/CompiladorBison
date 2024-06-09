flex analisisLexico.l
bison -d analisisSemantico.y
gcc -Wall *.c -o calculadora -lfl -lm