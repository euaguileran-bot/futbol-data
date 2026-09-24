// Jugador.cpp
// Implementación de la clase Jugador.

#include "Jugador.h"

#include <iostream>
#include <iomanip>   // setw, setprecision, left, right, fixed

using namespace std;

Jugador::Jugador() {
    nombre = "";
    equipo = "";
    posicion = "";
    edad = 0;
    nacionalidad = "";
    partidosJugados = 0;
    partidosTitular = 0;
    minutos = 0;
    goles = 0;
    asistencias = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
}

// Como los parámetros se llaman igual que los atributos, usamos "this->"
// para indicar que del lado izquierdo está el atributo del objeto.
Jugador::Jugador(const string& nombre, const string& equipo,
                 const string& posicion, int edad, const string& nacionalidad,
                 int partidosJugados, int partidosTitular, int minutos,
                 int goles, int asistencias, int tarjetasAmarillas, int tarjetasRojas) {
    this->nombre = nombre;
    this->equipo = equipo;
    this->posicion = posicion;
    this->edad = edad;
    this->nacionalidad = nacionalidad;
    this->partidosJugados = partidosJugados;
    this->partidosTitular = partidosTitular;
    this->minutos = minutos;
    this->goles = goles;
    this->asistencias = asistencias;
    this->tarjetasAmarillas = tarjetasAmarillas;
    this->tarjetasRojas = tarjetasRojas;
}

string Jugador::getNombre() const { return nombre; }
string Jugador::getEquipo() const { return equipo; }
string Jugador::getPosicion() const { return posicion; }
int Jugador::getEdad() const { return edad; }
string Jugador::getNacionalidad() const { return nacionalidad; }
int Jugador::getPartidosJugados() const { return partidosJugados; }
int Jugador::getPartidosTitular() const { return partidosTitular; }
int Jugador::getMinutos() const { return minutos; }
int Jugador::getGoles() const { return goles; }
int Jugador::getAsistencias() const { return asistencias; }
int Jugador::getTarjetasAmarillas() const { return tarjetasAmarillas; }
int Jugador::getTarjetasRojas() const { return tarjetasRojas; }

double Jugador::golesPor90Min() const {
    // Si el jugador no ha jugado ni un minuto evitamos dividir entre 0
    if (minutos == 0) {
        return 0.0;
    }
    // Se usa 90.0 (y no 90) para que la división sea con decimales;
    // con enteros, 100 / 90 daría 1 en lugar de 1.11
    return goles / (minutos / 90.0);
}

void Jugador::mostrar() const {
    // setw(n) reserva n espacios para el siguiente dato; así las columnas
    // quedan alineadas. "left" alinea texto a la izquierda y "right" los
    // números a la derecha. Los anchos coinciden con el encabezado que
    // imprime Registro::mostrarLista().
    cout << left
         << setw(24) << nombre
         << setw(18) << equipo
         << setw(14) << posicion
         << right << setw(4) << edad << "  "
         << left << setw(18) << nacionalidad
         << right
         << setw(4) << partidosJugados
         << setw(4) << partidosTitular
         << setw(6) << minutos
         << setw(4) << goles
         << setw(4) << asistencias
         << setw(4) << tarjetasAmarillas
         << setw(4) << tarjetasRojas
         << setw(7) << fixed << setprecision(2) << golesPor90Min()
         << endl;
}
