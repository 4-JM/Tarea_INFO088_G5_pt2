#include "tree.h"
#include <iostream>

// retorna primer nombre de la ruta y el resto de la ruta
pair<string, string> obtenerNombresRuta(const string& ruta) {
    string nombre_base; 
    string ruta_restante;

    size_t idx_primer_separador = ruta.find('/');

    if (idx_primer_separador == string::npos) {
        nombre_base = ruta;
        ruta_restante = "";
    }

    else {
        nombre_base = ruta.substr(0, idx_primer_separador);
        ruta_restante = ruta.substr(idx_primer_separador + 1);
    }
    
    return {nombre_base, ruta_restante};
}

// constructor de la clase
Arbol::Arbol() {
    this->raiz = new NodoArbol();
    this->raiz->nombre = "raiz";
    this->raiz->hijos = {};
}


// libera los nodos creados del subarbol t. No elimina a t del vector hijos de su padre.
void Arbol::eliminarNodos(NodoArbol *t) {
    if (t == nullptr) {
        return;
    }
    for (NodoArbol* hijo : t->hijos) {
        eliminarNodos(hijo);
    }
    delete t;
    t = nullptr;
}


// libera la memoria del arbol.
Arbol::~Arbol() {
    eliminarNodos(raiz);
}


// R-I-D
void Arbol::imprimirPreorder(NodoArbol *t) {
    if (t == nullptr) {
        return;
    }
    cout << t->nombre << endl;
    for (NodoArbol *hijo : t->hijos) {
        imprimirPreorder(hijo);
    }
}


// I-R-D
void Arbol::imprimirInorder(NodoArbol *t) {
    if (t == nullptr) {
        return;
    }
    if (t->hijos.size() == 0) {
        cout << t->nombre << endl;
        return;
    }
    imprimirInorder(t->hijos[0]);
    cout << t->nombre << endl;
    for (unsigned int i = 1; i < t->hijos.size(); i++) {
        imprimirInorder(t->hijos[i]);
    }
}


// I-D-R
void Arbol::imprimirPostorder(NodoArbol *t) {
    if (t == nullptr) {
        return;
    }
    for (NodoArbol* hijo : t->hijos) {
        imprimirPostorder(hijo);
    }
    cout << t->nombre << endl;
}


/* Encuentra por busqueda binaria lexicográfica el indice del hijo en el vector de hijos.
Si indice_insertar es true, entonces devuelve el indice para insertar el hijo en el vector de hijos.
-1 si se buscaba la posición del hijo y no se encuentra o si no se buscaba y se encontró.
*/ 
int Arbol::indiceNodoHijo(NodoArbol **t, const string& nombre_hijo, bool indice_insertar){
    
    int izq = 0;
    int der = int((*t)->hijos.size()) - 1;
    while (izq <= der) {
        int med = izq + (der - izq) / 2;

        string palabra_actual = (*t)->hijos[med]->nombre;
        
        unsigned int i = 0;
        while (i < min(palabra_actual.size(), palabra_actual.size()) && palabra_actual[i] == nombre_hijo[i]) {
            i++;
        }

        // si se recorrió una o dos de las palabras
        if (i >= min(palabra_actual.size(), nombre_hijo.size())) {
            if (palabra_actual.size() == nombre_hijo.size()) {
                if (indice_insertar) {
                    return -1;
                }
                return med;
            }
            if (palabra_actual.size() < nombre_hijo.size()) {
                izq = med + 1;
            }
            else {
                der = med - 1;
            }
        }
        
        else {
            if (palabra_actual[i] < nombre_hijo[i]) {
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


/*
retorna una referencia al padre del nodo al final de la ruta provista,
lo que permite insertar o eliminar al nodo hijo del vector hijos del padre.
También retorna el nombre del nodo al final de la ruta.
adicionalmente, si buscar_ancestro es true, retornará el ancestro más cercano del nodo para poder insertar una cadena de nodos
(ej: si se busca la ruta "a/b/c/d" pero solo existe la ruta "a/b" entonces el ancestro más cercano de "d" será "b" y será retornado junto a la ruta pendiente "c/d") 
Se debe corroborar que el padre recibido realmente contiene el hijo que se especificó,
esto con el fin de no repetir operaciones.
*/ 
pair<NodoArbol**, string> Arbol::buscarNodoPadre(NodoArbol **t, const string& ruta, bool buscar_ancestro) {
    
    auto [nombre_base, ruta_restante] = obtenerNombresRuta(ruta);

    // si solo falta la ultima ruta el nodo actual es el posible padre
    if (ruta_restante.empty()) {
        return {t, nombre_base};
    }

    int idx_hijo = indiceNodoHijo(t, nombre_base, false);

    if (idx_hijo == -1) {
        if (buscar_ancestro) {
            return {t, ruta};
        }
        return {nullptr, ""};
    }
    
    return buscarNodoPadre(&((*t)->hijos[idx_hijo]), ruta_restante, buscar_ancestro);
}


// Dada una ruta se busca el último nodo y retorna su tipo (0 archivo, 1 no existe y 2 directorio)
// (ej: "ruta = a/b/c" -> se busca el nodo "c").
int Arbol::buscarRuta(NodoArbol **t, const string& ruta) {

    auto [posible_padre, nombre_hijo] = buscarNodoPadre(t, ruta, false);

    if (posible_padre == nullptr) {
        return 1;
    }

    int idx_hijo = indiceNodoHijo(posible_padre, nombre_hijo, false);

    if (idx_hijo == -1) {
        return 1;
    }

    if ((*posible_padre)->hijos[idx_hijo]->hijos.size() == 0) {
        return 0;
    }

    return 2;
}


/* 
Se crea e inserta un nodo como hijo en el nodo proporcionado (mantiene el orden del vector hijos)
retorna falso si el nodo ya existía
(ej: arbol solo con raiz y nombre = "a" -> arbol con raiz y el nodo "a" de primer hijo) 
*/ 
bool Arbol::insertarNodo(NodoArbol **t, const string& nombre) {
    NodoArbol* p;
	if (*t == nullptr) {
		*t = p = new NodoArbol();
		p->nombre = nombre;
		p->hijos = {};
		return true;
	}

	p = new NodoArbol();
    p->nombre = nombre;
    p->hijos = {};


    int idx_insertar_hijo = indiceNodoHijo(t, nombre, true);
    if (idx_insertar_hijo == -1) {
        return false;   // ya estaba insertado
    }

    (*t)->hijos.insert((*t)->hijos.begin() + idx_insertar_hijo, p);
    return true;
}


/* Se crean e insertan nodos hasta completar la ruta. (mantiene el orden de los vectores hijos en el camino)
retorna falso si la ruta ya estaba insertada.

ej:
sea un arbol 
"raiz"
    ->"a"->"b"  
    ->"c"->"b"  
    ->"e"      

y ruta = "c/b/c/x" 
entonces el arbol queda

"raiz"
    ->"c"->"b"->"c"->"x"
    ->"a"->"b"
    ->"e"
*/
bool Arbol::insertarRuta(NodoArbol **t, const string& ruta) {
    
    auto [ancestro, ruta_restante] = buscarNodoPadre(t, ruta, true);

    if (ancestro == nullptr) {
        return false;
    }

    auto [nombre_base, nueva_ruta_restante] = obtenerNombresRuta(ruta_restante);

    int idx_insertar_hijo = indiceNodoHijo(ancestro, nombre_base, true);
    if (idx_insertar_hijo == -1) {
        return false;
    }

    NodoArbol* p = new NodoArbol();
    p->nombre = nombre_base;
    p->hijos = {};

    (*ancestro)->hijos.insert((*ancestro)->hijos.begin() + idx_insertar_hijo, p);

    while (!nueva_ruta_restante.empty()) {
        pair<string, string> nombre_y_ruta = obtenerNombresRuta(nueva_ruta_restante);
        
        ancestro = &((*ancestro)->hijos[idx_insertar_hijo]);

        p = new NodoArbol();
        p->nombre = nombre_y_ruta.first;
        p->hijos = {};

        idx_insertar_hijo = 0;
        (*ancestro)->hijos.push_back(p);

        nueva_ruta_restante = nombre_y_ruta.second;
    }

    return true;
}


// elimina el directorio o archivo al final de la ruta
// retorna falso si no existe
bool Arbol::eliminarRuta(NodoArbol **t, const string& ruta) {
    
    auto [posible_padre, nombre_hijo] = buscarNodoPadre(t, ruta, false);

    if (posible_padre == nullptr) {
        return false;
    }

    int idx_hijo = indiceNodoHijo(posible_padre, nombre_hijo, false);

    if (idx_hijo == -1) {
        return false;
    }

    eliminarNodos((*posible_padre)->hijos[idx_hijo]);

    (*posible_padre)->hijos.erase((*posible_padre)->hijos.begin() + idx_hijo);

    return true;
}
