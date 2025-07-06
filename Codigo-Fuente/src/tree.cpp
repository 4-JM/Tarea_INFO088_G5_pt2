#include "tree.h"
using namespace std;

// TODO: corregir uso de string y string&
// TODO: debo pasar la referencia de los vectores?

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


// podría haber una variante que retorne donde debería ser insertado un hijo?
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


// FIXME
NodoArbol** buscarNodoPadre(NodoArbol* nodo, const string& ruta) {
    /*
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
    */
}


// TODO
bool insertarRuta(NodoArbol* nodo, const string& ruta) {

    // ya que existe insertarRuta, podría también existir bool insertarNodo() que asume estamos en el nodo padre
    // probablemente innecesario ya que cumpliría la misma función que insertarRuta() llamado con otro argumento de nodo
    // insertarNodo() sería iterativo y muy simple

    // encuentra el nodo padre
    // caso 1: Solo se encuentra parcialmente la ruta
        // crea un nodo y lo agrega al vector hijos del nodo padre
        // como aun queda ruta repetimos sabiendo que el nodo padre ahora es 1
        // retorna verdadero
        // EJ:
            // Queremos insertar x/1/a
            // Existe x y no tiene un hijo 1
            // ...
    // caso 2: Se encuentra completamente la ruta
        // retorna falso
}    


// TODO
int buscarNodoTipo(NodoArbol* nodo, const string& ruta) {
    // Encuentra el nodo padre
    // Caso 1: Solo se encuentra parcialmente la ruta
        // retorna 1 (Tipo vacio)
        // EJ:
        // Queremos buscar el nodo x/1/a
            // xxiste x y no tiene un hijo 1 o existe x/1 y no tiene un hijo a
            // retornamos x o x/1 respectivamente
    // Caso 2: Se encuentra completamente la ruta
        // caso 2.1: El nodo no tiene hijos
            // retorna 0 (Tipo archivo)
        // caso 2.2: El nodo tiene hijos
            // retorna 2 (Tipo directorio)
    
}

// TODO
// Debería ser una referencia al nodo?
bool eliminarRuta(NodoArbol* nodo, const string& ruta) {
    // encuentra el nodo padre
    // caso 1: solo se encuentra parcialmente la ruta
        // retorna falso
    // caso 2: se encuentra completament la ruta
        // llama a destruirArbol() y retorna verdadero
}
