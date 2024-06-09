#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

// Declaración de funciones de la tabla de simbolos
void iniciarTablaSimbolos();
void cerrarTablaSimbolos();
void anadirVariable(char *lexema, double valor);
unsigned esVariable(char *lexema);
unsigned esConstante(char *lexema);
unsigned esFuncion(char *lexema);
double obtenerVariableConstante(char *lexema);
double ejecutarFuncion(char *lexema, double val);
double ejecutarFuncion2(char *lexema, double val1, double val2);
void imprimirTablaSimbolos();
void imprimirTablaSimbolosVariables();
void limpiarVariables();
void verFunciones(); 
#endif // TABLASIMBOLOS_H
