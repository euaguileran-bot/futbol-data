// Ordenamientos.cpp
// Implementación de Bubble Sort y Merge Sort.

#include "Ordenamientos.h"

string nombreCriterio(int criterio) {
    switch (criterio) {
        case 1: return "goles";
        case 2: return "asistencias";
        case 3: return "edad";
        case 4: return "minutos";
        case 5: return "nombre";
        default: return "desconocido";
    }
}

// Compara dos jugadores según el criterio. Regresa:
//   un número negativo si a < b,  0 si son iguales,  un número positivo si a > b
int comparar(const Jugador& a, const Jugador& b, int criterio) {
    switch (criterio) {
        case 1: return a.getGoles() - b.getGoles();
        case 2: return a.getAsistencias() - b.getAsistencias();
        case 3: return a.getEdad() - b.getEdad();
        case 4: return a.getMinutos() - b.getMinutos();
        case 5:
            // Con strings, "<" y ">" comparan en orden alfabético
            if (a.getNombre() < b.getNombre()) return -1;
            if (a.getNombre() > b.getNombre()) return 1;
            return 0;
        default: return 0;
    }
}

// Regresa true si 'a' debe quedar DESPUÉS de 'b' en el resultado.
// Si son iguales regresa false, así los empatados no se mueven de lugar.
bool vaDespues(const Jugador& a, const Jugador& b, int criterio, bool ascendente) {
    int resultado = comparar(a, b, criterio);
    if (ascendente) {
        return resultado > 0;   // de menor a mayor: el mayor va después
    } else {
        return resultado < 0;   // de mayor a menor: el menor va después
    }
}

// ============================ BUBBLE SORT ============================
// Compara cada par de vecinos y los intercambia si están en el orden
// incorrecto. Después de cada pasada, el elemento que debe ir al final
// "sube como burbuja" hasta su lugar.

void bubbleSort(vector<Jugador>& v, int criterio, bool ascendente) {
    int n = v.size();

    for (int pasada = 0; pasada < n - 1; pasada++) {
        bool huboIntercambio = false;

        // Los últimos 'pasada' elementos ya están en su lugar,
        // por eso cada pasada revisa uno menos
        for (int j = 0; j < n - 1 - pasada; j++) {
            if (vaDespues(v[j], v[j + 1], criterio, ascendente)) {
                Jugador temporal = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temporal;
                huboIntercambio = true;
            }
        }

        // Optimización: si no hubo ningún intercambio, ya está ordenado.
        // Por esto el mejor caso (datos ya ordenados) es O(n).
        if (!huboIntercambio) {
            break;
        }
    }
}

// ============================ MERGE SORT ============================
// Divide y vencerás:
//   1. Dividir el vector en dos mitades.
//   2. Ordenar cada mitad (llamándose a sí mismo, de forma recursiva).
//   3. Mezclar (merge) las dos mitades ordenadas en una sola.

// Mezcla las mitades ya ordenadas v[inicio..mitad] y v[mitad+1..fin]
void merge(vector<Jugador>& v, int inicio, int mitad, int fin,
           int criterio, bool ascendente) {
    // Copiamos cada mitad a un vector auxiliar. Estos vectores son
    // la razón por la que Merge Sort usa memoria extra O(n).
    vector<Jugador> izquierda;
    vector<Jugador> derecha;
    for (int i = inicio; i <= mitad; i++) {
        izquierda.push_back(v[i]);
    }
    for (int i = mitad + 1; i <= fin; i++) {
        derecha.push_back(v[i]);
    }

    int i = 0;        // posición en 'izquierda'
    int j = 0;        // posición en 'derecha'
    int k = inicio;   // posición donde escribimos en el vector original

    // Mientras las dos mitades tengan elementos, tomamos el que va primero
    while (i < (int)izquierda.size() && j < (int)derecha.size()) {
        if (!vaDespues(izquierda[i], derecha[j], criterio, ascendente)) {
            v[k] = izquierda[i];
            i++;
        } else {
            v[k] = derecha[j];
            j++;
        }
        k++;
    }

    // Copiamos lo que haya sobrado de alguna de las dos mitades
    while (i < (int)izquierda.size()) {
        v[k] = izquierda[i];
        i++;
        k++;
    }
    while (j < (int)derecha.size()) {
        v[k] = derecha[j];
        j++;
        k++;
    }
}

// Parte recursiva: ordena v[inicio..fin]
void mergeSortRecursivo(vector<Jugador>& v, int inicio, int fin,
                        int criterio, bool ascendente) {
    // Caso base: una parte con 0 o 1 elementos ya está ordenada
    if (inicio >= fin) {
        return;
    }

    int mitad = (inicio + fin) / 2;
    mergeSortRecursivo(v, inicio, mitad, criterio, ascendente);    // mitad izquierda
    mergeSortRecursivo(v, mitad + 1, fin, criterio, ascendente);   // mitad derecha
    merge(v, inicio, mitad, fin, criterio, ascendente);            // unir las dos
}

void mergeSort(vector<Jugador>& v, int criterio, bool ascendente) {
    int n = v.size();
    mergeSortRecursivo(v, 0, n - 1, criterio, ascendente);
}
