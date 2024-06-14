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
void imprimirTablaSimbolos();
void imprimirWorkspace();
void imprimirTablaSimbolosVariables();
void limpiarVariables();
void verFunciones(); 

#endif // TABLASIMBOLOS_H
