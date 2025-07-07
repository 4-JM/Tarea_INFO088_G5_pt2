#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
#include <utility>

struct NodoArbol {
    std::string nombre;
    std::vector<NodoArbol*> hijos;
};

// Dado crearNodo, crearArbol podría ser simplemente crearNodo("raiz"), vale la pena?
NodoArbol* crearArbol();

NodoArbol* crearNodo(const std::string& nombre);

void destruirArbol(NodoArbol* nodo);

/*
Retorna indice en el vector de nodos por búsqueda binaria lexicográfica. 
Si indice_insertar es verdadero, busca el índice en el que debería ser insertado el hijo
-1 si se quiere encontrar y no está o si se quiere insertar y ya está
*/
int indiceNodoHijo(std::vector<NodoArbol*> v, const std::string& nombre, bool indice_insertar = false);

/* 
Referencia al posible padre de un nodo para poder insertar y eliminar en el vector hijos
Si busca_ancestro es verdadero, retornará el ancestro más cercano en vez del padre
Busca todos los niveles del árbol. Retorna puntero nulo si no se encuentra el padre o ancestro
*/ 
std::pair<NodoArbol**, const std::string&> buscarNodoPadre(NodoArbol* nodo, const std::string& ruta, bool busca_ancestro = false);

/* 
Insertar nodo, retorna true si se logra insertar.
Acepta ruta de tipo "nombre1/nombre2/.../nombreN", no de tipo "raiz/nombre1/nombre2/.../nombreN"
*/ 
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


/*
pseudocódigo:
    buscarNodoTipo:
        // Encuentra el nodo padre
        // Caso 1: Solo se encuentra parcialmente la ruta
            // EJ:
            // Queremos buscar el nodo x/y/z
                // existe x y no tiene un hijo y o existe x/y y no tiene un hijo z
                // tenemos un puntero nulo 
                // retornamos 1
        // Caso 2: Se encuentra completamente la ruta
            // caso 2.1: El nodo no tiene hijos
                // retorna 0 (Tipo archivo)
            // caso 2.2: El nodo tiene hijos
                // retorna 2 (Tipo directorio)

    eliminarRuta:
        // encuentra el nodo padre
        // caso 1: solo se encuentra parcialmente la ruta
            // retorna falso
        // caso 2: se encuentra completament la ruta
            // llama a destruirArbol() y retorna verdadero
*/


    // ej:
    // ruta: x/y/z/x/y
    // ancestro: x
    // ruta_restante -> y/z/x/y
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

// podría existir la función obtenerNombresDesdeRuta()
// que retorne un par de strings que sean el primer nombre y el resto

// tal vez podría haber tratado la ruta como un vector de nombres desde el principio
// eso sería más eficiente? más cómodo de programar?