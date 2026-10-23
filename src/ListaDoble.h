#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <iostream>
#include <vector>
using namespace std;

// ¿Por qué todo el código del template está en el .h y no hay ListaDoble.cpp?
// Un template es un "molde": el compilador fabrica la versión real (por
// ejemplo ListaDoble<Jugador>) en el archivo donde se usa, y para eso necesita
// ver el código completo de cada método. Si los métodos estuvieran en un .cpp
// aparte, al compilar Registro.cpp solo vería las declaraciones, nunca se
// fabricaría ListaDoble<Jugador> y el programa no enlazaría.

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
// n = número de nodos.
// No se debe copiar (pasar por valor): la copia apuntaría a los mismos nodos
// y el destructor los liberaría dos veces. Siempre se pasa por referencia.
template <class T>
class ListaDoble {
private:
    NodoLista<T>* cabeza;
    NodoLista<T>* cola;
    int tamano;

    // O(n): regresa el nodo de una posición (0 = cabeza). Como la lista es
    // doble, si la posición está en la segunda mitad se recorre desde la cola
    // hacia atrás. Así nunca se visitan más de n/2 nodos (sigue siendo O(n),
    // pero con la mitad de pasos que en una lista simple).
    NodoLista<T>* nodoEnPosicion(int posicion) const {
        NodoLista<T>* actual;
        if (posicion < tamano / 2) {
            actual = cabeza;
            for (int i = 0; i < posicion; i++) {
                actual = actual->siguiente;
            }
        } else {
            actual = cola;
            for (int i = tamano - 1; i > posicion; i--) {
                actual = actual->anterior;
            }
        }
        return actual;
    }

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

    // O(1)
    void insertarAlInicio(const T& valor) {
        NodoLista<T>* nuevo = new NodoLista<T>(valor);
        if (cabeza == nullptr) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
            cabeza = nuevo;
        }
        tamano++;
    }

    // O(n): búsqueda secuencial desde la cabeza usando ==.
    // Regresa la posición (o -1 si no está) y en 'pasos' cuántos nodos comparó.
    int buscar(const T& valor, int& pasos) const {
        pasos = 0;
        NodoLista<T>* actual = cabeza;
        int posicion = 0;
        while (actual != nullptr) {
            pasos++;
            if (actual->dato == valor) {
                return posicion;
            }
            actual = actual->siguiente;
            posicion++;
        }
        return -1;
    }

    // O(n): llega a la posición con nodoEnPosicion
    T obtenerEnPosicion(int posicion) const {
        if (posicion < 0 || posicion >= tamano) {
            T vacio;
            return vacio;
        }
        return nodoEnPosicion(posicion)->dato;
    }

    // O(n): llega a la posición y reemplaza el dato
    bool actualizarEnPosicion(int posicion, const T& valor) {
        if (posicion < 0 || posicion >= tamano) {
            return false;
        }
        nodoEnPosicion(posicion)->dato = valor;
        return true;
    }

    // O(n): llegar al nodo cuesta O(n) (desde la cabeza o desde la cola, ver
    // nodoEnPosicion); desconectarlo cuesta O(1)
    bool eliminarEnPosicion(int posicion) {
        if (posicion < 0 || posicion >= tamano) {
            return false;
        }
        NodoLista<T>* nodo = nodoEnPosicion(posicion);

        // Se conecta el anterior con el siguiente, "saltándose" el nodo
        if (nodo->anterior != nullptr) {
            nodo->anterior->siguiente = nodo->siguiente;
        } else {
            cabeza = nodo->siguiente;   // era la cabeza
        }
        if (nodo->siguiente != nullptr) {
            nodo->siguiente->anterior = nodo->anterior;
        } else {
            cola = nodo->anterior;      // era la cola
        }

        delete nodo;
        tamano--;
        return true;
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

    // O(1)
    bool estaVacia() const {
        return tamano == 0;
    }
};

#endif
