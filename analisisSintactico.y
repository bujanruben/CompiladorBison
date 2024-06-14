%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lex.yy.h"
#include "definiciones.h"
#include "tablaSimbolos.h"

extern int yylex();
void yyerror(const char *s);
void echoOff();
void echoOn();
void ayuda();
void verFunciones();

int echo = 1;
%}

%union {
    double val;
    char *str;
}

%start start

%token <val> TOKEN_NUMERO
%token <str> TOKEN_IDENTIFICADOR
%token <str> TOKEN_ARCHIVO
%token <str> TOKEN_FUNCIONES

%token TOKEN_MAS_IGUAL
%token TOKEN_MENOS_IGUAL
%token TOKEN_POR_IGUAL
%token TOKEN_DIVIDIDO_IGUAL
%token TOKEN_MAS_MAS
%token TOKEN_MENOS_MENOS
%token TOKEN_EOF
%token TOKEN_ERROR
%token TOKEN_CLEAR
%token TOKEN_QUIT
%token TOKEN_HELP
%token TOKEN_WORKSPACE
%token TOKEN_ECHO
%token ON OFF
%token TOKEN_LOAD

%type <val> EXPRESION
%type <str> COMANDO
%type <val> ASIGNACION

%left '-' '+' TOKEN_MAS_IGUAL TOKEN_MENOS_IGUAL
%left '*' '/' TOKEN_POR_IGUAL TOKEN_DIVIDIDO_IGUAL
%left NEG
%right '^'

%%

start
    : INICIO
    | start INICIO
    ;

INICIO
    : '\n'
    | EXPRESION '\n' {
        mostrarResultado($1);
    }
    | COMANDO '\n'
    | ASIGNACION '\n' {
        mostrarResultado($1);
    }
    | EXPRESION ';' '\n'
    | ASIGNACION ';' '\n'
    | TOKEN_HELP {imprimirAyuda();}      
    | TOKEN_WORKSPACE {imprimirTablaSimbolos();}   
    | TOKEN_CLEAR {limpiarVariables();}    
    | TOKEN_ECHO ON {
        echoOn(); 
        printf("-> ECHO ACTIVADO\n");
        }
    | TOKEN_ECHO OFF {
        echoOff(); 
        printf("-> ECHO DESACTIVADO\n");
        }
    | TOKEN_LOAD TOKEN_ARCHIVO {leerArchivo($2); }
    | TOKEN_QUIT {
        printf("-> Saliendo...\n");
        exit(0);
        }     

    | error {
        yyerror("ERROR: Error de sintaxis");
    }
    ;

EXPRESION
    : TOKEN_NUMERO { $$ = $1; }
    | TOKEN_IDENTIFICADOR {
        if (esVariable($1) || esConstante($1)) {
            $$ = obtenerVariableConstante($1);
        } else {
            yyerror("ERROR: La variable a utilizar no existe ni es una constante o función.");
            $$ = NAN;
        }
        free($1);
    }
    | EXPRESION '+' EXPRESION { $$ = $1 + $3; }
    | EXPRESION '-' EXPRESION { $$ = $1 - $3; }
    | EXPRESION '*' EXPRESION { $$ = $1 * $3; }
    | EXPRESION '/' EXPRESION {
        if ($3 == 0) {
            yyerror("ERROR: División por cero.");
            $$ = NAN;
        } else {
            $$ = $1 / $3;
        }
    }
    | '-' EXPRESION %prec NEG { $$ = -$2; }
    | EXPRESION '^' EXPRESION { $$ = pow($1, $3); }
    | '(' EXPRESION ')' { $$ = $2; }
    | TOKEN_IDENTIFICADOR TOKEN_MAS_MAS {
        if (esVariable($1)) {
            $$ = obtenerVariableConstante($1) + 1;
            anadirVariable($1, $$);
        } else {
            yyerror("ERROR: Variable no existente.");
            $$ = NAN;
        }
        free($1);
    }
    | TOKEN_IDENTIFICADOR TOKEN_MENOS_MENOS {
        if (esVariable($1)) {
            $$ = obtenerVariableConstante($1) - 1;
            anadirVariable($1, $$);
        } else {
            yyerror("ERROR: Variable no existente.");
            $$ = NAN;
        }
        free($1);
    }
    | TOKEN_IDENTIFICADOR TOKEN_MAS_IGUAL EXPRESION {
        if (esVariable($1)) {
            $$ = obtenerVariableConstante($1) + $3;
            anadirVariable($1, $$);
        } else {
            yyerror("ERROR: Variable no existente.");
            $$ = NAN;
        }
        free($1);
    }
    | TOKEN_IDENTIFICADOR TOKEN_MENOS_IGUAL EXPRESION {
        if (esVariable($1)) {
            $$ = obtenerVariableConstante($1) - $3;
            anadirVariable($1, $$);
        } else {
            yyerror("ERROR: Variable no existente.");
            $$ = NAN;
        }
        free($1);
    }
    | TOKEN_IDENTIFICADOR TOKEN_POR_IGUAL EXPRESION {
        if (esVariable($1)) {
            $$ = obtenerVariableConstante($1) * $3;
            anadirVariable($1, $$);
        } else {
            yyerror("ERROR: Variable no existente.");
            $$ = NAN;
        }
        free($1);
    }
    | TOKEN_IDENTIFICADOR TOKEN_DIVIDIDO_IGUAL EXPRESION {
        if (esVariable($1)) {
            if ($3 == 0) {
                yyerror("ERROR: División por cero.");
                $$ = NAN;
            } else {
                $$ = obtenerVariableConstante($1) / $3;
                anadirVariable($1, $$);
            }
        } else {
            yyerror("ERROR: Variable no existente.");
            $$ = NAN;
        }
        free($1);
    }    
    | TOKEN_FUNCIONES '(' EXPRESION ')' {
        if (esFuncion($1)) {
            $$ = ejecutarFuncion($1, $3);
        } else {
            yyerror("ERROR: Función no existente.");
            verFunciones();
            $$ = NAN;
        }
        free($1);
    }
    ;

COMANDO
    : TOKEN_EOF {
        cerrarArchivo();
    }
    | TOKEN_ERROR {
        yyerror("ERROR: Lexema mal formado.");
    }
    ;

ASIGNACION
    : TOKEN_IDENTIFICADOR '=' EXPRESION {
        if (!esConstante($1)) {
            anadirVariable($1, $3);
            $$ = $3;
        } else {
            yyerror("ERROR: No se puede modificar una constante.");
            $$ = NAN;
        }
        free($1);
    }
    | TOKEN_IDENTIFICADOR '=' COMANDO {
        yyerror("ERROR: Asignación no válida a un comando.");
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

void mostrarResultado(double valor) {
    if (echo && !isnan(valor)) {
        printf("-> %g\n", valor);
    }
}

void echoOff() {
    echo = 0;
}

void echoOn() {
    echo = 1;
}
