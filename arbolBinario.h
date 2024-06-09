#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

// DEFINICIÓN DEL VALOR DE LOS ELEMENTOS DEL ÁRBOL
union Valor
{
    double num;
    double (*funcion)();
};

typedef union Valor valor;

// DEFINICIÓN DE LOS ELEMENTOS DEL ÁRBOL
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
double buscarFuncion2(abb arbol, char *lexema, double val1, double val2);

void mostrarArbol(abb arbol);
void imprimirArbolVariables(abb *arbol);
void eliminarVariables(abb *arbol);
void eliminarNodo(abb *arbol);
void eliminarComponente(variable *variable);

#endif // ARBOLBINARIO_H
