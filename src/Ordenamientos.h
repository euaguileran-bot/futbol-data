#ifndef ORDENAMIENTOS_H
#define ORDENAMIENTOS_H

#include <string>
#include <vector>
#include "Jugador.h"

// criterio:   1 = goles, 2 = asistencias, 3 = edad, 4 = minutos, 5 = nombre
// ascendente: true = de menor a mayor (A-Z), false = de mayor a menor (Z-A)
void bubbleSort(vector<Jugador>& v, int criterio, bool ascendente);
void mergeSort(vector<Jugador>& v, int criterio, bool ascendente);

string nombreCriterio(int criterio);

// Cuántas comparaciones hizo el último ordenamiento
int getComparaciones();

#endif
