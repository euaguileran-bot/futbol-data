// Jugador.h
// Clase que representa a un jugador de la Premier League con sus
// estadísticas de la temporada 2025-2026.

#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

class Jugador {
private:
    std::string nombre;
    std::string equipo;
    std::string posicion;       // Portero, Defensa, Mediocampista o Delantero
    int edad;
    std::string nacionalidad;
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

    // Constructor con parámetros.
    // Los textos se reciben como "const std::string&" (referencia constante)
    // para no copiar el texto al llamar la función y garantizar que no se modifica.
    Jugador(const std::string& nombre, const std::string& equipo,
            const std::string& posicion, int edad, const std::string& nacionalidad,
            int partidosJugados, int partidosTitular, int minutos,
            int goles, int asistencias, int tarjetasAmarillas, int tarjetasRojas);

    // Getters. Son "const" porque solo leen los atributos, no los cambian.
    std::string getNombre() const;
    std::string getEquipo() const;
    std::string getPosicion() const;
    int getEdad() const;
    std::string getNacionalidad() const;
    int getPartidosJugados() const;
    int getPartidosTitular() const;
    int getMinutos() const;
    int getGoles() const;
    int getAsistencias() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;

    // Atributo derivado: no se guarda, se calcula a partir de goles y minutos.
    // Indica cuántos goles anota el jugador en promedio cada 90 minutos.
    double golesPor90Min() const;

    // Imprime los datos del jugador formateados en una sola línea (fila de tabla)
    void mostrar() const;
};

#endif
