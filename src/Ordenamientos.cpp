// Ordenamientos.cpp
// Implementación de Bubble Sort y Merge Sort.

#include "Ordenamientos.h"
#include "Utilidades.h"

using namespace std;

string nombreCriterio(int criterio) {
    switch (criterio) {
        case 1:  return "goles";
        case 2:  return "asistencias";
        case 3:  return "edad";
        case 4:  return "minutos";
        case 5:  return "partidos jugados";
        case 6:  return "partidos titular";
        case 7:  return "tarjetas amarillas";
        case 8:  return "tarjetas rojas";
        case 9:  return "nombre";
        case 10: return "equipo";
        case 11: return "nacionalidad";
        default: return "desconocido";
    }
}

// Funciones auxiliares para comparar: regresan -1, 0 o 1
int compararEnteros(int x, int y) {
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int compararTextos(const string& x, const string& y) {
    string a = aMinusculas(x);
    string b = aMinusculas(y);
    if (a < b) return -1;   // en string, "<" compara en orden alfabético
    if (a > b) return 1;
    return 0;
}

int compararJugadores(const Jugador& a, const Jugador& b, int criterio) {
    // El switch elige qué atributo comparar. Así un mismo algoritmo sirve
    // para ordenar por cualquiera de los 11 criterios.
    switch (criterio) {
        case 1:  return compararEnteros(a.getGoles(), b.getGoles());
        case 2:  return compararEnteros(a.getAsistencias(), b.getAsistencias());
        case 3:  return compararEnteros(a.getEdad(), b.getEdad());
        case 4:  return compararEnteros(a.getMinutos(), b.getMinutos());
        case 5:  return compararEnteros(a.getPartidosJugados(), b.getPartidosJugados());
        case 6:  return compararEnteros(a.getPartidosTitular(), b.getPartidosTitular());
        case 7:  return compararEnteros(a.getTarjetasAmarillas(), b.getTarjetasAmarillas());
        case 8:  return compararEnteros(a.getTarjetasRojas(), b.getTarjetasRojas());
        case 9:  return compararTextos(a.getNombre(), b.getNombre());
        case 10: return compararTextos(a.getEquipo(), b.getEquipo());
        case 11: return compararTextos(a.getNacionalidad(), b.getNacionalidad());
        default: return 0;   // criterio inválido: se consideran iguales
    }
}

// Nota: si los jugadores son iguales en el criterio (resultado == 0) regresa
// false, así que NO se intercambian. Eso hace que ambos algoritmos sean
// "estables": los jugadores empatados conservan el orden que tenían antes.
bool vaDespues(const Jugador& a, const Jugador& b, int criterio, bool ascendente) {
    int resultado = compararJugadores(a, b, criterio);
    if (ascendente) {
        return resultado > 0;   // de menor a mayor: el mayor va después
    } else {
        return resultado < 0;   // de mayor a menor: el menor va después
    }
}

// ============================ BUBBLE SORT ============================
// Idea: recorrer el vector comparando cada par de vecinos y
// intercambiarlos si están en el orden incorrecto. Después de cada pasada,
// el elemento que debe ir al final "sube como burbuja" hasta su lugar.

void bubbleSort(vector<Jugador>& v, int criterio, bool ascendente) {
    int n = v.size();

    for (int pasada = 0; pasada < n - 1; pasada++) {
        bool huboIntercambio = false;

        // En cada pasada revisamos un elemento menos (n - 1 - pasada),
        // porque los últimos 'pasada' elementos ya quedaron en su lugar.
        for (int j = 0; j < n - 1 - pasada; j++) {
            if (vaDespues(v[j], v[j + 1], criterio, ascendente)) {
                Jugador temporal = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temporal;
                huboIntercambio = true;
            }
        }

        // Optimización: si en toda la pasada no hubo intercambios, el vector
        // ya está ordenado y podemos terminar. Por esto el mejor caso
        // (vector ya ordenado) es O(n): una sola pasada.
        if (!huboIntercambio) {
            break;
        }
    }
}

// ============================ MERGE SORT ============================
// Idea "divide y vencerás":
//   1. Dividir el vector en dos mitades.
//   2. Ordenar cada mitad de forma recursiva.
//   3. Mezclar (merge) las dos mitades ordenadas en una sola.

void mergeSort(vector<Jugador>& v, int criterio, bool ascendente) {
    int n = v.size();
    if (n > 1) {
        mergeSortRecursivo(v, 0, n - 1, criterio, ascendente);
    }
}

void mergeSortRecursivo(vector<Jugador>& v, int inicio, int fin,
                        int criterio, bool ascendente) {
    // Caso base: una parte con 0 o 1 elementos ya está ordenada
    if (inicio >= fin) {
        return;
    }

    // Se calcula así (y no como (inicio + fin) / 2) para evitar un posible
    // desbordamiento de int si los índices fueran muy grandes.
    int mitad = inicio + (fin - inicio) / 2;

    mergeSortRecursivo(v, inicio, mitad, criterio, ascendente);     // mitad izquierda
    mergeSortRecursivo(v, mitad + 1, fin, criterio, ascendente);    // mitad derecha
    merge(v, inicio, mitad, fin, criterio, ascendente);             // unir ambas
}

void merge(vector<Jugador>& v, int inicio, int mitad, int fin,
           int criterio, bool ascendente) {
    // Copiamos cada mitad a un vector auxiliar. Estos vectores son la razón
    // por la que Merge Sort usa memoria extra O(n).
    vector<Jugador> izquierda;
    vector<Jugador> derecha;
    for (int i = inicio; i <= mitad; i++) {
        izquierda.push_back(v[i]);
    }
    for (int i = mitad + 1; i <= fin; i++) {
        derecha.push_back(v[i]);
    }

    int tamIzquierda = izquierda.size();
    int tamDerecha = derecha.size();
    int i = 0;        // índice en 'izquierda'
    int j = 0;        // índice en 'derecha'
    int k = inicio;   // posición donde escribimos en el vector original

    // Mientras las dos mitades tengan elementos, tomamos el que va primero
    while (i < tamIzquierda && j < tamDerecha) {
        // Si el de la izquierda NO va después del de la derecha, tomamos el
        // de la izquierda. En un empate se toma el de la izquierda, lo que
        // mantiene el algoritmo estable.
        if (!vaDespues(izquierda[i], derecha[j], criterio, ascendente)) {
            v[k] = izquierda[i];
            i++;
        } else {
            v[k] = derecha[j];
            j++;
        }
        k++;
    }

    // Copiamos lo que haya sobrado (solo uno de estos ciclos se ejecuta)
    while (i < tamIzquierda) {
        v[k] = izquierda[i];
        i++;
        k++;
    }
    while (j < tamDerecha) {
        v[k] = derecha[j];
        j++;
        k++;
    }
}
