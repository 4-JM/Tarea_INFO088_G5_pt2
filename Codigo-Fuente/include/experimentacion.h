#ifndef EXPERIMENTACION_H
#define EXPERIMENTACION_H

#include <string>
#include <chrono>
#include "tree.h"

#define REP 100000

// Experimentación
std::chrono::microseconds crearArbolDesdeFS(NodoArbol* raiz, const std::string& base);
std::chrono::microseconds testBusqueda(NodoArbol* raiz, const std::vector<std::string>& nombres);
std::chrono::microseconds testEliminacion(NodoArbol* raiz, const std::vector<std::string>& nombres);
std::chrono::microseconds testInsercion(NodoArbol* raiz, const std::vector<std::string>& carpetas, const std::vector<std::string>& nombres, const std::vector<std::string>& extensiones);

#endif
