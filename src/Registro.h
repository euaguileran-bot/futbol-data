// Registro.h
// Clase que guarda a todos los jugadores cargados desde el CSV y permite
// mostrarlos y filtrarlos.

#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <vector>
#include "Jugador.h"

class Registro {
private:
    vector<Jugador> jugadores;   // todos los jugadores cargados del archivo

public:
    // Lee el archivo CSV línea por línea y guarda los jugadores válidos.
    // Regresa cuántos jugadores se cargaron (0 si no se pudo abrir el archivo).
    int cargarDesdeCSV(string ruta);

    // Muestra todos los jugadores cargados
    void mostrarTodos() const;

    // Muestra los primeros 'cantidad' jugadores de una lista en forma de tabla
    // (si 'cantidad' es 0 o más grande que la lista, se muestran todos)
    void mostrarLista(const vector<Jugador>& lista, int cantidad) const;

    // Regresa una copia del vector de jugadores (para ordenarla sin
    // modificar el registro original)
    vector<Jugador> getJugadores() const;

    // Cantidad de jugadores cargados
    int getCantidad() const;

    // Filtros: regresan un vector nuevo con los jugadores que cumplen
    vector<Jugador> filtrarPorEquipo(string equipo) const;
    vector<Jugador> filtrarPorPosicion(string posicion) const;
    vector<Jugador> filtrarPorRangoGoles(int minimo, int maximo) const;
};

#endif
