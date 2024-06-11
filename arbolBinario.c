#include "arbolBinario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"

// Estructura de arbol binario (Arbol sobre rama recursiva con dos ramas izquierda y derecha, junto a variable y tipo de variable
struct celda
{
    variable info;
    int tipo;
    struct celda *izquierda, *derecha;
};

// crea un arbol vacio
void crearArbol(abb *arbol)
{
    *arbol = NULL;
}

// elimina una hoja del arbol
void eliminarComponente(variable *variable)
{
    if (variable->lexema != NULL)
    {
        free(variable->lexema);
        variable->lexema = NULL;
    }
}

// elimina el arbol
void destruir(abb *arbol)
{
    if (*arbol != NULL)
    {
        destruir(&(*arbol)->izquierda);
        destruir(&(*arbol)->derecha);
        eliminarComponente(&(*arbol)->info);
        free(*arbol);
        *arbol = NULL;
    }
}

// comprueba si el arbol está vacio
unsigned arbolVacio(abb arbol)
{
    return arbol == NULL;
}

// devuelve la rama izquierda
abb devolverIzquierda(abb arbol)
{
    return arbol->izquierda;
}

// devuelve la rama derecha
abb devolverDerecha(abb arbol)
{
    return arbol->derecha;
}

// inserta una función en el árbol
void insertarFuncion(abb *arbol, char *lexema, double (*funcion)())
{
    if (arbolVacio(*arbol))
    {
        *arbol = (abb)malloc(sizeof(struct celda));
        (*arbol)->info.lexema = (char *)malloc(strlen(lexema) + 1);
        strcpy((*arbol)->info.lexema, lexema);
        (*arbol)->info.data.funcion = funcion;
        (*arbol)->tipo = ID_FUNCION;
        (*arbol)->izquierda = NULL;
        (*arbol)->derecha = NULL;
        return;
    }

    int comparacion = strcmp(lexema, (*arbol)->info.lexema);
    if (comparacion > 0)
    {
        insertarFuncion(&(*arbol)->derecha, lexema, funcion);
    }
    else if (comparacion < 0)
    {
        insertarFuncion(&(*arbol)->izquierda, lexema, funcion);
    }
    else
    {
        (*arbol)->info.data.funcion = funcion;
    }
}

// inserta una variable en el árbol
void insertarVariable(abb *arbol, char *lexema, double val)
{
    if (arbolVacio(*arbol))
    {
        *arbol = (abb)malloc(sizeof(struct celda));
        (*arbol)->info.lexema = (char *)malloc(strlen(lexema) + 1);
        strcpy((*arbol)->info.lexema, lexema);
        (*arbol)->info.data.num = val;
        (*arbol)->tipo = ID_VARIABLE;
        (*arbol)->izquierda = NULL;
        (*arbol)->derecha = NULL;
        return;
    }

    int comparacion = strcmp(lexema, (*arbol)->info.lexema);
    if (comparacion > 0)
    {
        insertarVariable(&(*arbol)->derecha, lexema, val);
    }
    else if (comparacion < 0)
    {
        insertarVariable(&(*arbol)->izquierda, lexema, val);
    }
    else
    {
        (*arbol)->info.data.num = val;
    }
}

// inserta una constante en el árbol
void insertarConstante(abb *arbol, char *lexema, double val)
{
    if (arbolVacio(*arbol))
    {
        *arbol = (abb)malloc(sizeof(struct celda));
        (*arbol)->info.lexema = (char *)malloc(strlen(lexema) + 1);
        strcpy((*arbol)->info.lexema, lexema);
        (*arbol)->info.data.num = val;
        (*arbol)->tipo = ID_CONSTANTE;
        (*arbol)->izquierda = NULL;
        (*arbol)->derecha = NULL;
        return;
    }

    int comparacion = strcmp(lexema, (*arbol)->info.lexema);
    if (comparacion > 0)
    {
        insertarConstante(&(*arbol)->derecha, lexema, val);
    }
    else if (comparacion < 0)
    {
        insertarConstante(&(*arbol)->izquierda, lexema, val);
    }
    else
    {
        (*arbol)->info.data.num = val;
    }
}

// busca un lexema en el árbol
int buscarLexema(abb arbol, char *lexema)
{
    if (arbolVacio(arbol))
    {
        return 0;
    }
    int comparacion = strcmp(lexema, arbol->info.lexema);
    if (comparacion == 0)
    {
        return 1;
    }
    else if (comparacion > 0)
    {
        return buscarLexema(arbol->derecha, lexema);
    }
    else
    {
        return buscarLexema(arbol->izquierda, lexema);
    }
}

// busca una variable en el árbol
int existeVariable(abb arbol, char *lexema)
{
    if (arbolVacio(arbol))
    {
        return 0;
    }

    int comparacion = strcmp(lexema, arbol->info.lexema);
    if (comparacion == 0)
    {
        return arbol->tipo == ID_VARIABLE;
    }
    else if (comparacion < 0)
    {
        return existeVariable(arbol->izquierda, lexema);
    }
    else
    {
        return existeVariable(arbol->derecha, lexema);
    }
}

// busca una constante en el árbol
int existeConstante(abb arbol, char *lexema)
{
    if (arbolVacio(arbol))
    {
        return 0;
    }

    int comparacion = strcmp(lexema, arbol->info.lexema);
    if (comparacion == 0)
    {
        return arbol->tipo == ID_CONSTANTE;
    }
    else if (comparacion < 0)
    {
        return existeConstante(arbol->izquierda, lexema);
    }
    else
    {
        return existeConstante(arbol->derecha, lexema);
    }
}

// busca una función en el árbol
int existeFuncion(abb arbol, char *lexema)
{
    if (arbolVacio(arbol))
    {
        return 0;
    }

    int comparacion = strcmp(lexema, arbol->info.lexema);
    if (comparacion == 0)
    {
        return arbol->tipo == ID_FUNCION;
    }
    else if (comparacion < 0)
    {
        return existeFuncion(arbol->izquierda, lexema);
    }
    else
    {
        return existeFuncion(arbol->derecha, lexema);
    }
}

// busca una variable o constante en el árbol y devuelve su valor
double buscarVariableConstante(abb arbol, char *lexema)
{
    int comparacion = strcmp(lexema, arbol->info.lexema);
    if (comparacion == 0)
    {
        return arbol->info.data.num;
    }
    else if (comparacion < 0)
    {
        return buscarVariableConstante(arbol->izquierda, lexema);
    }
    else
    {
        return buscarVariableConstante(arbol->derecha, lexema);
    }
}

// busca una función en el árbol y la ejecuta (1 parámetro)
double buscarFuncion(abb arbol, char *lexema, double val)
{
    int comparacion = strcmp(lexema, arbol->info.lexema);
    if (comparacion == 0)
    {
        return arbol->info.data.funcion(val);
    }
    else if (comparacion < 0)
    {
        return buscarFuncion(arbol->izquierda, lexema, val);
    }
    else
    {
        return buscarFuncion(arbol->derecha, lexema, val);
    }
}



// muestra el nodo
void mostrarNodo(abb arbol)
{
    if (arbol->tipo == ID_VARIABLE)
    {
        printf("Variable: %s\n", arbol->info.lexema);

        printf("Valor: %f\n\n", arbol->info.data.num);
    }
    else if (arbol->tipo == ID_CONSTANTE)
    {
        printf("Constante: %s\n", arbol->info.lexema);
        printf("Valor: %f\n\n", arbol->info.data.num);
    }
    else if (arbol->tipo == ID_FUNCION)
    {
        printf("Función: %s\n", arbol->info.lexema);
        printf("Categoría: Función\n\n");
    }
}


// muestra el arbol entero de forma ordenada
void mostrarArbol(abb arbol)
{
    if (!arbolVacio(arbol))
    {
        mostrarArbol(devolverIzquierda(arbol));
        mostrarNodo(arbol);
        mostrarArbol(devolverDerecha(arbol));
    }
}

// muestra el árbol de variables
void imprimirArbolVariables(abb *arbol)
{
    if (!arbolVacio(*arbol))
    {
        if ((*arbol)->izquierda != NULL)
        {
            imprimirArbolVariables(&(*arbol)->izquierda);
        }

        if ((*arbol)->tipo == ID_VARIABLE)
        {
            mostrarNodo(*arbol);
        }

        if ((*arbol)->derecha != NULL)
        {
            imprimirArbolVariables(&(*arbol)->derecha);
        }
    }
}

// elimina un nodo del árbol y conserva sus descendientes
void eliminarNodo(abb *arbol)
{
    if (*arbol == NULL)
    {
        return;
    }
    if ((*arbol)->izquierda == NULL && (*arbol)->derecha == NULL)
    {
        free((*arbol)->info.lexema);
        free(*arbol);
        *arbol = NULL;
    }
    else if ((*arbol)->izquierda == NULL)
    {
        abb aux = *arbol;
        *arbol = (*arbol)->derecha;
        free(aux->info.lexema);
        free(aux);
    }
    else if ((*arbol)->derecha == NULL)
    {
        abb aux = *arbol;
        *arbol = (*arbol)->izquierda;
        free(aux->info.lexema);
        free(aux);
    }
    else
    {
        abb aux = (*arbol)->derecha;
        while (aux->izquierda != NULL)
        {
            aux = aux->izquierda;
        }
        free((*arbol)->info.lexema);
        (*arbol)->info.lexema = strdup(aux->info.lexema);
        (*arbol)->info.data = aux->info.data;
        eliminarNodo(&(*arbol)->derecha);
    }
}

// elimina todas las variables del árbol
void eliminarVariables(abb *arbol)
{
    if (!arbolVacio(*arbol))
    {
        eliminarVariables(&(*arbol)->izquierda);
        eliminarVariables(&(*arbol)->derecha);
        if ((*arbol)->tipo == ID_VARIABLE)
        {
            eliminarNodo(arbol);
        }
    }
}
