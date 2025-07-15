#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "experimentacion.h"

using namespace std;

int main() {
    srand(time(nullptr));

    string base = "/home/jm_4/Taller_3/Tarea_INFO088_G5_pt2/grandee";  //ruta al direcctorio
    NodoArbol* raiz = new NodoArbol();
    raiz->nombre = "raiz";

    cout << "Creando árbol desde el sistema de archivos..." << endl;
    auto duracion_creacion = crearArbolDesdeFS(raiz, base);
    cout << "Árbol creado en " << duracion_creacion.count() << " microsegundos." << endl;

    // Recolectar rutas reales del árbol para experimentos
    vector<string> rutas;
    recolectarRutasArbol(raiz, "", rutas);
    cout << "Rutas recolectadas: " << rutas.size() << endl;

    // Datos para inserción
    vector<string> carpetas = {"img", "doc", "tmp", "config", "data"};
    vector<string> nombres = {"archivo", "informe", "imagen", "reporte", "registro"};
    vector<string> extensiones = {"txt", "jpg", "png", "log", "csv"};

    // Test de búsqueda
    cout << "Realizando test de búsqueda..." << endl;
    auto dur_busqueda = testBusqueda(raiz, rutas);
    cout << "Búsqueda terminada en " << dur_busqueda.count() << " microsegundos." << endl;

    // Test de eliminación
    cout << "Realizando test de eliminación..." << endl;
    auto dur_eliminacion = testEliminacion(raiz, rutas);
    cout << "Eliminación terminada en " << dur_eliminacion.count() << " microsegundos." << endl;

    // Test de inserción
    cout << "Realizando test de inserción..." << endl;
    auto dur_insercion = testInsercion(raiz, carpetas, nombres, extensiones);
    cout << "Inserción terminada en " << dur_insercion.count() << " microsegundos." << endl;

    // Liberar memoria del árbol
    Arbol arbol;
    arbol.raiz = raiz;
    delete arbol.raiz;

    return 0;
}
