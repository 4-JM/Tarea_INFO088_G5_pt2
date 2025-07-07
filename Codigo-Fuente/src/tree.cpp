#include "tree.h"
using namespace std;

/*
Para indiceNodoHijo() se puede dar el parámtero indice_insertar si se quiere recibir
el índice donde *estaría* para mantener el orden del vector hijos, 
para poder usar dentro de insertarRuta().

Tambien buscarNodoPadre() admite el parámetro indice_insertar ya que
hará llamadas a indiceNodoHijo() para pasar de un nivel del árbol al siguiente

El fundamento de estas decisiones es que tanto insertarRuta(), buscarNodoTipo() como eliminarRuta()
se benefician de tener funciones para saber donde está un nodo hijo pero requieren 
de información ligeramente distinta para ser aprovechadas

insertarRuta() permite la insercion de rutas aun si no existen todos los directorios previos
ej:
ruta a insertar: x/y/z/1
directorio encontrado: x
crea el directorio y, luego el z e inserta el archivo 1
*/

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


// TODO: Como retorno la posición donde debería estar?
int indiceNodoHijo(vector<NodoArbol*> v, const string& nombre, bool indice_insertar = false) {
    int izq = 0;
    int der = v.size() - 1;

    while (izq <= der) {
        int med = izq + (der - izq) / 2;

        string actual = v[med]->nombre;
        int i = 0;
        
        while (i < min(actual.size(), nombre.size()) && actual[i] == nombre[i]) {
            i++;
        }

        // si se recorrió una o dos de las palabras
        if (i >= min(actual.size(), nombre.size())) {
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
        return ; // Qué cosa?
    }

    return -1;
}

// TODO: probar con punteros normales
// a lo mejor el puntero doble es solo con las clases
// a lo mejor para eliminar si o si se necesita una referencia al puntero a la raiz
NodoArbol** buscarNodoPadre(NodoArbol* nodo, const string& ruta, bool busca_insertar = false) {
    
    int idx_hijo;
    size_t primer_sep = ruta.find('/');

    // primer nombre de la ruta
    string nombre_base = ruta.substr(0, primer_sep);

    // si solo queda el hijo en la ruta
    if (primer_sep == string::npos) {
        return &nodo;
    }

    // está el siguiente nodo en el árbol?
    idx_hijo = indiceNodoHijo(nodo->hijos, nombre_base);
    
    if (idx_hijo == -1) {
        if (busca_insertar) {
            // retorna el ancestro
            return &nodo;
        }
        return nullptr;
    }
        
    string siguiente_ruta = ruta.substr(primer_sep+1);
    return buscarNodoPadre(nodo->hijos[idx_hijo], siguiente_ruta);
}

// TODO
bool insertarRuta(NodoArbol* nodo, const string& ruta) {

    NodoArbol** ancestro = buscarNodoPadre(nodo, ruta, true);

    if (*ancestro == nullptr) {
        return false;
    }

    // ej:
    // ruta: x/y/z
    // ancestro: x
    // ruta_restante -> y/z
    // no sería necesario si pudieramos saber el nivel de profundidad al que llegó buscarNodoPadre

    // si ancestro no es nulo, insertarmos en el vector de hijos la ruta correspondiente (cual?)
    // si queda más ruta, creamos un nodo como nieto y lo agregamos al vector hijos del hijo
    // repetir si queda más ruta



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
    
        // NodoArbol* hijo = crearNodo(nombre_base);
    //  ...inserta el hijo de manera que el vector hijos quede ordenado
    // return true;
}    


// TODO
int buscarNodoTipo(NodoArbol* nodo, const string& ruta) {
    NodoArbol** padre = buscarNodoPadre(nodo, ruta, false); 

    if (*padre == nullptr) {
        return 1;
    }


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
bool eliminarRuta(NodoArbol* nodo, const string& ruta) {

    NodoArbol** padre = buscarNodoPadre(nodo, ruta, false);

    if (*padre == nullptr) {
        return false;
    }

    string nombre_hijo;
    
    size_t ultimo_sep = ruta.rfind('/');
    if (ultimo_sep == string::npos) {
        nombre_hijo = ruta;
    }
    else {
        nombre_hijo = ruta.substr(ultimo_sep+1);
    }

    int idx_hijo = indiceNodoHijo((*padre)->hijos, nombre_hijo, false);
    if (idx_hijo == -1) {
        return false;
    }

    ((*padre)->hijos.erase((*padre)->hijos.begin() + idx_hijo));
    destruirArbol((*padre)->hijos[idx_hijo]);


    // encuentra el nodo padre
    // caso 1: solo se encuentra parcialmente la ruta
        // retorna falso
    // caso 2: se encuentra completament la ruta
        // llama a destruirArbol() y retorna verdadero
}
