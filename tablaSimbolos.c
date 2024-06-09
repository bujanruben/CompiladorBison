#include "arbolBinario.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "definiciones.h"
#include "tablaSimbolos.h"

// Arbol binario de busqueda para la tabla de simbolos
abb tablaSimbolos;

// FUNCION DE INICIALIZACION DE LA TABLA DE SIMBOLOS
void iniciarTablaSimbolos()
{
    crearArbol(&tablaSimbolos);
    insertarConstante(&tablaSimbolos, "PI", NUM_PI);
    insertarConstante(&tablaSimbolos, "E", NUM_E);
    insertarFuncion(&tablaSimbolos, "sin", sin);
    insertarFuncion(&tablaSimbolos, "cos", cos);
    insertarFuncion(&tablaSimbolos, "tan", tan);
    insertarFuncion(&tablaSimbolos, "sec", asin);
    insertarFuncion(&tablaSimbolos, "cosec", acos);
    insertarFuncion(&tablaSimbolos, "cotan", atan);
    insertarFuncion(&tablaSimbolos, "pow", pow);
    insertarFuncion(&tablaSimbolos, "sqrt", sqrt);
    insertarFuncion(&tablaSimbolos, "log", log);
    insertarFuncion(&tablaSimbolos, "ln", log10);
    insertarFuncion(&tablaSimbolos, "exp", exp);
}

// FUNCION DE DESTRUCCION DE LA TABLA DE SIMBOLOS
void cerrarTablaSimbolos()
{
    destruir(&tablaSimbolos);
}

// FUNCION QUE INSERTA UNA VARIABLE EN LA TABLA DE SIMBOLOS
void anadirVariable(char *lexema, double valor)
{
    insertarVariable(&tablaSimbolos, lexema, valor);
}

// FUNCION QUE BUSCA SI UNA VARIABLE YA EXISTE EN LA TABLA DE SIMBOLOS
unsigned esVariable(char *lexema)
{
    return existeVariable(tablaSimbolos, lexema);
}

// FUNCION QUE BUSCA SI UNA CONSTANTE YA EXISTE EN LA TABLA DE SIMBOLOS
unsigned esConstante(char *lexema)
{
    return existeConstante(tablaSimbolos, lexema);
}

// FUNCION QUE BUSCA SI UNA FUNCION YA EXISTE EN LA TABLA DE SIMBOLOS
unsigned esFuncion(char *lexema)
{
    return existeFuncion(tablaSimbolos, lexema);
}

// FUNCION QUE BUSCA UNA VARIABLE O CONSTANTE EN LA TABLA DE SIMBOLOS
double obtenerVariableConstante(char *lexema)
{
    return buscarVariableConstante(tablaSimbolos, lexema);
}

// FUNCION QUE BUSCA UNA FUNCION EN LA TABLA DE SIMBOLOS
double ejecutarFuncion(char *lexema, double val)
{
    return buscarFuncion(tablaSimbolos, lexema, val);
}

// FUNCION QUE BUSCA UNA FUNCION CON DOS PARÁMETROS EN LA TABLA DE SIMBOLOS
double ejecutarFuncion2(char *lexema, double val1, double val2)
{
    return buscarFuncion2(tablaSimbolos, lexema, val1, val2);
}

// FUNCION QUE IMPRIME LA TABLA DE SIMBOLOS
void imprimirTablaSimbolos()
{
    printf("\nTABLA DE SIMBOLOS\n----------------\n");
    mostrarArbol(tablaSimbolos);
    printf("----------------\n");
}

// FUNCION QUE IMPRIME LA TABLA DE SIMBOLOS DE VARIABLES
void imprimirTablaSimbolosVariables()
{
    imprimirArbolVariables(&tablaSimbolos);
}

// FUNCION QUE LIMPIA LA TABLA DE SIMBOLOS DE VARIABLES
void limpiarVariables()
{
    eliminarVariables(&tablaSimbolos);
}

void imprimirAyuda(){
    printf("*****************AYUDA******************\n****************************************\n");

    printf("\n--------------IMPRESION--------------\n");
    printf("Las operaciones con ; al final o con la opción de ECHO OFF no se imprimirán.\nActivando ECHO ON se volverá a activar la opción de imprimir\n");

    printf("\n--------------NÚMEROS--------------\n");
    printf("Se cuenta con la opción de operar con números decimales y flotantes\n");

    printf("\n--------------VARIABLES--------------\n");
    printf("Puedes introducir variables con las que operar. \nEjemplo: >x=1 (Esto guardará en el workspace la variable x con valor 1)\nNo se puede utilizar las palabras reservadas (OPERADORES, CONSTANTES, FUNCIONES Y COMANDOS)\n");
    printf("\n--------------VARIABLES CONSTANTES--------------\n");
    printf("PI = 3.14159265\n");
    printf("E = 2.71828182\n");

    printf("\n--------------OPERADORES--------------\n");
    printf("Operadores de suma (+), resta (-), multiplicación (*) y división (/): NUMERO op NUMERO\n");
    printf("Operadores de exponente (^) y módulo (%%): NUMERO op NUMERO\n");
    printf("Uso de parentesis () para prioridad y uso de = para igualdades: VARIABLE = OPERACION/NUMERO/VARIABLE\n");
    printf("Operadores de incremento (++) y drecremento (--): VARIABLE op\n");
    printf("Operadores de asignación compuesta (+= -= *= /=): VARIABLE op OPERACION/NUMERO/VARIABLE\n");


    printf("\n--------------FUNCIONES--------------\n");
    printf("sin(NUMERO) -seno del número\ncos(NUMERO) -coseno del número\ntan(NUMERO) -tangente del número\n");
    printf("sec(NUMERO) -secante del número\ncosec(NUMERO) -cosecante del número\ncotan(NUMERO) -contangente del número\n");
    //printf("pow(NUMERO) -secante del número\nsqrt(NUMERO) -raíz cuadrada del número\nlog(NUMERO) -logaritmo en base 10 del número\nln(NUMERO) -logaritmo neperiano del número\nexp(NUMERO) -el numero de euler elevado al número\n\n");

    printf("\n--------------COMANDOS--------------\n");
    printf("WORKSPACE -Imprime las variables guardadas en la tabla de simbolos.\n");
    printf("CLEAR -Limpia el workspace.\n");
    printf("HELP -Muestra información de ayuda.\n");
    printf("ECHO ON -Activa la impresión de resultados.\n");
    printf("ECHO OFF -Desactiva la impresión de resultados.\n");
    //printf("LOAD archivo -Abre y ejecuta las filas del archivo\n");
    printf("QUIT -Cierra la calculadora\n\n");

    printf("**************FIN DE AYUDA**************\n****************************************\n");
}
void verFunciones() {
    printf("Funciones disponibles:\n");
    printf("sin, cos, tan, sec, cosec, cotan, pow, sqrt, log, ln, exp\n");
}