%{
#include <string.h>
#include "definiciones.h"
#include "tablaSimbolos.h"
#include "analisisSemantico.tab.h"
#include "lex.yy.h"

void leerArchivo(char *nombre);
void cerrarArchivo();
%}

%option noyywrap
%option yylineno
%option noinput nounput
/* Definicion de expresiones regulares */

NEWLINE \n
DIGITO [0-9]
LETRA [a-zA-Z]
BARRABAJA [_]
IDENTIFICADOR ({LETRA}|{BARRABAJA})({LETRA}|{DIGITO}|{BARRABAJA})*

DIGITOPARTE {DIGITO}(_?{DIGITO})*
FRACCION \.{DIGITOPARTE}
EXPONENTE [eE][+-]?{DIGITOPARTE}

/* Definicion de los numeros */
NUMERO_ENTERO {DIGITO}+
NUMERO_FLOTANTE ({DIGITOPARTE}?{FRACCION}|{DIGITOPARTE}\.)({EXPONENTE})?|{DIGITOPARTE}{EXPONENTE}
NUMERO {NUMERO_ENTERO}|{NUMERO_FLOTANTE}

ARCHIVO {IDENTIFICADOR}\.{LETRA}+ 
/* archivo.c, archivo.md, archivo.txt...*/

/* Definiciones de las funciones de la calculadora */
FUNCIONES   ("sin"|"cos"|"tan"|"sec"|"cosec"|"cotan"|"pow"|"sqrt"|"log"|"ln"|"exp")

OPERADORES (\+|\-|\*|\/|\^|\%|\(|\)|\;|\=)
MAS_IGUAL   \+=
MENOS_IGUAL \-=
POR_IGUAL   \*=
DIVISION_IGUAL  \/=
MAS_MAS \+\+
MENOS_MENOS \-\-


/* Definicion de las reglas segun los automatas de las expresiones regulares */
%%

[ \t\r]+ {}

"LOAD" return (TOKEN_LOAD);
"HELP" return (TOKEN_HELP);
"QUIT" return (TOKEN_QUIT);
"WORKSPACE" return (TOKEN_WORKSPACE);
"CLEAR" return (TOKEN_CLEAR);
"ECHO" return(TOKEN_ECHO);
"ON" return (ON);
"OFF" return (OFF);

{FUNCIONES} { yylval.str = strdup(yytext); return (TOKEN_FUNCIONES);}

{NEWLINE}  {return ((int)*yytext);}
{NUMERO} {  yylval.val=atof(yytext);
            return (TOKEN_NUMERO);}

{IDENTIFICADOR} {   yylval.str = strdup(yytext);
                    return (TOKEN_IDENTIFICADOR);}

{ARCHIVO} { yylval.str = strdup(yytext);
            return (TOKEN_ARCHIVO); 
}


{OPERADORES}        {return ((int)*yytext);}
{MAS_IGUAL}         {return (TOKEN_MAS_IGUAL);}
{MENOS_IGUAL}       {return (TOKEN_MENOS_IGUAL);}
{POR_IGUAL}         {return (TOKEN_POR_IGUAL);}
{DIVISION_IGUAL}    {return (TOKEN_DIVIDIDO_IGUAL);}
{MAS_MAS}           {return (TOKEN_MAS_MAS);}
{MENOS_MENOS}       {return (TOKEN_MENOS_MENOS);}


. {printf("ERROR");}

<<EOF>>     {cerrarArchivo();yyrestart(stdin); return (0);}

%%

void leerArchivo(char *nombre){
    yyin = fopen(nombre, "r");
    if(yyin == NULL){
        fprintf(stderr, "Error al abrir el archivo: %s\n", nombre);
        yyin = stdin;
    }
}

void cerrarArchivo(){
    if (yyin != stdin) {
        fclose(yyin);
    }
    yyin = NULL;
}
