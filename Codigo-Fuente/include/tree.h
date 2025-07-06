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

// Retorna indice en el vector de nodos por búsqueda binaria lexicográfica. -1 si no se encuentra
int indiceNodoHijo(std::vector<NodoArbol*> v, const string& nombre);

// Referencia al padre de un nodo para poder insertar y eliminar en el vector hijos
NodoArbol** buscarNodoPadre(NodoArbol* nodo, const std::string& ruta);

// Insertar nodo, retorna true si se logra insertar.
// Acepta ruta de tipo "nombre1/nombre2/.../nombreN", no de tipo "raiz/nombre1/nombre2/.../nombreN"
bool insertarRuta(NodoArbol* nodo, const std::string& ruta);

// Buscar nodo (0 archivo, 1 no existe, 2 directorio)
int buscarNodoTipo(NodoArbol* nodo, const std::string& ruta);

// Eliminar nodo, retorna true si se elimina
bool eliminarRuta(NodoArbol* nodo, const std::string& ruta);

#endif
