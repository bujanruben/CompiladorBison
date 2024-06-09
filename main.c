#include <stdio.h>
#include <stdlib.h>
#include "tablaSimbolos.h"
#include "lex.yy.h"
#include "analisisSemantico.tab.h"

int main(int argc, char **argv)
{

    printf("\n*****************CALCULADORA BISON*****************\n\n");
    printf("Esta calculadora permite ejecutar operaciones aritmeticas así como funciones matemáticas:\n(sin, cos, tan, sec, cosec, cotan, pow, sqrt, log, ln, exp)\n");
    printf("Permite el uso de variables para almacenar valores\n");
    printf("También se cuenta con comandos internos:\nECHO ON, ECHO OFF,HELP,QUIT,WORKSPACE,CLEAR,LOAD()\n");
    printf("Para más información escriba HELP\n");
    printf("Para salir escriba QUIT\n\n***************************************************\n");
    iniciarTablaSimbolos();

    if (argc == 2)
    {
        leerArchivo(argv[1]);
    }

    yyparse();

    cerrarTablaSimbolos();
    return EXIT_SUCCESS;
}