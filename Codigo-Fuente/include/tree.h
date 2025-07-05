#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
#include <filesystem>


struct NodoArbol {
    std::string nombre;
    std::vector<NodoArbol*> hijos;
};

// Crear árbol
NodoArbol* crearArbol();

// Liberar memoria
void destruirArbol(NodoArbol* nodo);

// Insertar ruta en árbol
void insertarRuta(NodoArbol* nodo, const std::string& ruta);

// Buscar nodo (0 archivo, 1 no existe, 2 directorio)
int buscarNodo(NodoArbol* nodo, const std::string& ruta);

// Eliminar nodo, retorna true si se elimina
bool eliminarRuta(NodoArbol* nodo, const std::string& ruta);

#endif
