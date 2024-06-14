flex analisisLexico.l
bison -d analisisSintactico.y
gcc -Wall *.c -o calculadora -lfl -lm