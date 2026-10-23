#include "Jugador.h"
#include <iomanip>

Jugador::Jugador(string nombre) {
    this->nombre = nombre;
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

// "this->" indica el atributo, porque el parámetro se llama igual
Jugador::Jugador(string nombre, string equipo, string posicion, int edad,
                 string nacionalidad, int partidosJugados, int partidosTitular,
                 int minutos, int goles, int asistencias,
                 int tarjetasAmarillas, int tarjetasRojas) {
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
    if (minutos == 0) {
        return 0.0;
    }
    return goles / (minutos / 90.0);   // 90.0 y no 90, para que tenga decimales
}

// Regresa una copia del texto en minúsculas (solo cambia de la A a la Z)
string aMinusculas(string texto) {
    for (int i = 0; i < (int)texto.size(); i++) {
        if (texto[i] >= 'A' && texto[i] <= 'Z') {
            texto[i] = texto[i] - 'A' + 'a';
        }
    }
    return texto;
}

bool Jugador::operator<(const Jugador& otro) const {
    return aMinusculas(nombre) < aMinusculas(otro.nombre);
}

bool Jugador::operator>(const Jugador& otro) const {
    return aMinusculas(nombre) > aMinusculas(otro.nombre);
}

bool Jugador::operator==(const Jugador& otro) const {
    return aMinusculas(nombre) == aMinusculas(otro.nombre);
}

ostream& operator<<(ostream& salida, const Jugador& jugador) {
    // setw(n) reserva n espacios para que las columnas queden alineadas
    salida << left
           << setw(24) << jugador.getNombre()
           << setw(18) << jugador.getEquipo()
           << setw(14) << jugador.getPosicion()
           << right << setw(4) << jugador.getEdad() << "  "
           << left << setw(18) << jugador.getNacionalidad()
           << right
           << setw(4) << jugador.getPartidosJugados()
           << setw(4) << jugador.getPartidosTitular()
           << setw(6) << jugador.getMinutos()
           << setw(4) << jugador.getGoles()
           << setw(4) << jugador.getAsistencias()
           << setw(4) << jugador.getTarjetasAmarillas()
           << setw(4) << jugador.getTarjetasRojas()
           << setw(7) << fixed << setprecision(2) << jugador.golesPor90Min();
    return salida;
}
