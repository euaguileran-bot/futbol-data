// Busquedas.cpp
// Implementación de la búsqueda secuencial y la búsqueda binaria.

#include "Busquedas.h"
#include "Utilidades.h"

using namespace std;

int busquedaSecuencial(const vector<Jugador>& v, const string& nombre) {
    string buscado = aMinusculas(limpiarEspacios(nombre));
    int n = v.size();

    for (int i = 0; i < n; i++) {
        if (aMinusculas(v[i].getNombre()) == buscado) {
            return i;   // mejor caso: está en la primera posición -> O(1)
        }
    }
    return -1;          // peor caso: revisamos los n elementos -> O(n)
}

int busquedaBinaria(const vector<Jugador>& v, const string& nombre) {
    string buscado = aMinusculas(limpiarEspacios(nombre));
    int n = v.size();
    int inicio = 0;
    int fin = n - 1;

    while (inicio <= fin) {
        int mitad = inicio + (fin - inicio) / 2;

        // Se compara en minúsculas, igual que el criterio 9 (nombre) del
        // ordenamiento. Si se comparara distinto a como se ordenó, la
        // búsqueda binaria podría irse por la mitad equivocada.
        string actual = aMinusculas(v[mitad].getNombre());

        if (actual == buscado) {
            return mitad;          // lo encontramos
        } else if (actual < buscado) {
            inicio = mitad + 1;    // el buscado está en la mitad derecha
        } else {
            fin = mitad - 1;       // el buscado está en la mitad izquierda
        }
    }
    return -1;   // el rango quedó vacío: no está en el vector
}
