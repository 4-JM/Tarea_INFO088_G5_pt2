#include "tree.h"
using namespace std;


NodoArbol* crearArbol() {
    NodoArbol* nodo = new NodoArbol;
    nodo->nombre = "raiz";
    return nodo;
}


NodoArbol* crearNodo(const string& nombre) {
    NodoArbol* nodo = new NodoArbol;
    nodo->nombre = nombre;
    return nodo;
}


void destruirArbol(NodoArbol* nodo) {
    for (NodoArbol* hijo : nodo->hijos)
        destruirArbol(hijo);
    delete nodo;
}

// FIXME: Qué ocurre si el vector está vacío?
int indiceNodoHijo(vector<NodoArbol*> v, const string& nombre, bool indice_insertar) {
    int izq = 0;
    int der = int(v.size()) - 1;

    while (izq <= der) {
        int med = izq + (der - izq) / 2;

        string actual = v[med]->nombre;
        int i = 0;
        
        while (i < min(int(actual.size()), int(nombre.size())) && actual[i] == nombre[i]) {
            i++;
        }

        // si se recorrió una o dos de las palabras
        if (i >= min(int(actual.size()), int(nombre.size()))) {
            if (actual.size() == nombre.size()) {
                if (indice_insertar) {
                    return -1;
                }
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

    if (indice_insertar) {
        return izq;
    }

    return -1;
}


pair<NodoArbol**, const string&> buscarNodoPadre(NodoArbol* nodo, const string& ruta, bool busca_ancestro) {
    
    int idx_hijo;
    size_t primer_sep = ruta.find('/');

    // primer nombre de la ruta
    string nombre_base = ruta.substr(0, primer_sep);

    // si solo queda el hijo en la ruta
    if (primer_sep == string::npos) {
        return {&nodo, ruta};
    }

    idx_hijo = indiceNodoHijo(nodo->hijos, nombre_base);
    
    // está el siguiente nodo en el árbol?
    if (idx_hijo == -1) {
        if (busca_ancestro) {
            // retorna el ancestro
            return {&nodo, ruta};
        }
        return {nullptr, ruta}; // debería retornar un string vacío pero da error
    }
        
    string siguiente_ruta = ruta.substr(primer_sep+1);
    return buscarNodoPadre(nodo->hijos[idx_hijo], siguiente_ruta, busca_ancestro);
}


bool insertarRuta(NodoArbol* nodo, const string& ruta) {

    auto [ancestro, ruta_restante] = buscarNodoPadre(nodo, ruta, true);

    if (*ancestro == nullptr) {
        return false;
    }

    size_t primer_sep = ruta.find('/');
    string nombre_base = ruta_restante.substr(0, primer_sep);

    int idx_hijo = indiceNodoHijo((*ancestro)->hijos, nombre_base, true);
    if (idx_hijo == -1) {
        return false;   // ya está insertado
    } 

    NodoArbol* nodo_hijo = crearNodo(nombre_base);

    (*ancestro)->hijos.insert((*ancestro)->hijos.begin() + idx_hijo, nodo_hijo);

    string nombres_siguientes = ruta_restante.substr(primer_sep + 1);
    while (!nombres_siguientes.empty()) {
        NodoArbol** padre = &(nodo_hijo);

        primer_sep = nombres_siguientes.find('/');
        nombre_base = nombres_siguientes.substr(0, primer_sep);

        nodo_hijo = crearNodo(nombre_base);
        (*padre)->hijos.push_back(nodo_hijo);

        nombres_siguientes = nombres_siguientes.substr(primer_sep + 1);
    }  

    return true;
}    


int buscarNodoTipo(NodoArbol* nodo, const string& ruta) {
    
    auto [padre, nombre_hijo] = buscarNodoPadre(nodo, ruta, false); 

    if (*padre == nullptr) {
        return 1;
    }

    int idx_hijo = indiceNodoHijo((*padre)->hijos, nombre_hijo, false);
    if (idx_hijo == -1) {
        return false;
    }

    if ((*padre)->hijos[idx_hijo]->hijos.size() == 0) {
        return 0;
    }

    return 2;
}


bool eliminarRuta(NodoArbol* nodo, const string& ruta) {

    auto [padre, nombre_hijo] = buscarNodoPadre(nodo, ruta, false);

    if (*padre == nullptr) {
        return false;
    }

    int idx_hijo = indiceNodoHijo((*padre)->hijos, nombre_hijo, false);
    if (idx_hijo == -1) {
        return false;
    }

    (*padre)->hijos.erase((*padre)->hijos.begin() + idx_hijo);
    destruirArbol((*padre)->hijos[idx_hijo]);
    
    return true;
}
