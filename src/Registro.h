#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <vector>
#include "Jugador.h"

class Registro {
private:
    vector<Jugador> jugadores;

public:
    // Regresa cuántos jugadores se cargaron (0 si no se pudo abrir el archivo)
    int cargarDesdeCSV(string ruta);

    void mostrarTodos() const;

    // Muestra los primeros 'cantidad' jugadores de la lista (0 = todos)
    void mostrarLista(const vector<Jugador>& lista, int cantidad) const;

    vector<Jugador> getJugadores() const;
    int getCantidad() const;

    vector<Jugador> filtrarPorEquipo(string equipo) const;
    vector<Jugador> filtrarPorPosicion(string posicion) const;
    vector<Jugador> filtrarPorRangoGoles(int minimo, int maximo) const;
};

#endif
