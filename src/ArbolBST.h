#ifndef ARBOLBST_H
#define ARBOLBST_H

#include <iostream>
#include <vector>
using namespace std;

// Igual que en ListaDoble.h, todo el código del template va en el .h porque
// el compilador necesita verlo completo para fabricar ArbolBST<Jugador>.

template <class T>
class NodoArbol {
public:
    T dato;
    NodoArbol<T>* izquierdo;
    NodoArbol<T>* derecho;

    NodoArbol(const T& valor) {
        dato = valor;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

// Árbol binario de búsqueda: a la izquierda de cada nodo van los menores y a
// la derecha los mayores. Para Jugador, "menor" significa que su nombre va
// antes en el alfabeto (gracias a los operadores < y > de Jugador).
//
// Convención: la raíz está en el NIVEL 1 y la altura es el número de niveles
// (árbol vacío = 0, solo la raíz = 1).
// n = número de nodos, h = altura. Si los datos llegan en desorden, h se
// acerca a log2(n); si llegan ya ordenados, el árbol se vuelve una "lista"
// y h = n (peor caso).
//
// No se debe copiar (pasar por valor), por la misma razón que ListaDoble.
template <class T>
class ArbolBST {
private:
    NodoArbol<T>* raiz;

    // O(n): libera en postorden (primero los hijos y al final el nodo), porque
    // si se borrara el nodo primero se perderían los apuntadores a sus hijos
    void vaciarRecursivo(NodoArbol<T>* nodo) {
        if (nodo == nullptr) {
            return;
        }
        vaciarRecursivo(nodo->izquierdo);
        vaciarRecursivo(nodo->derecho);
        delete nodo;
    }

    // O(n): nodo, izquierdo, derecho
    void preordenRecursivo(NodoArbol<T>* nodo) const {
        if (nodo == nullptr) {
            return;
        }
        cout << nodo->dato << endl;
        preordenRecursivo(nodo->izquierdo);
        preordenRecursivo(nodo->derecho);
    }

    // O(n): izquierdo, nodo, derecho (sale en orden de menor a mayor)
    void inordenRecursivo(NodoArbol<T>* nodo) const {
        if (nodo == nullptr) {
            return;
        }
        inordenRecursivo(nodo->izquierdo);
        cout << nodo->dato << endl;
        inordenRecursivo(nodo->derecho);
    }

    // O(n): izquierdo, derecho, nodo
    void postordenRecursivo(NodoArbol<T>* nodo) const {
        if (nodo == nullptr) {
            return;
        }
        postordenRecursivo(nodo->izquierdo);
        postordenRecursivo(nodo->derecho);
        cout << nodo->dato << endl;
    }

    // O(n): igual que el inorden, pero guarda los datos en lugar de imprimirlos
    void inordenAVectorRecursivo(NodoArbol<T>* nodo, vector<T>& resultado) const {
        if (nodo == nullptr) {
            return;
        }
        inordenAVectorRecursivo(nodo->izquierdo, resultado);
        resultado.push_back(nodo->dato);
        inordenAVectorRecursivo(nodo->derecho, resultado);
    }

    // O(n): visita todos los nodos
    int alturaRecursivo(NodoArbol<T>* nodo) const {
        if (nodo == nullptr) {
            return 0;
        }
        int alturaIzquierda = alturaRecursivo(nodo->izquierdo);
        int alturaDerecha = alturaRecursivo(nodo->derecho);
        if (alturaIzquierda > alturaDerecha) {
            return alturaIzquierda + 1;
        }
        return alturaDerecha + 1;
    }

    // O(n): visita todos los nodos
    int contarRecursivo(NodoArbol<T>* nodo) const {
        if (nodo == nullptr) {
            return 0;
        }
        return 1 + contarRecursivo(nodo->izquierdo) + contarRecursivo(nodo->derecho);
    }

    // O(n): imprime solo los nodos que están 'nivel' niveles debajo de 'nodo'.
    // Cada vez que baja un nivel le resta 1; cuando llega a 1, ese es el nivel
    // que se busca.
    void imprimirNivel(NodoArbol<T>* nodo, int nivel) const {
        if (nodo == nullptr) {
            return;
        }
        if (nivel == 1) {
            cout << nodo->dato << endl;
        } else {
            imprimirNivel(nodo->izquierdo, nivel - 1);
            imprimirNivel(nodo->derecho, nivel - 1);
        }
    }

public:
    // O(1)
    ArbolBST() {
        raiz = nullptr;
    }

    // O(n): libera todos los nodos
    ~ArbolBST() {
        vaciar();
    }

    // O(n)
    void vaciar() {
        vaciarRecursivo(raiz);
        raiz = nullptr;
    }

    // O(1)
    bool estaVacio() const {
        return raiz == nullptr;
    }

    // O(h): baja desde la raíz (izquierda si es menor, derecha si es mayor)
    // hasta encontrar un lugar vacío. Si ya existe un dato igual (==), no lo
    // inserta y regresa false.
    bool insertar(const T& valor) {
        if (raiz == nullptr) {
            raiz = new NodoArbol<T>(valor);
            return true;
        }
        NodoArbol<T>* actual = raiz;
        while (true) {
            if (valor == actual->dato) {
                return false;
            }
            if (valor < actual->dato) {
                if (actual->izquierdo == nullptr) {
                    actual->izquierdo = new NodoArbol<T>(valor);
                    return true;
                }
                actual = actual->izquierdo;
            } else {
                if (actual->derecho == nullptr) {
                    actual->derecho = new NodoArbol<T>(valor);
                    return true;
                }
                actual = actual->derecho;
            }
        }
    }

    // O(h): en cada paso descarta todo un subárbol. Regresa un apuntador al
    // dato del nodo (o nullptr si no está). 'pasos' cuenta los nodos
    // comparados, que es igual al nivel donde está el dato.
    T* buscar(const T& valor, int& pasos) const {
        pasos = 0;
        NodoArbol<T>* actual = raiz;
        while (actual != nullptr) {
            pasos++;
            if (valor == actual->dato) {
                return &(actual->dato);
            }
            if (valor < actual->dato) {
                actual = actual->izquierdo;
            } else {
                actual = actual->derecho;
            }
        }
        return nullptr;
    }

    // O(h): busca el nodo igual (==) y reemplaza su dato. Para Jugador, el
    // nombre no cambia (es lo que se compara), así que el orden no se rompe.
    bool actualizar(const T& valor) {
        int pasos;
        T* dato = buscar(valor, pasos);
        if (dato == nullptr) {
            return false;
        }
        *dato = valor;   // "*dato" es el dato al que apunta el apuntador
        return true;
    }

    // O(n) cada uno: visitan todos los nodos
    void preorden() const {
        preordenRecursivo(raiz);
    }
    void inorden() const {
        inordenRecursivo(raiz);
    }
    void postorden() const {
        postordenRecursivo(raiz);
    }

    // O(n·h): sin usar cola. Para cada nivel de 1 a h se recorre el árbol
    // desde la raíz imprimiendo solo los nodos de ese nivel. En el peor caso
    // (h = n) es O(n²). Si está balanceado es O(n), porque los niveles de
    // arriba tienen pocos nodos y en total se visitan menos de 2n.
    void porNiveles() const {
        int h = altura();
        for (int nivel = 1; nivel <= h; nivel++) {
            cout << "--- Nivel " << nivel << " ---" << endl;
            imprimirNivel(raiz, nivel);
        }
    }

    // O(n): datos en orden de menor a mayor (alfabético para Jugador)
    vector<T> inordenAVector() const {
        vector<T> resultado;
        inordenAVectorRecursivo(raiz, resultado);
        return resultado;
    }

    // O(n): número de niveles (0 si está vacío)
    int altura() const {
        return alturaRecursivo(raiz);
    }

    // O(n)
    int contarNodos() const {
        return contarRecursivo(raiz);
    }

    // O(h): camino desde la raíz hasta el padre del dato. Es el mismo camino
    // que sigue la búsqueda. Si el dato es la raíz o no existe, regresa un
    // vector vacío.
    vector<T> ancestros(const T& valor) const {
        vector<T> camino;
        NodoArbol<T>* actual = raiz;
        while (actual != nullptr) {
            if (valor == actual->dato) {
                return camino;
            }
            camino.push_back(actual->dato);
            if (valor < actual->dato) {
                actual = actual->izquierdo;
            } else {
                actual = actual->derecho;
            }
        }
        camino.clear();   // no se encontró
        return camino;
    }

    // O(h): nivel del dato (raíz = 1) o -1 si no existe. Es el número de
    // pasos de la búsqueda, porque se compara un nodo por cada nivel.
    int nivelDe(const T& valor) const {
        int pasos;
        if (buscar(valor, pasos) == nullptr) {
            return -1;
        }
        return pasos;
    }
};

#endif
