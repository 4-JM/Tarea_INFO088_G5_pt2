#include <tree.h>
#include <iostream>
using namespace std;

int main() {
    NodoArbol* raiz = crearArbol();
    NodoArbol* nodo1 = crearNodo("nombre1");
    NodoArbol* nodo2 = crearNodo("nombre2");
    NodoArbol* nodo3 = crearNodo("nombre3");
    raiz->hijos.push_back(nodo1);
    raiz->hijos.push_back(nodo2);
    raiz->hijos.push_back(nodo3);

    NodoArbol* otro_raiz = crearArbol();
    NodoArbol* otro_nodo1 = crearNodo("otro_nombre1");
    NodoArbol* otro_nodo2 = crearNodo("otro_nombre2");
    NodoArbol* otro_nodo3 = crearNodo("otro_nombre3");
    insertarRuta(otro_raiz, "otro_nombre1");
    insertarRuta(otro_raiz, "otro_nombre2");
    insertarRuta(otro_raiz, "otro_nombre3");

}
