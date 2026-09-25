// Ordenamientos.h
// Algoritmos de ordenamiento programados desde cero: Bubble Sort y Merge Sort.
//
// Parámetro "criterio" (qué atributo se compara):
//   1 = goles   2 = asistencias   3 = edad   4 = minutos   5 = nombre
//
// Parámetro "ascendente": true = de menor a mayor (A-Z)
//                         false = de mayor a menor (Z-A)

#ifndef ORDENAMIENTOS_H
#define ORDENAMIENTOS_H

#include <string>
#include <vector>
#include "Jugador.h"

void bubbleSort(vector<Jugador>& v, int criterio, bool ascendente);
void mergeSort(vector<Jugador>& v, int criterio, bool ascendente);

// Regresa el nombre del criterio en texto (por ejemplo 1 -> "goles")
string nombreCriterio(int criterio);

#endif
