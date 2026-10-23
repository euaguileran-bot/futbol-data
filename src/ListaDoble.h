#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <iostream>
#include <vector>
using namespace std;

// ¿Por qué todo el código del template está en el .h y no hay ListaDoble.cpp?
// Un template es un "molde": el compilador fabrica la versión real (por
// ejemplo ListaDoble<Jugador>) en el archivo donde se usa, y para eso necesita
// ver el código completo de cada método. Si estuvieran en un .cpp aparte, al
// compilar Registro.cpp solo vería las declaraciones y el programa no enlazaría.

template <class T>
class NodoLista {
public:
    T dato;
    NodoLista<T>* anterior;
    NodoLista<T>* siguiente;

    NodoLista(const T& valor) {
        dato = valor;
        anterior = nullptr;
        siguiente = nullptr;
    }
};

// Lista doblemente ligada: cada nodo apunta al anterior y al siguiente.
// n = número de nodos. No se debe copiar (pasar por valor): la copia apuntaría
// a los mismos nodos y el destructor los liberaría dos veces.
template <class T>
class ListaDoble {
private:
    NodoLista<T>* cabeza;
    NodoLista<T>* cola;
    int tamano;

public:
    // O(1)
    ListaDoble() {
        cabeza = nullptr;
        cola = nullptr;
        tamano = 0;
    }

    // O(n): libera todos los nodos
    ~ListaDoble() {
        vaciar();
    }

    // O(n): recorre la lista borrando cada nodo
    void vaciar() {
        NodoLista<T>* actual = cabeza;
        while (actual != nullptr) {
            NodoLista<T>* siguiente = actual->siguiente;   // se guarda antes de borrar
            delete actual;
            actual = siguiente;
        }
        cabeza = nullptr;
        cola = nullptr;
        tamano = 0;
    }

    // O(1): gracias al apuntador a la cola no hay que recorrer la lista
    void insertarAlFinal(const T& valor) {
        NodoLista<T>* nuevo = new NodoLista<T>(valor);
        if (cola == nullptr) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        tamano++;
    }

    // O(n): búsqueda secuencial desde la cabeza usando ==. Regresa un apuntador
    // al dato (o nullptr si no está) y en 'pasos' cuántos nodos comparó.
    T* buscar(const T& valor, int& pasos) const {
        pasos = 0;
        NodoLista<T>* actual = cabeza;
        while (actual != nullptr) {
            pasos++;
            if (actual->dato == valor) {
                return &(actual->dato);
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    // O(n): de la cabeza a la cola
    void mostrarAdelante() const {
        NodoLista<T>* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->dato << endl;
            actual = actual->siguiente;
        }
    }

    // O(n): de la cola a la cabeza, usando el apuntador 'anterior'
    void mostrarAtras() const {
        NodoLista<T>* actual = cola;
        while (actual != nullptr) {
            cout << actual->dato << endl;
            actual = actual->anterior;
        }
    }

    // O(n): copia los datos a un vector para ordenarlos o filtrarlos sin
    // modificar la lista
    vector<T> aVector() const {
        vector<T> resultado;
        NodoLista<T>* actual = cabeza;
        while (actual != nullptr) {
            resultado.push_back(actual->dato);
            actual = actual->siguiente;
        }
        return resultado;
    }

    // O(1)
    int obtenerTamano() const {
        return tamano;
    }
};

#endif
