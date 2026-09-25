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
    Jugador();
    Jugador(string nombre, string equipo, string posicion, int edad,
            string nacionalidad, int partidosJugados, int partidosTitular,
            int minutos, int goles, int asistencias,
            int tarjetasAmarillas, int tarjetasRojas);

    // Son "const" porque solo leen los atributos, no los cambian
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

    // Atributo derivado: se calcula con goles y minutos, no se guarda
    double golesPor90Min() const;

    void mostrar() const;
};

#endif
