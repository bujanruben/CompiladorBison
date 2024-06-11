#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

// Definicion de los datos del elemento variable
union Valor
{
    double num;
    double (*funcion)();
};

typedef union Valor valor;

// Definicion del elemento variable del arbol
typedef struct
{
    valor data;
    char *lexema;
    int tipo;
} variable;

typedef struct celda *abb;

void crearArbol(abb *arbol);
void destruir(abb *arbol);
unsigned arbolVacio(abb arbol);
abb devolverIzquierda(abb arbol);
abb devolverDerecha(abb arbol);
void insertarFuncion(abb *arbol, char *lexema, double (*funcion)());
void insertarVariable(abb *arbol, char *lexema, double val);
void insertarConstante(abb *arbol, char *lexema, double val);
int buscarLexema(abb arbol, char *lexema);
int existeVariable(abb arbol, char *lexema);
int existeConstante(abb arbol, char *lexema);
int existeFuncion(abb arbol, char *lexema);
double buscarVariableConstante(abb arbol, char *lexema);
double buscarFuncion(abb arbol, char *lexema, double val);
void mostrarArbol(abb arbol);
void imprimirArbolVariables(abb *arbol);
void eliminarVariables(abb *arbol);
void eliminarNodo(abb *arbol);
void eliminarComponente(variable *variable);

#endif // ARBOLBINARIO_H
