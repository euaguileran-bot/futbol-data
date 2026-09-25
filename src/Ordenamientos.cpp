#include "Ordenamientos.h"

int comparaciones = 0;

int getComparaciones() {
    return comparaciones;
}

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

// Regresa un número negativo si a < b, 0 si son iguales, positivo si a > b
int comparar(const Jugador& a, const Jugador& b, int criterio) {
    switch (criterio) {
        case 1: return a.getGoles() - b.getGoles();
        case 2: return a.getAsistencias() - b.getAsistencias();
        case 3: return a.getEdad() - b.getEdad();
        case 4: return a.getMinutos() - b.getMinutos();
        case 5:
            if (a.getNombre() < b.getNombre()) return -1;
            if (a.getNombre() > b.getNombre()) return 1;
            return 0;
        default: return 0;
    }
}

// Regresa true si 'a' debe quedar DESPUÉS de 'b'. Si son iguales regresa
// false, así los empatados no se mueven de lugar.
bool vaDespues(const Jugador& a, const Jugador& b, int criterio, bool ascendente) {
    comparaciones++;
    int resultado = comparar(a, b, criterio);
    if (ascendente) {
        return resultado > 0;
    } else {
        return resultado < 0;
    }
}

void bubbleSort(vector<Jugador>& v, int criterio, bool ascendente) {
    comparaciones = 0;
    int n = v.size();

    for (int pasada = 0; pasada < n - 1; pasada++) {
        bool huboIntercambio = false;

        // Cada pasada revisa uno menos, porque los últimos ya están en su lugar
        for (int j = 0; j < n - 1 - pasada; j++) {
            if (vaDespues(v[j], v[j + 1], criterio, ascendente)) {
                Jugador temporal = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temporal;
                huboIntercambio = true;
            }
        }

        // Si no hubo intercambios ya está ordenado (por eso el mejor caso es O(n))
        if (!huboIntercambio) {
            break;
        }
    }
}

// Mezcla las mitades ya ordenadas v[inicio..mitad] y v[mitad+1..fin]
void merge(vector<Jugador>& v, int inicio, int mitad, int fin,
           int criterio, bool ascendente) {
    // Estos vectores auxiliares son la memoria extra O(n) de Merge Sort
    vector<Jugador> izquierda;
    vector<Jugador> derecha;
    for (int i = inicio; i <= mitad; i++) {
        izquierda.push_back(v[i]);
    }
    for (int i = mitad + 1; i <= fin; i++) {
        derecha.push_back(v[i]);
    }

    int i = 0;
    int j = 0;
    int k = inicio;

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

    // Se copia lo que haya sobrado de alguna de las dos mitades
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

void mergeSortRecursivo(vector<Jugador>& v, int inicio, int fin,
                        int criterio, bool ascendente) {
    if (inicio >= fin) {
        return;   // caso base: 0 o 1 elementos ya están ordenados
    }

    int mitad = (inicio + fin) / 2;
    mergeSortRecursivo(v, inicio, mitad, criterio, ascendente);
    mergeSortRecursivo(v, mitad + 1, fin, criterio, ascendente);
    merge(v, inicio, mitad, fin, criterio, ascendente);
}

void mergeSort(vector<Jugador>& v, int criterio, bool ascendente) {
    comparaciones = 0;
    int n = v.size();
    mergeSortRecursivo(v, 0, n - 1, criterio, ascendente);
}
