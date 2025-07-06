#include "tree.h"
using namespace std;

// TODO: corregir uso de string y string&
// TODO: debo pasar la referencia de los vectores?


int indiceNodoHijo(vector<NodoArbol*> v, const string& nombre) {
    int izq = 0;
    int der = v.size() - 1;
    while (izq <= der) {
        int med = izq + (der - izq) / 2;

        // TODO: otro nombre en vez de actual? No es muy descriptivo
        string actual = v[med]->nombre;
        int i = 0;
        
        while (i < min(actual.size(), nombre.size()) && actual[i] == nombre[i]) {
            i++;
        }

        // si se recorrió una o dos de las palabras
        if (i >= min(actual.size(), nombre.size())) {
            if (actual.size() == nombre.size()) {
                return med;
            }
            else if (actual.size() < nombre.size()) {
                izq = med + 1;
            }
            else {
                der = med - 1;
            }
        }
        else {
            if (actual[i] < nombre[i]) {
                izq = med + 1;
            }
            else {
                der = med - 1;
            }
        }
    }

    return -1;
}


NodoArbol* crearArbol() {
    NodoArbol* nodo = new NodoArbol;
    nodo->nombre = "raiz";
    return nodo;
}


NodoArbol* crearNodo(const string& nombre) {
    NodoArbol* nodo = new NodoArbol;
    nodo->nombre = nombre;
    return;
}


void destruirArbol(NodoArbol* nodo) {
    for (NodoArbol* hijo : nodo->hijos)
        destruirArbol(hijo);
    delete nodo;
}


bool insertarRuta(NodoArbol* nodo, const string& ruta) {

    size_t primer_sep = ruta.find('/');
    
    // primer nombre de la ruta
    string nombre_base = ruta.substr(0, primer_sep); // const? &?
    int idx_hijo = busquedaBinariaLexicografica(nodo->hijos, nombre_base);

    // primero queremos saber si el nombre base de la ruta está en el arbol


    // si solo queda un nombre en la ruta
    if (primer_sep == string::npos) {
        if (idx_hijo == -1) {
            return false;
        }
        
        NodoArbol* hijo = crearNodo(nombre_base);
        // ...inserta el hijo de manera que el vector hijos quede ordenado
        return true;

    }
    
    string siguiente_ruta = ruta.substr(primer_sep+1);

    return insertarRuta(nodo->hijos[idx_hijo], siguiente_ruta);
}

NodoArbol** buscarNodoPadre(NodoArbol* nodo, const string& ruta) {

}

int buscarNodo(NodoArbol* nodo, const string& ruta) {

}


bool eliminarRuta(NodoArbol* nodo, const string& ruta) {

}
