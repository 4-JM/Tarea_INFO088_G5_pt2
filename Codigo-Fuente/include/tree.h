#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
// #include <filesystem> Creo que debería ir en main

struct NodoArbol {
    std::string nombre;
    std::vector<NodoArbol*> hijos;
};

// Dado crearNodo, crearArbol podría ser simplemente crearNodo("raiz"), vale la pena?
NodoArbol* crearArbol();

NodoArbol* crearNodo(const std::string& nombre);

void destruirArbol(NodoArbol* nodo);

// Retorna indice en el vector de nodos por búsqueda binaria lexicográfica. 
// Si indice_insertar es verdadero, busca el índice en el que debería ser insertado el hijo
// -1 si la función falla
int indiceNodoHijo(std::vector<NodoArbol*> v, const string& nombre, bool indice_insertar = false);

// Referencia al padre de un nodo para poder insertar y eliminar en el vector hijos
// Si busca_insertar es verdadero, retornará el ancestro más cercano en vez del padre
// Busca todos los niveles del árbol
// retorna puntero nulo si no se encuentra el padre 
NodoArbol** buscarNodoPadre(NodoArbol* nodo, const std::string& ruta, bool busca_insertar = false);

// Insertar nodo, retorna true si se logra insertar.
// Acepta ruta de tipo "nombre1/nombre2/.../nombreN", no de tipo "raiz/nombre1/nombre2/.../nombreN"
bool insertarRuta(NodoArbol* nodo, const std::string& ruta);

// Buscar nodo en cada nivel del arbol (0 archivo, 1 no existe, 2 directorio)
int buscarNodoTipo(NodoArbol* nodo, const std::string& ruta);

// Eliminar ruta, retorna true si se elimina
bool eliminarRuta(NodoArbol* nodo, const std::string& ruta);

#endif


// buscarNodoPadre() podría solo llegar hasta el padre sin corroborar que su hijo existe
// quedaría de tarea para insertarRuta() saber (si es un ancestro)? y si el hijo existe
// para saber si es un ancestro deberiamos empezar buscando desde la derecha
// quedaría de tarea para buscarNodoTipo() saber si el hijo existe
// quedaría de tarea para eliminarRuta() saber si el hijo existe
// queda de tarea porque después tienen que saber en qué posición está y repetiría los cálculos

// para buscarNodoPadre(), si nos queda solo un nombre en la ruta devolvemos el posible padre
// podría existir la función verificarHijo()

// En vez de tener funcionalidad extraña con insertarRuta(), podría solo admitir la inserción
// si es que existen los directorios necesarios y llamarla nuevamente con el nodo siendo el
// directorio recien creado
// se encaargaría main?
// ponerlo en un while loop