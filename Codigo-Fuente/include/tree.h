#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct NodoArbol {
    string nombre;
    vector<NodoArbol*> hijos; // Vector siempre ordenado lexicográficamente
};

pair<string, string> obtenerNombresRuta(const string& ruta);

class Arbol {
public: 
    NodoArbol* raiz; 
    
    Arbol();
    
    void eliminarNodos(NodoArbol *t);
	virtual ~Arbol();
    
    void imprimirPreorder(NodoArbol *t);
    void imprimirInorder(NodoArbol *t);
    void imprimirPostorder(NodoArbol *t);

    int indiceNodoHijo(NodoArbol **t, const string& nombre_hijo, bool indice_insertar);

    pair<NodoArbol**, string> buscarNodoPadre(NodoArbol **t, const string& ruta, bool buscar_ancestro);
    
    int buscarRuta(NodoArbol **t, const string& ruta);

    bool insertarNodo(NodoArbol **t, const string& nombre);
    bool insertarRuta(NodoArbol **t, const string& ruta);
    
    bool eliminarRuta(NodoArbol **t, const string& ruta);
};

#endif