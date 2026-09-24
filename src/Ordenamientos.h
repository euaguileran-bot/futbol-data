// Ordenamientos.h
// Algoritmos de ordenamiento implementados desde cero: Bubble Sort y Merge Sort.
// Son funciones libres (no pertenecen a una clase).
//
// Parámetro "criterio" (qué atributo se compara):
//   1 = goles              7 = tarjetas amarillas
//   2 = asistencias        8 = tarjetas rojas
//   3 = edad               9 = nombre (alfabético)
//   4 = minutos           10 = equipo (alfabético)
//   5 = partidos jugados  11 = nacionalidad (alfabética)
//   6 = partidos titular
//
// Parámetro "ascendente": true = de menor a mayor (A-Z),
//                         false = de mayor a menor (Z-A).

#ifndef ORDENAMIENTOS_H
#define ORDENAMIENTOS_H

#include <string>
#include <vector>
#include "Jugador.h"

// Regresa el nombre del criterio en texto (por ejemplo 1 -> "goles")
std::string nombreCriterio(int criterio);

// Compara dos jugadores según el criterio. Regresa:
//   un número negativo si a < b,  0 si son iguales,  un número positivo si a > b.
// Los textos se comparan en minúsculas para que "de Ligt" y "De Cuyper"
// queden en el lugar correcto sin importar las mayúsculas.
int compararJugadores(const Jugador& a, const Jugador& b, int criterio);

// Regresa true si 'a' debe quedar DESPUÉS de 'b' en el resultado final,
// tomando en cuenta el criterio y si el orden es ascendente o descendente.
bool vaDespues(const Jugador& a, const Jugador& b, int criterio, bool ascendente);

// Bubble Sort con optimización (se detiene si en una pasada no hubo intercambios)
void bubbleSort(std::vector<Jugador>& v, int criterio, bool ascendente);

// Merge Sort: función que se llama desde el programa
void mergeSort(std::vector<Jugador>& v, int criterio, bool ascendente);

// Parte recursiva de Merge Sort: ordena v[inicio..fin]
void mergeSortRecursivo(std::vector<Jugador>& v, int inicio, int fin,
                        int criterio, bool ascendente);

// Función auxiliar de Merge Sort: mezcla las mitades ya ordenadas
// v[inicio..mitad] y v[mitad+1..fin] en una sola parte ordenada
void merge(std::vector<Jugador>& v, int inicio, int mitad, int fin,
           int criterio, bool ascendente);

#endif
