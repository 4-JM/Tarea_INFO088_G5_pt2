#include "tree.h"
using namespace std;

NodoArbol* crearArbol() {
    NodoArbol* nodo = new NodoArbol;
    nodo->nombre = "raiz";
    return nodo;
}

void destruirArbol(NodoArbol* nodo) {
    for (auto hijo : nodo->hijos)
        destruirArbol(hijo);
    delete nodo;
}

void insertarRuta(NodoArbol* nodo, const string& ruta) {

}

int buscarNodo(NodoArbol* nodo, const string& ruta) {

}

bool eliminarRuta(NodoArbol* nodo, const string& ruta) {

}
