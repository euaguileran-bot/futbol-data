#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "Jugador.h"
#include "Ordenamientos.h"
using namespace std;

// Heap máximo (montículo) guardado en un vector: el jugador "mayor" según el
// criterio siempre está en la posición 0. Para el nodo en la posición i:
//   padre = (i - 1) / 2,   hijo izquierdo = 2i + 1,   hijo derecho = 2i + 2
//
// No es template como ListaDoble y ArbolBST: el heap NO puede usar el
// operador < de Jugador (ese compara por nombre, para el árbol). Necesita
// comparar por el criterio elegido (goles, asistencias...), así que usa la
// función comparar() de Ordenamientos, que solo sirve para Jugador.
//
// n = número de jugadores en el heap. Su altura es log2(n) porque el vector
// se llena nivel por nivel, de izquierda a derecha.
class MonticuloMax {
private:
    vector<Jugador> datos;
    int criterio;   // 1 = goles, 2 = asistencias, 3 = edad, 4 = minutos

    // true si 'a' debe quedar arriba de 'b'
    bool esMayor(const Jugador& a, const Jugador& b) const {
        return comparar(a, b, criterio) > 0;
    }

    void intercambiar(int i, int j) {
        Jugador temporal = datos[i];
        datos[i] = datos[j];
        datos[j] = temporal;
    }

public:
    // O(1)
    MonticuloMax(int criterio) {
        this->criterio = criterio;
    }

    // O(log n): se agrega al final y "sube" cambiándose con su padre mientras
    // sea mayor que él. Sube como máximo la altura del heap.
    void push(const Jugador& jugador) {
        datos.push_back(jugador);
        int i = datos.size() - 1;
        while (i > 0) {
            int padre = (i - 1) / 2;
            if (!esMayor(datos[i], datos[padre])) {
                break;
            }
            intercambiar(i, padre);
            i = padre;
        }
    }

    // O(1): el mayor siempre está en la posición 0
    Jugador top() const {
        return datos[0];
    }

    // O(log n): el último pasa a la raíz y "baja" cambiándose con su hijo
    // mayor mientras alguno de sus hijos sea mayor que él.
    void pop() {
        if (datos.size() == 0) {
            return;
        }
        datos[0] = datos[datos.size() - 1];
        datos.pop_back();

        int n = datos.size();
        int i = 0;
        while (true) {
            int izquierdo = 2 * i + 1;
            int derecho = 2 * i + 2;
            int mayor = i;
            if (izquierdo < n && esMayor(datos[izquierdo], datos[mayor])) {
                mayor = izquierdo;
            }
            if (derecho < n && esMayor(datos[derecho], datos[mayor])) {
                mayor = derecho;
            }
            if (mayor == i) {
                break;
            }
            intercambiar(i, mayor);
            i = mayor;
        }
    }

    // O(1)
    bool empty() const {
        return datos.size() == 0;
    }

    // O(1)
    int size() const {
        return datos.size();
    }
};

#endif
