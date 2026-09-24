// Busquedas.h
// Algoritmos de búsqueda por nombre implementados desde cero.
// La búsqueda compara el nombre completo sin importar mayúsculas/minúsculas.

#ifndef BUSQUEDAS_H
#define BUSQUEDAS_H

#include <string>
#include <vector>
#include "Jugador.h"

// Revisa uno por uno desde el inicio. Funciona aunque el vector NO esté ordenado.
// Regresa el índice donde está el jugador o -1 si no se encontró.
int busquedaSecuencial(const std::vector<Jugador>& v, const std::string& nombre);

// Divide el rango de búsqueda a la mitad en cada paso.
// REQUIERE que el vector esté ordenado por nombre de forma ascendente (A-Z),
// por ejemplo con mergeSort(v, 9, true).
// Regresa el índice donde está el jugador o -1 si no se encontró.
int busquedaBinaria(const std::vector<Jugador>& v, const std::string& nombre);

#endif
