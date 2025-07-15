#include "experimentacion.h"
#include "tree.h"
#include <filesystem>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;
namespace fs = filesystem;

// Genera números aleatorios
random_device rd;
mt19937 gen(rd());

// Función para juntar todas las rutas de un directorio (recursivo)
void recolectarRutas(const string& directorio, vector<string>& rutas) {
    try {
        for (const auto& entrada : fs::recursive_directory_iterator(directorio)) {
            if (entrada.is_regular_file() || entrada.is_directory()) {
                string rutaRelativa = fs::relative(entrada.path(), directorio).string();
                replace(rutaRelativa.begin(), rutaRelativa.end(), '\\', '/');
                rutas.push_back(rutaRelativa);
            }
        }
    } catch (const fs::filesystem_error& ex) {
        cerr << "Error accediendo al directorio: " << ex.what() << endl;
    }
}

// Función para juntar directorios del árbol
void recolectarDirectorios(NodoArbol* nodo, const string& rutaActual, vector<string>& directorios) {
    if (nodo == nullptr) {
	return;
    }
    if (!nodo->hijos.empty()) {
        if (!rutaActual.empty()) {
            directorios.push_back(rutaActual);
        }
        for (NodoArbol* hijo : nodo->hijos) {
            string nuevaRuta = rutaActual.empty() ? hijo->nombre : rutaActual + "/" + hijo->nombre;
            recolectarDirectorios(hijo, nuevaRuta, directorios);
        }
    }
}

// Función para juntar todas las rutas del árbol
void recolectarRutasArbol(NodoArbol* nodo, const string& rutaActual, vector<string>& rutas) {
    if (nodo == nullptr) {
	return;
    }
    if (!rutaActual.empty()) {
        rutas.push_back(rutaActual);
    }
    for (NodoArbol* hijo : nodo->hijos) {
        string nuevaRuta = rutaActual.empty() ? hijo->nombre : rutaActual + "/" + hijo->nombre;
        recolectarRutasArbol(hijo, nuevaRuta, rutas);
    }
}

// Genera nombres aleatorios para archivos
string generarNombreAleatorio(const vector<string>& nombres, const vector<string>& extensiones) {
    uniform_int_distribution<> distNombres(0, nombres.size() - 1);
    uniform_int_distribution<> distExtensiones(0, extensiones.size() - 1);

    return nombres[distNombres(gen)] + "." + extensiones[distExtensiones(gen)];
}

// Crear arbol desde File system
chrono::microseconds crearArbolDesdeFS(NodoArbol* raiz, const string& base) {
    vector<string> rutas;
    
    // Recolecta todas las rutas del directorio base
    recolectarRutas(base, rutas);
    
    // Crea árbol y mide tiempo
    Arbol arbol;
    
    auto inicio = chrono::high_resolution_clock::now();
    
    // Inserta cada ruta en el árbol (en preorden)
    for (const string& ruta : rutas) {
        arbol.insertarRuta(&(arbol.raiz), ruta);
    }
    
    auto fin = chrono::high_resolution_clock::now();
    
    // Copiar la estructura del árbol creado a la raíz que se le entrega
    *raiz = *(arbol.raiz);
    arbol.raiz = nullptr; // Evita que el destructor elimine los nodos del árbol
    
    return chrono::duration_cast<chrono::microseconds>(fin - inicio);
}

// Función testBusqueda
chrono::microseconds testBusqueda(NodoArbol* raiz, const vector<string>& nombres) {
    Arbol arbol;
    arbol.raiz = raiz; 
    
    // Genera rutas "random" para buscar en las rutas existentes
    vector<string> rutasBusqueda;
    uniform_int_distribution<> dist(0, nombres.size() - 1);
    
    for (int i = 0; i < REP; i++) {
        rutasBusqueda.push_back(nombres[dist(gen)]);
    }
    
    auto inicio = chrono::high_resolution_clock::now();
    
    for (const string& ruta : rutasBusqueda) {
        arbol.buscarRuta(&raiz, ruta);
    }
    
    auto fin = chrono::high_resolution_clock::now();
    
    arbol.raiz = nullptr; // Evita que el destructor elimine el árbol
    
    return chrono::duration_cast<chrono::microseconds>(fin - inicio);
}

// Función de testEliminacion
chrono::microseconds testEliminacion(NodoArbol* raiz, const vector<string>& nombres) {
    Arbol arbol;
    arbol.raiz = raiz;
    
    // Genera rutas aleatorias para eliminar
    vector<string> rutasEliminacion;
    uniform_int_distribution<> dist(0, nombres.size() - 1);
    
    for (int i = 0; i < REP; i++) {
        rutasEliminacion.push_back(nombres[dist(gen)]);
    }
    
    auto inicio = chrono::high_resolution_clock::now();
    
    // Hace las eliminaciones de las rutas
    for (const string& ruta : rutasEliminacion) {
        arbol.eliminarRuta(&raiz, ruta);
    }
    
    auto fin = chrono::high_resolution_clock::now();
    
    arbol.raiz = nullptr; // Evita que el destructor elimine el árbol
    
    return chrono::duration_cast<chrono::microseconds>(fin - inicio);
}

// Función de testInsercion
chrono::microseconds testInsercion(NodoArbol* raiz, const vector<string>& carpetas, 
                                  const vector<string>& nombres, 
                                  const vector<string>& extensiones) {
    const int NUM_DIRECTORIOS = 2000;
    
    Arbol arbol;
    arbol.raiz = raiz;
    
    // Junta los directorios existentes en el árbol
    vector<string> directoriosExistentes;
    recolectarDirectorios(raiz, "", directoriosExistentes);
    
    // Si no hay suficientes directorios, usa los entregados
    if (directoriosExistentes.size() < NUM_DIRECTORIOS) {
        directoriosExistentes.insert(directoriosExistentes.end(), carpetas.begin(), carpetas.end());
    }
    
    // Verifica que hay al menos algún directorio
    if (directoriosExistentes.empty()) {
        directoriosExistentes.push_back(""); 
    }
    
    // Genera inserciones aleatorias
    vector<string> inserciones;
    uniform_int_distribution<> distDir(0, min((int)directoriosExistentes.size() - 1, NUM_DIRECTORIOS - 1));
    
    for (int i = 0; i < REP; i++) {
        string directorioAleatorio = directoriosExistentes[distDir(gen)];
        string archivoAleatorio = generarNombreAleatorio(nombres, extensiones);
        
        string rutaCompleta;
        if (directorioAleatorio.empty()) {
            rutaCompleta = archivoAleatorio;
        } else {
            rutaCompleta = directorioAleatorio + "/" + archivoAleatorio;
        }
        
        inserciones.push_back(rutaCompleta);
    }
    
    auto inicio = chrono::high_resolution_clock::now();
    
    // Realiza las inserciones
    for (const string& insercion : inserciones) {
        arbol.insertarRuta(&raiz, insercion);
    }
    
    auto fin = chrono::high_resolution_clock::now();
    
    arbol.raiz = nullptr; // Evita que el destructor elimine el árbol
    
    return chrono::duration_cast<chrono::microseconds>(fin - inicio);
}
