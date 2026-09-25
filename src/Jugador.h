// Jugador.h
// Clase que representa a un jugador de la Premier League con sus
// estadísticas de la temporada 2025-2026.

#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
using namespace std;

class Jugador {
private:
    string nombre;
    string equipo;
    string posicion;       // Portero, Defensa, Mediocampista o Delantero
    int edad;
    string nacionalidad;
    int partidosJugados;
    int partidosTitular;
    int minutos;
    int goles;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;

public:
    // Constructor por defecto: textos vacíos y números en 0
    Jugador();

    // Constructor con parámetros
    Jugador(string nombre, string equipo, string posicion, int edad,
            string nacionalidad, int partidosJugados, int partidosTitular,
            int minutos, int goles, int asistencias,
            int tarjetasAmarillas, int tarjetasRojas);

    // Getters. Son "const" porque solo leen los atributos, no los cambian.
    string getNombre() const;
    string getEquipo() const;
    string getPosicion() const;
    int getEdad() const;
    string getNacionalidad() const;
    int getPartidosJugados() const;
    int getPartidosTitular() const;
    int getMinutos() const;
    int getGoles() const;
    int getAsistencias() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;

    // Atributo derivado: no se guarda, se calcula con goles y minutos.
    // Indica cuántos goles anota el jugador en promedio cada 90 minutos.
    double golesPor90Min() const;

    // Imprime los datos del jugador en una sola línea (una fila de la tabla)
    void mostrar() const;
};

#endif
